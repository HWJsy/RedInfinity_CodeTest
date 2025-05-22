#ifndef UNDOACTION_H
#define UNDOACTION_H

#include "cocos2d.h"

// 回退操作类型
enum class UndoActionType
{
    NONE,
    CARD_MATCHED,    // 卡牌匹配操作
    STACK_TO_TRAY    // 从剩余栈推到顶部栈的操作
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