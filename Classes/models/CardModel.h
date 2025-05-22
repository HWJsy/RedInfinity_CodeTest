#ifndef CARDMODEL_H
#define CARDMODEL_H

#include "cocos2d.h"

// ��ɫ����
enum CardSuitType
{
    CST_NONE = -1,
    CST_CLUBS,      // ÷��
    CST_DIAMONDS,   // ����
    CST_HEARTS,     // ����
    CST_SPADES,     // ����
    CST_NUM_CARD_SUIT_TYPES
};

// ��������
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

    // Getter ����
    int getId() const { return _id; }
    CardFaceType getFace() const { return _face; }
    CardSuitType getSuit() const { return _suit; }
    cocos2d::Vec2 getPosition() const { return _position; }

    // Setter ����
    void setPosition(const cocos2d::Vec2& pos) { _position = pos; }

    // ����������Ƿ����ƥ�䣨�������1��
    bool canMatch(const CardModel* other) const;
private:
    int _id;                // ����ΨһID
    CardFaceType _face;     // ����
    CardSuitType _suit;     // ��ɫ
    cocos2d::Vec2 _position;// ����λ��
};

#endif