// models/GameModel.cpp
#include "GameModel.h"
USING_NS_CC;

GameModel::GameModel() {}
GameModel::~GameModel() {}

bool GameModel::init() {
    _playfieldCards.clear();
    _stockCards.clear();
    _trayCards.clear();
    _cardPositionHistory.clear();
    _cards.clear();
    return true;
}

void GameModel::addCardToPlayfield(std::shared_ptr<CardModel> card) {
    if (!card) return;
    _playfieldCards.push_back(card);
    _cards[card->getId()] = card;
}

void GameModel::addCardToStock(std::shared_ptr<CardModel> card) {
    if (!card) return;
    _stockCards.push_back(card);
    _cards[card->getId()] = card;
}

void GameModel::addCardToTray(std::shared_ptr<CardModel> card) {
    if (!card) return;
    _trayCards.push_back(card);
    _cards[card->getId()] = card;
}

std::shared_ptr<CardModel> GameModel::getTopTrayCard() const {
    return _trayCards.empty() ? nullptr : _trayCards.back();
}

bool GameModel::stockToTray() {
    if (_stockCards.empty()) return false;
    auto card = _stockCards.back();
    _stockCards.pop_back();
    _trayCards.push_back(card);
    return true;
}

bool GameModel::playfieldToTray(int cardId) {
    // 遍历手牌区，找到并移除
    for (auto it = _playfieldCards.begin(); it != _playfieldCards.end(); ++it) {
        if ((*it)->getId() == cardId) {
            auto card = *it;
            _playfieldCards.erase(it);
            CCLOG("now playfieldCards has %d cards",_playfieldCards.size());
            // 推入顶部牌区
            _trayCards.push_back(card);
            return true;
        }
    }
    log("GameModel::playfieldToTray: cardId %d not found", cardId);
    return false;
}

bool GameModel::canMoveToTray(int cardId) const {
    auto it = _cards.find(cardId);
    auto top = getTopTrayCard();
    if (it == _cards.end() || !top) return false;
    return it->second->canMatch(top.get());
}

bool GameModel::matchCardToTray(int cardId) {
    if (!canMoveToTray(cardId)) return false;
    // 记录旧位置以便撤销
    recordCardPosition(cardId, getCardPosition(cardId));
    // 从 Playfield 转移到 Tray
    return playfieldToTray(cardId);
}

void GameModel::recordCardPosition(int cardId, const Vec2& pos) {
    _cardPositionHistory[cardId] = pos;
}

void GameModel::restoreCardPosition(int cardId, const Vec2& pos) {
    auto it = _cards.find(cardId);
    if (it != _cards.end()) {
        it->second->setPosition(pos);
    }
}

void GameModel::undoCardMatch(int cardId, const Vec2& targetPos) {
    // 恢复到 playfield
    CCLOG("Undo record position for card %d: (%.2f, %.2f)", cardId, targetPos.x, targetPos.y);
    auto card = _cards.at(cardId);
    card->setPosition(targetPos);

    _trayCards.pop_back();//弹出栈顶卡牌
    _playfieldCards.push_back(card);//添加到桌面牌区中
    
}

void GameModel::undoCardReplace(int cardId)
{
    // 恢复到 stock
    auto card = _cards.at(cardId);

    _trayCards.pop_back();//弹出栈顶卡牌
    _stockCards.push_back(card);//添加到桌面牌区中
}

bool GameModel::isCardInPlayfield(int cardId) const {
    for (auto& c : _playfieldCards) if (c->getId() == cardId) return true;
    return false;
}

Vec2 GameModel::getCardPosition(int cardId) const {
    auto it = _cards.find(cardId);
    return it != _cards.end() ? it->second->getPosition() : Vec2::ZERO;
}

std::shared_ptr<CardModel> GameModel::getCardById(int cardId) const {
    auto it = _cards.find(cardId);
    return it != _cards.end() ? it->second : nullptr;
}

