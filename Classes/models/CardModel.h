#ifndef CARDMODEL_H
#define CARDMODEL_H

#include "cocos2d.h"

USING_NS_CC;

/**
 * @enum CardSuitType
 * @brief 卡牌花色枚举类型
 */
enum CardSuitType {
    CST_NONE = -1,      ///< 未知花色
    CST_CLUBS,          ///< 梅花
    CST_DIAMONDS,       ///< 方块
    CST_HEARTS,         ///< 红桃
    CST_SPADES,         ///< 黑桃
    CST_NUM_CARD_SUIT_TYPES  ///< 花色类型总数
};

/**
 * @enum CardFaceType
 * @brief 卡牌面值枚举类型
 */
enum CardFaceType {
    CFT_NONE = -1,      ///< 未定义面值
    CFT_ACE = 0,        ///< A
    CFT_TWO,            ///< 2
    CFT_THREE,          ///< 3
    CFT_FOUR,           ///< 4
    CFT_FIVE,           ///< 5
    CFT_SIX,            ///< 6
    CFT_SEVEN,          ///< 7
    CFT_EIGHT,          ///< 8
    CFT_NINE,           ///< 9
    CFT_TEN,            ///< 10
    CFT_JACK,           ///< J
    CFT_QUEEN,          ///< Q
    CFT_KING,           ///< K
    CFT_NUM_CARD_FACE_TYPES  ///< 面值类型总数
};

/**
 * @class CardModel
 * @brief 表示一张卡牌的模型，包括唯一 ID、面值、花色和位置。
 *
 * CardModel 负责存储和提供卡牌的基本信息，并支持检查与另一张卡牌是否可匹配。
 */
class CardModel {
public:
    /**
     * @brief 构造函数
     * @param id 唯一标识该卡牌的 ID
     * @param face 卡牌面值
     * @param suit 卡牌花色
     */
    CardModel(int id, CardFaceType face, CardSuitType suit);

    /**
     * @brief 析构函数
     */
    virtual ~CardModel();

    /**
     * @brief 获取卡牌 ID
     * @return 卡牌的唯一 ID
     */
    int getId() const { return _id; }

    /**
     * @brief 获取卡牌面值
     * @return 卡牌面值枚举
     */
    CardFaceType getFace() const { return _face; }

    /**
     * @brief 获取卡牌花色
     * @return 卡牌花色枚举
     */
    CardSuitType getSuit() const { return _suit; }

    /**
     * @brief 获取卡牌当前位置
     * @return 卡牌在场景中的坐标
     */
    Vec2 getPosition() const { return _position; }

    /**
     * @brief 设置卡牌位置
     * @param pos 要设置的新位置
     */
    void setPosition(const Vec2& pos) { _position = pos; }

    /**
     * @brief 检查两张卡牌是否可匹配（面值相差1）
     * @param other 另一张卡牌的模型指针
     * @return 可以匹配返回 true，否则 false
     */
    bool canMatch(const CardModel* other) const;

private:
    int     _id;         ///< 卡牌唯一标识
    CardFaceType _face;  ///< 卡牌面值
    CardSuitType _suit;  ///< 卡牌花色
    Vec2    _position;   ///< 卡牌在场景中的坐标
};

#endif // CARDMODEL_H
