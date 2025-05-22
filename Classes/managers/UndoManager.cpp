#include "UndoManager.h"
#include "controllers/GameController.h"

UndoManager::UndoManager()
{
}

UndoManager::~UndoManager()
{
}

std::shared_ptr<UndoManager> UndoManager::create()
{
    return std::make_shared<UndoManager>();
}

void UndoManager::init()
{
    _undoStack.clear();
}

void UndoManager::recordAction(const std::shared_ptr<UndoAction>& action)
{
    _undoStack.push_back(action);
}

std::shared_ptr<UndoAction> UndoManager::undo()
{
    if (_undoStack.empty()) {
        return nullptr;
    }

    // 获取最后一个操作
    auto action = _undoStack.back();
    _undoStack.pop_back();

    return action;
}

bool UndoManager::canUndo() const
{
    return !_undoStack.empty();
}
