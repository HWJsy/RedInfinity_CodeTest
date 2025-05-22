#include "GameView.h"
#include "CardView.h"
USING_NS_CC;

// ��ɸ��� UI �������������ֵ
const Vec2 GameView::kTrayTopPosition = Vec2(680, 20);
const Vec2 GameView::kStockOrigin = Vec2(20, 20);

// ��ʼ����̬��Ա����
std::map<int, CardView*> GameView::_playfieldViews;
std::map<int, CardView*> GameView::_stockViews;
CardView* GameView::_trayTopView = nullptr;
std::map<int, CardView*> GameView::_trayHistoryViews;

GameView* GameView::create(const std::shared_ptr<GameModel>& m) {
    auto p = new (std::nothrow) GameView();
    if (p && p->init(m)) { p->autorelease(); return p; }
    delete p;
    return nullptr;
}

std::shared_ptr<GameView> GameView::createShared(const std::shared_ptr<GameModel>& m) {
    auto ptr = std::shared_ptr<GameView>(new (std::nothrow) GameView());
    if (ptr && ptr->init(m)) { ptr->autorelease(); return ptr; }
    return nullptr;
}

bool GameView::init(const std::shared_ptr<GameModel>& model)
{
    if (!Layer::init()) return false;
    _gameModel = model;
    createUI();
    return true;
}

void GameView::createUI()
{
    createBackground();
    createPlayfield();
    createStockArea();
    createTrayArea();
    
    // ���� overlayNode����֤�������ϲ�
    _overlayNode = Node::create();
    this->addChild(_overlayNode, std::numeric_limits<int>::max());

    createUndoButton();
}

void GameView::createBackground()
{
    // ��������
    auto bgUp = LayerColor::create(Color4B(204, 102, 0, 100), 1080, 1500);
    bgUp->setPosition(0, 580);
    addChild(bgUp);
    // ��������
    auto bgDown = LayerColor::create(Color4B(153, 51, 255, 100), 1080, 580);
    bgDown->setPosition(0, 0);
    addChild(bgDown);
}

void GameView::createPlayfield()
{
    _playfieldNode = Node::create();
    _playfieldNode->setPosition(Vec2(0, 580)); // �������������
    addChild(_playfieldNode);
}

void GameView::createStockArea()
{
    _stockNode = Node::create();
    _stockNode->setPosition(kStockOrigin);
    addChild(_stockNode);
}

void GameView::createTrayArea()
{
    _trayNode = Node::create();
    _trayNode->setPosition(kTrayTopPosition);
    addChild(_trayNode);
}

void GameView::createUndoButton()
{
    auto label = Label::createWithTTF("Undo", "fonts/Arial.ttf", 52);
    label->setTextColor(Color4B::WHITE);
    auto item = MenuItemLabel::create(label, CC_CALLBACK_1(GameView::onUndoButtonClicked, this));
    _ui = Menu::create(item, nullptr);
    _ui->setPosition(Vec2(570, 50));
    addChild(_ui);
}

void GameView::updateView()
{
    // ��� overlayNode �ϲ�������ʱ����
    if (_overlayNode) {
        _overlayNode->removeAllChildren();
    }

    updatePlayfieldCards();
    updateStockCards();
    updateTrayTopCard();
    updateTrayHistory();
}

void GameView::updatePlayfieldCards()
{
    _playfieldNode->removeAllChildren();
    _playfieldViews.clear();

    auto cards = _gameModel->getPlayfieldCards();
    CCLOG("GameView: updatePlayfieldCards(), model has %zu cards", cards.size());

    for (auto& cm : cards) {
        auto cv = CardView::create(cm);
        if (!cv) {
            CCLOGERROR("GameView: failed to create CardView for model id=%d", cm->getId());
            continue;
        }

        cv->setPosition(cm->getPosition());
        cv->setClickCallback(_cardClickCallback);
        _playfieldNode->addChild(cv);
        _playfieldViews[cm->getId()] = cv;
    }
}

