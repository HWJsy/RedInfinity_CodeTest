#ifndef UNDOMANAGER_H
#define UNDOMANAGER_H

#include <memory>
#include <vector>
#include "models/UndoAction.h"

/**
 * @class UndoManager
 * @brief 管理游戏中的撤销操作，维护一个操作栈以支持多次回退。
 *
 * 该类负责：
 * - 记录每一次对游戏状态的可回退操作
 * - 提供回退（undo）功能，按先进后出的顺序恢复操作
 * - 检查是否还有可回退的操作
 *
 * 使用场景：
 * 在 GameController 中使用，在每次状态变更前调用 recordAction()，
 * 在用户点击“撤销”时调用 undo() 并根据返回的 UndoAction 恢复状态。
 */
class UndoManager {
public:
    /**
     * @brief 静态构造方法
     * @return UndoManager 的共享指针
     */
    static std::shared_ptr<UndoManager> create();

    /**
     * @brief 初始化管理器，清空已有的操作记录
     */
    void init();

    /**
     * @brief 记录一条可回退操作
     * @param action 要记录的撤销动作
     */
    void recordAction(const std::shared_ptr<UndoAction>& action);

    /**
     * @brief 执行一次回退操作
     * @return 最后一次记录的 UndoAction，若无可回退操作则返回 nullptr
     */
    std::shared_ptr<UndoAction> undo();

    /**
     * @brief 检查是否还有可回退的操作
     * @return 有可回退操作返回 true，否则返回 false
     */
    bool canUndo() const;

    UndoManager();
    virtual ~UndoManager();

private:
    std::vector<std::shared_ptr<UndoAction>> _undoStack;  ///< 撤销操作栈，后进先出
};

#endif // UNDOMANAGER_H
