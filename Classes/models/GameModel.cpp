// GameModel.cpp
#include "GameModel.h"
USING_NS_CC; 

GameModel::GameModel() {}

GameModel::~GameModel() {}

// 初始化游戏模型，清空所有数据结构
bool GameModel::init() {
    _playfieldCards.clear();         // 桌面牌区
    _stockCards.clear();             // 剩余牌栈
    _trayCards.clear();              // 顶部牌栈
    _cardPositionHistory.clear();    // 卡牌位置信息记录，用于撤销
    _cards.clear();                  // 所有卡牌的 ID -> 实例映射
    return true;
}

// 添加卡牌到桌面区
void GameModel::addCardToPlayfield(const std::shared_ptr<CardModel>& card) {
    if (!card) return;
    _playfieldCards.push_back(card);
    _cards[card->getId()] = card; // 记录到映射中
}

// 添加卡牌到剩余牌栈
void GameModel::addCardToStock(const std::shared_ptr<CardModel>& card) {
    if (!card) return;
    _stockCards.push_back(card);
    _cards[card->getId()] = card;
}

// 添加卡牌到顶部牌栈
void GameModel::addCardToTray(const std::shared_ptr<CardModel>& card) {
    if (!card) return;
    _trayCards.push_back(card);
    _cards[card->getId()] = card;
}

// 获取主牌堆
const std::vector<std::shared_ptr<CardModel>>& GameModel::getPlayfieldCards() const {
    return _playfieldCards;
}

// 获取剩余牌栈
const std::vector<std::shared_ptr<CardModel>>& GameModel::getStockCards() const {
    return _stockCards;
}

// 获取顶部牌栈
const std::vector<std::shared_ptr<CardModel>>& GameModel::getTrayCards() const {
    return _trayCards;
}

// 获取顶部栈的最上方一张卡牌（即最后一张）
std::shared_ptr<CardModel> GameModel::getTopTrayCard() const {
    return _trayCards.empty() ? nullptr : _trayCards.back();
}

// 从剩余牌栈抽一张卡牌到顶部牌栈
bool GameModel::stockToTray() {
    if (_stockCards.empty()) return false;
    auto card = _stockCards.back();     // 获取栈顶卡
    _stockCards.pop_back();             // 移出剩余栈
    _trayCards.push_back(card);         // 推入顶部栈
    return true;
}

// 将桌面的一张指定卡牌移动到顶部牌栈
bool GameModel::playfieldToTray(int cardId) {
    for (auto it = _playfieldCards.begin(); it != _playfieldCards.end(); ++it) {
        if ((*it)->getId() == cardId) {
            auto card = *it;
            _playfieldCards.erase(it); // 从桌面移除
            CCLOG("now playfieldCards has %d cards", _playfieldCards.size());
            _trayCards.push_back(card); // 推入顶部栈
            return true;
        }
    }
    log("GameModel::playfieldToTray: cardId %d not found", cardId);
    return false; // 未找到该卡牌
}

// 判断指定卡牌是否能匹配顶部栈顶卡牌
bool GameModel::canMoveToTray(int cardId) const {
    auto it = _cards.find(cardId);
    auto top = getTopTrayCard();
    if (it == _cards.end() || !top) return false;
    return it->second->canMatch(top.get()); // 调用卡牌的匹配逻辑
}

// 尝试将卡牌从桌面移动到顶部牌栈（匹配成功时）
bool GameModel::matchCardToTray(int cardId) {
    if (!canMoveToTray(cardId)) return false;

    // 记录旧位置用于撤销操作
    recordCardPosition(cardId, getCardPosition(cardId));

    // 实际转移卡牌
    return playfieldToTray(cardId);
}

// 记录卡牌位置（用于撤销时恢复）
void GameModel::recordCardPosition(int cardId, const Vec2& pos) {
    _cardPositionHistory[cardId] = pos;
}

// 恢复卡牌到某个位置（通常用于撤销时）
void GameModel::restoreCardPosition(int cardId, const Vec2& pos) {
    auto it = _cards.find(cardId);
    if (it != _cards.end()) {
        it->second->setPosition(pos);
    }
}

// 撤销一张卡牌的匹配操作
void GameModel::undoCardMatch(int cardId, const Vec2& targetPos) {
    CCLOG("Undo record position for card %d: (%.2f, %.2f)", cardId, targetPos.x, targetPos.y);

    auto card = _cards.at(cardId);     // 获取卡牌对象
    card->setPosition(targetPos);      // 还原位置

    _trayCards.pop_back();             // 从顶部栈弹出
    _playfieldCards.push_back(card);   // 放回桌面
}

// 撤销顶部牌栈从 stock 抽卡的操作
void GameModel::undoCardReplace(int cardId) {
    auto card = _cards.at(cardId);     // 获取卡牌对象

    _trayCards.pop_back();             // 从顶部栈弹出
    _stockCards.push_back(card);       // 放回剩余栈
}

// 判断卡牌是否还在桌面区中
bool GameModel::isCardInPlayfield(int cardId) const {
    for (auto& c : _playfieldCards)
        if (c->getId() == cardId) return true;
    return false;
}

// 获取指定卡牌当前的位置
Vec2 GameModel::getCardPosition(int cardId) const {
    auto it = _cards.find(cardId);
    return it != _cards.end() ? it->second->getPosition() : Vec2::ZERO;
}

// 根据 ID 获取卡牌实例
std::shared_ptr<CardModel> GameModel::getCardById(int cardId) const {
    auto it = _cards.find(cardId);
    return it != _cards.end() ? it->second : nullptr;
}
