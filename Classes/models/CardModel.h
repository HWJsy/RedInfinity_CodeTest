#ifndef CARDMODEL_H
#define CARDMODEL_H

#include "cocos2d.h"

USING_NS_CC;

/**
 * @enum CardSuitType
 * @brief ���ƻ�ɫö������
 */
enum CardSuitType {
    CST_NONE = -1,      ///< δ֪��ɫ
    CST_CLUBS,          ///< ÷��
    CST_DIAMONDS,       ///< ����
    CST_HEARTS,         ///< ����
    CST_SPADES,         ///< ����
    CST_NUM_CARD_SUIT_TYPES  ///< ��ɫ��������
};

/**
 * @enum CardFaceType
 * @brief ������ֵö������
 */
enum CardFaceType {
    CFT_NONE = -1,      ///< δ������ֵ
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
    CFT_NUM_CARD_FACE_TYPES  ///< ��ֵ��������
};

/**
 * @class CardModel
 * @brief ��ʾһ�ſ��Ƶ�ģ�ͣ�����Ψһ ID����ֵ����ɫ��λ�á�
 *
 * CardModel ����洢���ṩ���ƵĻ�����Ϣ����֧�ּ������һ�ſ����Ƿ��ƥ�䡣
 */
class CardModel {
public:
    /**
     * @brief ���캯��
     * @param id Ψһ��ʶ�ÿ��Ƶ� ID
     * @param face ������ֵ
     * @param suit ���ƻ�ɫ
     */
    CardModel(int id, CardFaceType face, CardSuitType suit);

    /**
     * @brief ��������
     */
    virtual ~CardModel();

    /**
     * @brief ��ȡ���� ID
     * @return ���Ƶ�Ψһ ID
     */
    int getId() const { return _id; }

    /**
     * @brief ��ȡ������ֵ
     * @return ������ֵö��
     */
    CardFaceType getFace() const { return _face; }

    /**
     * @brief ��ȡ���ƻ�ɫ
     * @return ���ƻ�ɫö��
     */
    CardSuitType getSuit() const { return _suit; }

    /**
     * @brief ��ȡ���Ƶ�ǰλ��
     * @return �����ڳ����е�����
     */
    Vec2 getPosition() const { return _position; }

    /**
     * @brief ���ÿ���λ��
     * @param pos Ҫ���õ���λ��
     */
    void setPosition(const Vec2& pos) { _position = pos; }

    /**
     * @brief ������ſ����Ƿ��ƥ�䣨��ֵ���1��
     * @param other ��һ�ſ��Ƶ�ģ��ָ��
     * @return ����ƥ�䷵�� true������ false
     */
    bool canMatch(const CardModel* other) const;

private:
    int     _id;         ///< ����Ψһ��ʶ
    CardFaceType _face;  ///< ������ֵ
    CardSuitType _suit;  ///< ���ƻ�ɫ
    Vec2    _position;   ///< �����ڳ����е�����
};

#endif // CARDMODEL_H
