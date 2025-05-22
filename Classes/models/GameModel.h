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

    // 填充接口
    void addCardToPlayfield(std::shared_ptr<CardModel> card);
    void addCardToStock(std::shared_ptr<CardModel> card); // 剩余牌栈
    void addCardToTray(std::shared_ptr<CardModel> card); // 顶部牌栈

    // 访问接口
    const std::vector<std::shared_ptr<CardModel>>& getPlayfieldCards() const { return _playfieldCards; }
    std::vector<std::shared_ptr<CardModel>>& getPlayfieldCards() { return _playfieldCards; }

    const std::vector<std::shared_ptr<CardModel>>& getStockCards() const { return _stockCards; }
    std::vector<std::shared_ptr<CardModel>>& getStockCards() { return _stockCards; }

    const std::vector<std::shared_ptr<CardModel>>& getTrayCards() const { return _trayCards; }
    std::vector<std::shared_ptr<CardModel>>& getTrayCards() { return _trayCards; }

    std::shared_ptr<CardModel> getTopTrayCard() const;
    bool stockToTray();                             // 从剩余栈推一张到顶部栈
    bool playfieldToTray(int cardId);               // 将匹配的桌面牌移动到顶部栈

    // 匹配相关
    bool canMoveToTray(int cardId) const;
    bool matchCardToTray(int cardId);

    // 撤销支持
    void recordCardPosition(int cardId, const cocos2d::Vec2& pos);
    void restoreCardPosition(int cardId, const cocos2d::Vec2& pos);
    void undoCardMatch(int cardId, const cocos2d::Vec2& targetPos);
    void GameModel::undoCardReplace(int cardId);

    bool isCardInPlayfield(int cardId) const;
    cocos2d::Vec2 getCardPosition(int cardId) const;
    std::shared_ptr<CardModel> getCardById(int cardId) const;



private:
    std::vector<std::shared_ptr<CardModel>> _playfieldCards; //桌面牌
    std::vector<std::shared_ptr<CardModel>> _stockCards; // 剩余牌栈
    std::vector<std::shared_ptr<CardModel>> _trayCards;  // 顶部牌栈
    std::map<int, cocos2d::Vec2> _cardPositionHistory;
    std::map<int, std::shared_ptr<CardModel>> _cards;
};

#endif