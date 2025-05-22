#include "GameView.h"
#include "CardView.h"
USING_NS_CC;

// 你可根据 UI 布局需求调整数值
const Vec2 GameView::kTrayTopPosition = Vec2(680, 20);
const Vec2 GameView::kStockOrigin = Vec2(20, 20);

// 初始化静态成员变量
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
    
    // 创建 overlayNode，保证它在最上层
    _overlayNode = Node::create();
    this->addChild(_overlayNode, std::numeric_limits<int>::max());

    createUndoButton();
}

void GameView::createBackground()
{
    // 上区背景
    auto bgUp = LayerColor::create(Color4B(204, 102, 0, 100), 1080, 1500);
    bgUp->setPosition(0, 580);
    addChild(bgUp);
    // 下区背景
    auto bgDown = LayerColor::create(Color4B(153, 51, 255, 100), 1080, 580);
    bgDown->setPosition(0, 0);
    addChild(bgDown);
}

void GameView::createPlayfield()
{
    _playfieldNode = Node::create();
    _playfieldNode->setPosition(Vec2(0, 580)); // 相对于上区背景
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
    // 清除 overlayNode 上残留的临时卡牌
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
        // 横向偏移 = 100 * 栈中高度
        cv->setPosition(Vec2(100.f * i, 0));
        cv->setClickCallback([this, cm](int id) {
            // 仅当是栈顶才触发
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
        _trayTopView->setPosition(Vec2::ZERO); // 容器位置已定
        _trayTopView->setClickCallback(_cardClickCallback);
        _trayNode->addChild(_trayTopView);
    }
}

void GameView::updateTrayHistory()
{
    // 这里用于回退时恢复历史动画，不进行点击处理
    for (auto& kv : _trayHistoryViews) {
        kv.second->removeFromParent();
    }
    _trayHistoryViews.clear();

    auto& history = _gameModel->getTrayCards();
    for (size_t i = 0; i < history.size(); ++i) {
        auto cm = history[i];
        auto cv = CardView::create(cm);
        cv->setPosition(Vec2(0, 0)); // 覆盖在顶牌下
        _trayNode->addChild(cv, -1);  // 保证在栈顶视图之下
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

    // 1) 计算出 cardView 当前在 GameView 坐标系中的位置
    Vec2 worldPos = cardView->getParent()->convertToWorldSpace(cardView->getPosition());
    Vec2 localPos = this->convertToNodeSpace(worldPos);

    // 2) 从原父节点移除它（不释放）
    cardView->retain();                  // 防止 autorelease pool 回收
    cardView->removeFromParent();

    // 3) 放到 overlayNode 上
    _overlayNode->addChild(cardView);
    cardView->setPosition(localPos);

    // 4) 目标位置同样转换到 overlay 坐标系
    Vec2 worldTarget = this->convertToWorldSpace(kTrayTopPosition);
    Vec2 overlayTarget = _overlayNode->convertToNodeSpace(worldTarget);


    // 5) 播放动画：移动到 overlayTarget
    auto move = MoveTo::create(0.5f, overlayTarget);
    auto onDone = CallFunc::create([this, cardView]() {
        this->updateView();   // 动画结束后，用 updateView 重建所有视图
        cardView->release();  // 配对 retain
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