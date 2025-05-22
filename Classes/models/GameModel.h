#ifndef GAMEMODEL_H
#define GAMEMODEL_H

#include "cocos2d.h"
#include "CardModel.h"
#include <vector>
#include <memory>
#include <map>

class GameModel {
public:
    GameModel();
    virtual ~GameModel();
    bool init();

    // ���ӿ�
    void addCardToPlayfield(std::shared_ptr<CardModel> card);
    void addCardToStock(std::shared_ptr<CardModel> card); // ʣ����ջ
    void addCardToTray(std::shared_ptr<CardModel> card); // ������ջ

    // ���ʽӿ�
    const std::vector<std::shared_ptr<CardModel>>& getPlayfieldCards() const { return _playfieldCards; }
    std::vector<std::shared_ptr<CardModel>>& getPlayfieldCards() { return _playfieldCards; }

    const std::vector<std::shared_ptr<CardModel>>& getStockCards() const { return _stockCards; }
    std::vector<std::shared_ptr<CardModel>>& getStockCards() { return _stockCards; }

    const std::vector<std::shared_ptr<CardModel>>& getTrayCards() const { return _trayCards; }
    std::vector<std::shared_ptr<CardModel>>& getTrayCards() { return _trayCards; }

    std::shared_ptr<CardModel> getTopTrayCard() const;
    bool stockToTray();                             // ��ʣ��ջ��һ�ŵ�����ջ
    bool playfieldToTray(int cardId);               // ��ƥ����������ƶ�������ջ

    // ƥ�����
    bool canMoveToTray(int cardId) const;
    bool matchCardToTray(int cardId);

    // ����֧��
    void recordCardPosition(int cardId, const cocos2d::Vec2& pos);
    void restoreCardPosition(int cardId, const cocos2d::Vec2& pos);
    void undoCardMatch(int cardId, const cocos2d::Vec2& targetPos);
    void GameModel::undoCardReplace(int cardId);

    bool isCardInPlayfield(int cardId) const;
    cocos2d::Vec2 getCardPosition(int cardId) const;
    std::shared_ptr<CardModel> getCardById(int cardId) const;



private:
    std::vector<std::shared_ptr<CardModel>> _playfieldCards; //������
    std::vector<std::shared_ptr<CardModel>> _stockCards; // ʣ����ջ
    std::vector<std::shared_ptr<CardModel>> _trayCards;  // ������ջ
    std::map<int, cocos2d::Vec2> _cardPositionHistory;
    std::map<int, std::shared_ptr<CardModel>> _cards;
};

#endif