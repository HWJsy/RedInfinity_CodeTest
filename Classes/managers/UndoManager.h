#ifndef UNDOMANAGER_H
#define UNDOMANAGER_H

#include <memory>
#include <vector>
#include "models/UndoAction.h"

class UndoManager
{
public:
    // 创建函数
    static std::shared_ptr<UndoManager> create();

    // 初始化
    void init();

    // 记录操作
    void recordAction(const std::shared_ptr<UndoAction>& action);

    // 执行回退
    std::shared_ptr<UndoAction> undo();

    // 检查是否可以回退
    bool canUndo() const;

    UndoManager();

    virtual ~UndoManager();
    
private:
    std::vector<std::shared_ptr<UndoAction>> _undoStack; // 回退操作栈
};

#endif