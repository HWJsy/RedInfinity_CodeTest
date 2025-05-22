#ifndef UNDOACTION_H
#define UNDOACTION_H

#include "cocos2d.h"

// ���˲�������
enum class UndoActionType
{
    NONE,
    CARD_MATCHED,    // ����ƥ�����
    STACK_TO_TRAY    // ��ʣ��ջ�Ƶ�����ջ�Ĳ���
};

class UndoAction
{
public:
    UndoAction(UndoActionType type, int cardId, const cocos2d::Vec2& position);
    UndoActionType getType() const;
    int getCardId() const;
    const cocos2d::Vec2& getPosition() const;

private:
    UndoActionType _type;
    int _cardId;
    cocos2d::Vec2 _position;
};

#endif