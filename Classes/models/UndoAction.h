#ifndef UNDOACTION_H
#define UNDOACTION_H

#include "cocos2d.h"

USING_NS_CC;

/**
 * @enum UndoActionType
 * @brief 定义支持的撤销操作类型
 *
 * NONE              - 无操作
 * CARD_MATCHED      - 卡牌匹配到托盘的操作
 * STACK_TO_TRAY     - 将剩余栈顶牌移到托盘的操作
 */
enum class UndoActionType {
    NONE,            ///< 未定义操作
    CARD_MATCHED,    ///< 卡牌匹配到托盘
    STACK_TO_TRAY    ///< 剩余栈推到托盘
};

/**
 * @class UndoAction
 * @brief 表示一次可撤销的操作，包括类型、涉及的卡牌 ID 及其原始位置。
 *
 * 每当游戏状态发生改变（如卡牌匹配或从剩余栈移动），
 * 都应创建一个 UndoAction 并交给 UndoManager 记录，
 * 以便用户点击“撤销”时能够恢复到之前的状态。
 */
class UndoAction {
public:
    /**
     * @brief 构造函数
     * @param type    操作类型
     * @param cardId  受影响的卡牌唯一 ID
     * @param position 操作发生前该卡牌的位置
     */
    UndoAction(UndoActionType type, int cardId, const Vec2& position);

    /**
     * @brief 获取操作类型
     * @return UndoActionType 枚举值
     */
    UndoActionType getType() const;

    /**
     * @brief 获取受影响卡牌的 ID
     * @return 卡牌唯一 ID
     */
    int getCardId() const;

    /**
     * @brief 获取操作发生前卡牌的位置
     * @return 卡牌原始位置 (Vec2)
     */
    const Vec2& getPosition() const;

private:
    UndoActionType _type;     ///< 操作类型
    int            _cardId;   ///< 受影响卡牌的 ID
    Vec2           _position; ///< 操作前卡牌的位置
};

#endif // UNDOACTION_H
