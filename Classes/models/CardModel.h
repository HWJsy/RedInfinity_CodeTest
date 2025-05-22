#ifndef CARDMODEL_H
#define CARDMODEL_H

#include "cocos2d.h"

// 花色类型
enum CardSuitType
{
    CST_NONE = -1,
    CST_CLUBS,      // 梅花
    CST_DIAMONDS,   // 方块
    CST_HEARTS,     // 红桃
    CST_SPADES,     // 黑桃
    CST_NUM_CARD_SUIT_TYPES
};

// 牌面类型
enum CardFaceType
{
    CFT_NONE = -1,
    CFT_ACE = 0,    // A
    CFT_TWO,        // 2
    CFT_THREE,      // 3
    CFT_FOUR,       // 4
    CFT_FIVE,       // 5
    CFT_SIX,        // 6
    CFT_SEVEN,      // 7
    CFT_EIGHT,      // 8
    CFT_NINE,       // 9
    CFT_TEN,        // 10
    CFT_JACK,       // J
    CFT_QUEEN,      // Q
    CFT_KING,       // K
    CFT_NUM_CARD_FACE_TYPES
};

class CardModel
{
public:
    CardModel(int id, CardFaceType face, CardSuitType suit);
    virtual ~CardModel();

    // Getter 方法
    int getId() const { return _id; }
    CardFaceType getFace() const { return _face; }
    CardSuitType getSuit() const { return _suit; }
    cocos2d::Vec2 getPosition() const { return _position; }

    // Setter 方法
    void setPosition(const cocos2d::Vec2& pos) { _position = pos; }

    // 检查两张牌是否可以匹配（数字相差1）
    bool canMatch(const CardModel* other) const;
private:
    int _id;                // 卡牌唯一ID
    CardFaceType _face;     // 牌面
    CardSuitType _suit;     // 花色
    cocos2d::Vec2 _position;// 卡牌位置
};

#endif