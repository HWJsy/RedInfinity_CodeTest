#include "CardModel.h"

CardModel::CardModel(int id, CardFaceType face, CardSuitType suit)
    : _id(id)
    , _face(face)
    , _suit(suit)
    , _position(Vec2::ZERO) {
}

CardModel::~CardModel() = default;

bool CardModel::canMatch(const CardModel* other) const {
    if (!other) {
        return false;
    }

    // ת����ֵ�����Ͳ�����Ƿ���� 1
    int thisValue = static_cast<int>(_face);
    int otherValue = static_cast<int>(other->getFace());

    return (thisValue == otherValue + 1) || (thisValue == otherValue - 1);
}
