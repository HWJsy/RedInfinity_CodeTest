// GameModel.cpp
#include "GameModel.h"
USING_NS_CC; 

GameModel::GameModel() {}

GameModel::~GameModel() {}

// ��ʼ����Ϸģ�ͣ�����������ݽṹ
bool GameModel::init() {
    _playfieldCards.clear();         // ��������
    _stockCards.clear();             // ʣ����ջ
    _trayCards.clear();              // ������ջ
    _cardPositionHistory.clear();    // ����λ����Ϣ��¼�����ڳ���
    _cards.clear();                  // ���п��Ƶ� ID -> ʵ��ӳ��
    return true;
}

// ��ӿ��Ƶ�������
void GameModel::addCardToPlayfield(const std::shared_ptr<CardModel>& card) {
    if (!card) return;
    _playfieldCards.push_back(card);
    _cards[card->getId()] = card; // ��¼��ӳ����
}

// ��ӿ��Ƶ�ʣ����ջ
void GameModel::addCardToStock(const std::shared_ptr<CardModel>& card) {
    if (!card) return;
    _stockCards.push_back(card);
    _cards[card->getId()] = card;
}

// ��ӿ��Ƶ�������ջ
void GameModel::addCardToTray(const std::shared_ptr<CardModel>& card) {
    if (!card) return;
    _trayCards.push_back(card);
    _cards[card->getId()] = card;
}

// ��ȡ���ƶ�
const std::vector<std::shared_ptr<CardModel>>& GameModel::getPlayfieldCards() const {
    return _playfieldCards;
}

// ��ȡʣ����ջ
const std::vector<std::shared_ptr<CardModel>>& GameModel::getStockCards() const {
    return _stockCards;
}

// ��ȡ������ջ
const std::vector<std::shared_ptr<CardModel>>& GameModel::getTrayCards() const {
    return _trayCards;
}

// ��ȡ����ջ�����Ϸ�һ�ſ��ƣ������һ�ţ�
std::shared_ptr<CardModel> GameModel::getTopTrayCard() const {
    return _trayCards.empty() ? nullptr : _trayCards.back();
}

// ��ʣ����ջ��һ�ſ��Ƶ�������ջ
bool GameModel::stockToTray() {
    if (_stockCards.empty()) return false;
    auto card = _stockCards.back();     // ��ȡջ����
    _stockCards.pop_back();             // �Ƴ�ʣ��ջ
    _trayCards.push_back(card);         // ���붥��ջ
    return true;
}

// �������һ��ָ�������ƶ���������ջ
bool GameModel::playfieldToTray(int cardId) {
    for (auto it = _playfieldCards.begin(); it != _playfieldCards.end(); ++it) {
        if ((*it)->getId() == cardId) {
            auto card = *it;
            _playfieldCards.erase(it); // �������Ƴ�
            CCLOG("now playfieldCards has %d cards", _playfieldCards.size());
            _trayCards.push_back(card); // ���붥��ջ
            return true;
        }
    }
    log("GameModel::playfieldToTray: cardId %d not found", cardId);
    return false; // δ�ҵ��ÿ���
}

// �ж�ָ�������Ƿ���ƥ�䶥��ջ������
bool GameModel::canMoveToTray(int cardId) const {
    auto it = _cards.find(cardId);
    auto top = getTopTrayCard();
    if (it == _cards.end() || !top) return false;
    return it->second->canMatch(top.get()); // ���ÿ��Ƶ�ƥ���߼�
}

// ���Խ����ƴ������ƶ���������ջ��ƥ��ɹ�ʱ��
bool GameModel::matchCardToTray(int cardId) {
    if (!canMoveToTray(cardId)) return false;

    // ��¼��λ�����ڳ�������
    recordCardPosition(cardId, getCardPosition(cardId));

    // ʵ��ת�ƿ���
    return playfieldToTray(cardId);
}

// ��¼����λ�ã����ڳ���ʱ�ָ���
void GameModel::recordCardPosition(int cardId, const Vec2& pos) {
    _cardPositionHistory[cardId] = pos;
}

// �ָ����Ƶ�ĳ��λ�ã�ͨ�����ڳ���ʱ��
void GameModel::restoreCardPosition(int cardId, const Vec2& pos) {
    auto it = _cards.find(cardId);
    if (it != _cards.end()) {
        it->second->setPosition(pos);
    }
}

// ����һ�ſ��Ƶ�ƥ�����
void GameModel::undoCardMatch(int cardId, const Vec2& targetPos) {
    CCLOG("Undo record position for card %d: (%.2f, %.2f)", cardId, targetPos.x, targetPos.y);

    auto card = _cards.at(cardId);     // ��ȡ���ƶ���
    card->setPosition(targetPos);      // ��ԭλ��

    _trayCards.pop_back();             // �Ӷ���ջ����
    _playfieldCards.push_back(card);   // �Ż�����
}

// ����������ջ�� stock �鿨�Ĳ���
void GameModel::undoCardReplace(int cardId) {
    auto card = _cards.at(cardId);     // ��ȡ���ƶ���

    _trayCards.pop_back();             // �Ӷ���ջ����
    _stockCards.push_back(card);       // �Ż�ʣ��ջ
}

// �жϿ����Ƿ�����������
bool GameModel::isCardInPlayfield(int cardId) const {
    for (auto& c : _playfieldCards)
        if (c->getId() == cardId) return true;
    return false;
}

// ��ȡָ�����Ƶ�ǰ��λ��
Vec2 GameModel::getCardPosition(int cardId) const {
    auto it = _cards.find(cardId);
    return it != _cards.end() ? it->second->getPosition() : Vec2::ZERO;
}

// ���� ID ��ȡ����ʵ��
std::shared_ptr<CardModel> GameModel::getCardById(int cardId) const {
    auto it = _cards.find(cardId);
    return it != _cards.end() ? it->second : nullptr;
}
