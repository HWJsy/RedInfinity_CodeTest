#ifndef UNDOACTION_H
#define UNDOACTION_H

#include "cocos2d.h"

USING_NS_CC;

/**
 * @enum UndoActionType
 * @brief ����֧�ֵĳ�����������
 *
 * NONE              - �޲���
 * CARD_MATCHED      - ����ƥ�䵽���̵Ĳ���
 * STACK_TO_TRAY     - ��ʣ��ջ�����Ƶ����̵Ĳ���
 */
enum class UndoActionType {
    NONE,            ///< δ�������
    CARD_MATCHED,    ///< ����ƥ�䵽����
    STACK_TO_TRAY    ///< ʣ��ջ�Ƶ�����
};

/**
 * @class UndoAction
 * @brief ��ʾһ�οɳ����Ĳ������������͡��漰�Ŀ��� ID ����ԭʼλ�á�
 *
 * ÿ����Ϸ״̬�����ı䣨�翨��ƥ����ʣ��ջ�ƶ�����
 * ��Ӧ����һ�� UndoAction ������ UndoManager ��¼��
 * �Ա��û������������ʱ�ܹ��ָ���֮ǰ��״̬��
 */
class UndoAction {
public:
    /**
     * @brief ���캯��
     * @param type    ��������
     * @param cardId  ��Ӱ��Ŀ���Ψһ ID
     * @param position ��������ǰ�ÿ��Ƶ�λ��
     */
    UndoAction(UndoActionType type, int cardId, const Vec2& position);

    /**
     * @brief ��ȡ��������
     * @return UndoActionType ö��ֵ
     */
    UndoActionType getType() const;

    /**
     * @brief ��ȡ��Ӱ�쿨�Ƶ� ID
     * @return ����Ψһ ID
     */
    int getCardId() const;

    /**
     * @brief ��ȡ��������ǰ���Ƶ�λ��
     * @return ����ԭʼλ�� (Vec2)
     */
    const Vec2& getPosition() const;

private:
    UndoActionType _type;     ///< ��������
    int            _cardId;   ///< ��Ӱ�쿨�Ƶ� ID
    Vec2           _position; ///< ����ǰ���Ƶ�λ��
};

#endif // UNDOACTION_H
