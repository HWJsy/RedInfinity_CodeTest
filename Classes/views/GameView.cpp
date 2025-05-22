#include "GameView.h"
#include "CardView.h"

USING_NS_CC;

const Vec2 GameView::kTrayTopPosition = Vec2(680, 20);
const Vec2 GameView::kStockOrigin = Vec2(20, 20);

std::map<int, CardView*> GameView::_playfieldViews;
std::map<int, CardView*> GameView::_stockViews;
CardView* GameView::_trayTopView = nullptr;
std::map<int, CardView*> GameView::_trayHistoryViews;

GameView* GameView::create(const std::shared_ptr<GameModel>& model)
{
    auto p = new (std::nothrow) GameView();
    if (p && p->init(model))
    {
        p->autorelease();
        return p;
    }
    delete p;
    return nullptr;
}

std::shared_ptr<GameView> GameView::createShared(const std::shared_ptr<GameModel>& model)
{
    auto ptr = std::shared_ptr<GameView>(new (std::nothrow) GameView());
    if (ptr && ptr->init(model))
    {
        ptr->autorelease();
        return ptr;
    }
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

    // 创建动画覆盖节点，确保在最上层显示动画
    _overlayNode = Node::create();
    this->addChild(_overlayNode, std::numeric_limits<int>::max());

    createUndoButton();
}

void GameView::createBackground()
{
    // 上区背景，橙色半透明
    auto bgUp = LayerColor::create(Color4B(204, 102, 0, 100), 1080, 1500);
    bgUp->setPosition(Vec2(0, 580));
    addChild(bgUp);

    // 下区背景，紫色半透明
    auto bgDown = LayerColor::create(Color4B(153, 51, 255, 100), 1080, 580);
    bgDown->setPosition(Vec2(0, 0));
    addChild(bgDown);
}

void GameView::createPlayfield()
{
    _playfieldNode = Node::create();
    _playfieldNode->setPosition(Vec2(0, 580));
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
    if (_overlayNode)
    {
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

    for (auto& cm : cards)
    {
        auto cv = CardView::create(cm);
        if (!cv)
        {
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
    for (size_t i = 0; i < stock.size(); ++i)
    {
        auto cm = stock[i];
        auto cv = CardView::create(cm);
        cv->setPosition(Vec2(100.f * i, 0));

        // 只有栈顶卡牌触发点击回调
        cv->setClickCallback([this, cm](int id) {
            if (!_cardClickCallback) return;
            if (_gameModel->getStockCards().back()->getId() == id)
            {
                _cardClickCallback(id);
            }
            });

        _stockNode->addChild(cv);
        _stockViews[cm->getId()] = cv;
    }
}

void GameView::updateTrayTopCard()
{
    if (_trayTopView)
    {
        _trayTopView->removeFromParent();
        _trayTopView = nullptr;
    }

    auto top = _gameModel->getTopTrayCard();
    if (top)
    {
        _trayTopView = CardView::create(top);
        _trayTopView->setPosition(Vec2::ZERO);
        _trayTopView->setClickCallback(_cardClickCallback);
        _trayNode->addChild(_trayTopView);
    }
}

void GameView::updateTrayHistory()
{
    for (auto& kv : _trayHistoryViews)
    {
        kv.second->removeFromParent();
    }
    _trayHistoryViews.clear();

    auto& history = _gameModel->getTrayCards();
    for (auto& cm : history)
    {
        auto cv = CardView::create(cm);
        cv->setPosition(Vec2::ZERO);
        _trayNode->addChild(cv, -1); // 确保在顶牌下方
        _trayHistoryViews[cm->getId()] = cv;
    }
}

void GameView::onUndoButtonClicked(Ref* sender)
{
    if (_undoClickCallback)
    {
        _undoClickCallback();
    }
}

void GameView::playMoveToAnimation(int cardId)
{
    auto cardView = getCardViewById(cardId);
    if (!cardView) return;

    // 转换 cardView 在 GameView 坐标系中的位置
    Vec2 worldPos = cardView->getParent()->convertToWorldSpace(cardView->getPosition());
    Vec2 localPos = this->convertToNodeSpace(worldPos);

    // 从原父节点移除但不释放
    cardView->retain();
    cardView->removeFromParent();

    // 添加到 overlayNode 以保证动画显示在最顶层
    cardView->setPosition(localPos);
    _overlayNode->addChild(cardView);
    cardView->release();

    // 创建移动动画到托盘顶位置，带缓动效果
    auto move = MoveTo::create(0.3f, kTrayTopPosition);
    auto ease = EaseIn::create(move, 2.0f);

    cardView->runAction(Sequence::create(ease, nullptr));
}

const std::map<int, CardView*>& GameView::getPlayfieldViews() const
{
    return _playfieldViews;
}

const std::map<int, CardView*>& GameView::getStockViews() const
{
    return _stockViews;
}

CardView*& GameView::getTrayTopView()
{
    return _trayTopView;
}

const std::map<int, CardView*>& GameView::getTrayHistoryViews() const
{
    return _trayHistoryViews;
}

CardView* GameView::getCardViewById(int cardId)
{
    if (_playfieldViews.count(cardId)) return _playfieldViews[cardId];
    if (_stockViews.count(cardId)) return _stockViews[cardId];
    if (_trayHistoryViews.count(cardId)) return _trayHistoryViews[cardId];
    if (_trayTopView && _trayTopView->getCardId() == cardId) return _trayTopView;
    return nullptr;
}

void GameView::setCardClickCallback(const std::function<void(int)>& cb)
{
    _cardClickCallback = cb;
}

void GameView::setUndoClickCallback(const std::function<void()>& cb)
{
    _undoClickCallback = cb;
}
