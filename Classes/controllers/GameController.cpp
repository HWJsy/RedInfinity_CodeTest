#include "GameController.h"
#include "views/GameView.h"
#include "views/CardView.h"
#include "models/GameModel.h"
#include "managers/UndoManager.h"
#include "models/UndoAction.h"
#include "configs/models/LevelConfig.h"
#include "services/GameModelFromLevelGenerator.h"
USING_NS_CC;

std::shared_ptr<GameController> GameController::create(const std::shared_ptr<GameModel>& model)
{
    return std::make_shared<GameController>(model);
}

GameController::GameController(const std::shared_ptr<GameModel>& model)
    : _gameModel(model)
{
    _undoManager = UndoManager::create();
}

GameController::~GameController() = default;

bool GameController::init(const std::shared_ptr<GameView>& view)
{
    _gameView = view;
    _gameView->setCardClickCallback([this](int cardId) { this->handleCardClick(cardId); });
    _gameView->setUndoClickCallback([this]() { this->handleUndoClick(); });
    return true;
}

void GameController::startGame(int levelId)
{
    // 初始化撤销管理器
    _undoManager->init();

    // 若模型尚未创建，加载关卡配置
    if (!_gameModel) {
        GameModel* rawModel = GameModelFromLevelGenerator::generateGameModel(levelId);
        if (!rawModel) {
            CCLOGERROR("Failed to generate GameModel for level %d", levelId);
            return;
        }
        CCLOG("Succeeded to generate GameModel for level %d", levelId);
        _gameModel = std::shared_ptr<GameModel>(rawModel);
    }
    // 通知 View 更新画面（会创建所有 CardView 节点）
    _gameView->updateView();

    // —— 调试输出 —— 
    logGameState();
}

void GameController::handleCardClick(int cardId)
{
    if (_gameModel->isCardInPlayfield(cardId)) {
        if (!isTopPlayfieldCard(cardId)) return;
        if (canMatchToTray(cardId))
        {
            matchCardToTray(cardId);
            _gameView->playMoveToAnimation(cardId);
        }
    }
    else {
        auto& stock = _gameModel->getStockCards();
        if (!stock.empty() && stock.back()->getId() == cardId) {
            _undoManager->recordAction(std::make_shared<UndoAction>(
                UndoActionType::STACK_TO_TRAY, cardId, Vec2::ZERO));
            _gameModel->stockToTray();
            _gameView->playMoveToAnimation(cardId);
        }
    }
    
    logGameState();
}

bool GameController::canMatchToTray(int cardId) const { return _gameModel->canMoveToTray(cardId); }

void GameController::matchCardToTray(int cardId)
{
    Vec2 orig = _gameModel->getCardPosition(cardId);
    CCLOG("Undo record position for card %d: (%.2f, %.2f)", cardId, orig.x, orig.y);
    _undoManager->recordAction(std::make_shared<UndoAction>(UndoActionType::CARD_MATCHED, cardId, orig));
    _gameModel->playfieldToTray(cardId);
}

bool GameController::isTopPlayfieldCard(int cardId) const
{
    const auto& cards = _gameModel->getPlayfieldCards();
    int idx = -1;
    for (int i = 0; i < cards.size(); ++i) if (cards[i]->getId() == cardId) { idx = i; break; }
    if (idx < 0) return false;
    Rect r1(cards[idx]->getPosition(), Size(182, 282));
    for (int j = idx + 1; j < cards.size(); ++j) {
        Rect r2(cards[j]->getPosition(), Size(182, 282));
        if (r1.intersectsRect(r2)) return false;
    }
    return true;
}

void GameController::handleUndoClick()
{
    if (!_undoManager->canUndo())
    {
        CCLOG("=== _undoManager can't undo ===");
        return;
    }
    auto action = _undoManager->undo();
    if (!action)
    {
        CCLOG("=== _undoManager can't undo ===");
        return;
    }
    if (action->getType() == UndoActionType::CARD_MATCHED) {
        int id = action->getCardId(); 
        Vec2 pos = action->getPosition();
        _gameModel->undoCardMatch(id, pos);
    }
    else if (action->getType() == UndoActionType::STACK_TO_TRAY) {
        // 把顶部栈顶移回 stock
        int id = action->getCardId();
        // 弹出 tray 栈顶
        _gameModel->undoCardReplace(id);
    }
    _gameView->updateView();

    logGameState();
}

void GameController::logGameState() const
{
    // 1) 桌面区
    CCLOG("=== Playfield Cards ===");
    for (auto& cm : _gameModel->getPlayfieldCards()) {
        Vec2 pos = cm->getPosition();
        CCLOG("ID %d: Face=%d Suit=%d Pos=(%.1f, %.1f)",
            cm->getId(),
            static_cast<int>(cm->getFace()),
            static_cast<int>(cm->getSuit()),
            pos.x, pos.y);
    }

    // 2) 剩余牌栈（Stock）
    CCLOG("=== Stock Cards (remaining) ===");
    auto& stock = _gameModel->getStockCards();
    for (auto& cm : stock) {
        Vec2 pos = cm->getPosition();
        CCLOG("ID %d: Face=%d Suit=%d Pos=(%.1f, %.1f)",
            cm->getId(),
            static_cast<int>(cm->getFace()),
            static_cast<int>(cm->getSuit()),
            pos.x, pos.y);
    }

    // 3) 顶部牌栈（Tray Top + history）
    CCLOG("=== Tray Top =====");
    if (auto top = _gameModel->getTopTrayCard()) {
        Vec2 pos = top->getPosition();
        CCLOG("ID %d: Face=%d Suit=%d Pos=(%.1f, %.1f)",
            top->getId(),
            static_cast<int>(top->getFace()),
            static_cast<int>(top->getSuit()),
            pos.x, pos.y);
    }
    else {
        CCLOG("Tray is empty");
    }

    CCLOG("=== Tray History (past moves) ===");
    for (auto& cm : _gameModel->getTrayCards()) {
        Vec2 pos = cm->getPosition();
        CCLOG("ID %d: Face=%d Suit=%d Pos=(%.1f, %.1f)",
            cm->getId(),
            static_cast<int>(cm->getFace()),
            static_cast<int>(cm->getSuit()),
            pos.x, pos.y);
    }
}