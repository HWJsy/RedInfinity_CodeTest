#include "UndoAction.h"

UndoAction::UndoAction(UndoActionType type,
    int cardId,
    const Vec2& position)
    : _type(type)
    , _cardId(cardId)
    , _position(position)
{
}

UndoActionType UndoAction::getType() const {
    return _type;
}

int UndoAction::getCardId() const {
    return _cardId;
}

const Vec2& UndoAction::getPosition() const {
    return _position;
}