void GameView::updateStockCards()
{
    _stockNode->removeAllChildren();
    _stockViews.clear();

    auto& stock = _gameModel->getStockCards();
    for (size_t i = 0; i < stock.size(); ++i) {
        auto cm = stock[i];
        auto cv = CardView::create(cm);
        // ����ƫ�� = 100 * ջ�и߶�
        cv->setPosition(Vec2(100.f * i, 0));
        cv->setClickCallback([this, cm](int id) {
            // ������ջ���Ŵ���
            if (_gameModel->getStockCards().back()->getId() == id && _cardClickCallback) {
                _cardClickCallback(id);
            }
            });
        _stockNode->addChild(cv);
        _stockViews[cm->getId()] = cv;
    }
}

void GameView::updateTrayTopCard()
{
    if (_trayTopView) {
        _trayTopView->removeFromParent();
    }
    _trayTopView = nullptr;
    auto top = _gameModel->getTopTrayCard();
    if (top) {
        _trayTopView = CardView::create(top);
        _trayTopView->setPosition(Vec2::ZERO); // ����λ���Ѷ�
        _trayTopView->setClickCallback(_cardClickCallback);
        _trayNode->addChild(_trayTopView);
    }
}

void GameView::updateTrayHistory()
{
    // �������ڻ���ʱ�ָ���ʷ�����������е������
    for (auto& kv : _trayHistoryViews) {
        kv.second->removeFromParent();
    }
    _trayHistoryViews.clear();

    auto& history = _gameModel->getTrayCards();
    for (size_t i = 0; i < history.size(); ++i) {
        auto cm = history[i];
        auto cv = CardView::create(cm);
        cv->setPosition(Vec2(0, 0)); // �����ڶ�����
        _trayNode->addChild(cv, -1);  // ��֤��ջ����ͼ֮��
        _trayHistoryViews[cm->getId()] = cv;
    }
}


void GameView::onUndoButtonClicked(Ref* sender)
{
    if (_undoClickCallback) {
        _undoClickCallback();
    }
}

void GameView::playMoveToAnimation(int cardId)
{
    auto cardView = getCardViewById(cardId);
    if (!cardView) return;

    // 1) ����� cardView ��ǰ�� GameView ����ϵ�е�λ��
    Vec2 worldPos = cardView->getParent()->convertToWorldSpace(cardView->getPosition());
    Vec2 localPos = this->convertToNodeSpace(worldPos);

    // 2) ��ԭ���ڵ��Ƴ��������ͷţ�
    cardView->retain();                  // ��ֹ autorelease pool ����
    cardView->removeFromParent();

    // 3) �ŵ� overlayNode ��
    _overlayNode->addChild(cardView);
    cardView->setPosition(localPos);

    // 4) Ŀ��λ��ͬ��ת���� overlay ����ϵ
    Vec2 worldTarget = this->convertToWorldSpace(kTrayTopPosition);
    Vec2 overlayTarget = _overlayNode->convertToNodeSpace(worldTarget);


    // 5) ���Ŷ������ƶ��� overlayTarget
    auto move = MoveTo::create(0.5f, overlayTarget);
    auto onDone = CallFunc::create([this, cardView]() {
        this->updateView();   // ������������ updateView �ؽ�������ͼ
        cardView->release();  // ��� retain
        });

    cardView->runAction(Sequence::create(move, onDone, nullptr));

}

CardView* GameView::getCardViewById(int cardId)
{
    if (_playfieldViews.find(cardId) != _playfieldViews.end()) {
        return _playfieldViews[cardId];
    }
    if (_stockViews.find(cardId) != _stockViews.end()) {
        return _stockViews[cardId];
    }
    if (_trayTopView && _trayTopView->getCardId() == cardId) {
        return _trayTopView;
    }
    if (_trayHistoryViews.find(cardId) != _trayHistoryViews.end()) {
        return _trayHistoryViews[cardId];
    }
    return nullptr;
}