#ifndef UNDOMANAGER_H
#define UNDOMANAGER_H

#include <memory>
#include <vector>
#include "models/UndoAction.h"

/**
 * @class UndoManager
 * @brief ������Ϸ�еĳ���������ά��һ������ջ��֧�ֶ�λ��ˡ�
 *
 * ���ฺ��
 * - ��¼ÿһ�ζ���Ϸ״̬�Ŀɻ��˲���
 * - �ṩ���ˣ�undo�����ܣ����Ƚ������˳��ָ�����
 * - ����Ƿ��пɻ��˵Ĳ���
 *
 * ʹ�ó�����
 * �� GameController ��ʹ�ã���ÿ��״̬���ǰ���� recordAction()��
 * ���û������������ʱ���� undo() �����ݷ��ص� UndoAction �ָ�״̬��
 */
class UndoManager {
public:
    /**
     * @brief ��̬���췽��
     * @return UndoManager �Ĺ���ָ��
     */
    static std::shared_ptr<UndoManager> create();

    /**
     * @brief ��ʼ����������������еĲ�����¼
     */
    void init();

    /**
     * @brief ��¼һ���ɻ��˲���
     * @param action Ҫ��¼�ĳ�������
     */
    void recordAction(const std::shared_ptr<UndoAction>& action);

    /**
     * @brief ִ��һ�λ��˲���
     * @return ���һ�μ�¼�� UndoAction�����޿ɻ��˲����򷵻� nullptr
     */
    std::shared_ptr<UndoAction> undo();

    /**
     * @brief ����Ƿ��пɻ��˵Ĳ���
     * @return �пɻ��˲������� true�����򷵻� false
     */
    bool canUndo() const;

    UndoManager();
    virtual ~UndoManager();

private:
    std::vector<std::shared_ptr<UndoAction>> _undoStack;  ///< ��������ջ������ȳ�
};

#endif // UNDOMANAGER_H
