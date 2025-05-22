#include "CardModel.h"

CardModel::CardModel(int id, CardFaceType face, CardSuitType suit)
    : _id(id)
    , _face(face)
    , _suit(suit)
    , _position(cocos2d::Vec2::ZERO)
{
}

CardModel::~CardModel()
{
}

bool CardModel::canMatch(const CardModel* other) const
{
    if (!other) return false;

    // 检查牌面数字是否相差1
    int thisValue = static_cast<int>(_face);
    int otherValue = static_cast<int>(other->getFace());

    return (thisValue == otherValue + 1) || (thisValue == otherValue - 1);
}