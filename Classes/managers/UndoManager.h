#ifndef UNDOMANAGER_H
#define UNDOMANAGER_H

#include <memory>
#include <vector>
#include "models/UndoAction.h"

class UndoManager
{
public:
    // ��������
    static std::shared_ptr<UndoManager> create();

    // ��ʼ��
    void init();

    // ��¼����
    void recordAction(const std::shared_ptr<UndoAction>& action);

    // ִ�л���
    std::shared_ptr<UndoAction> undo();

    // ����Ƿ���Ի���
    bool canUndo() const;

    UndoManager();

    virtual ~UndoManager();
    
private:
    std::vector<std::shared_ptr<UndoAction>> _undoStack; // ���˲���ջ
};

#endif