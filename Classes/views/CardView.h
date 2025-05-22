#ifndef CARDVIEW_H
#define CARDVIEW_H

#include "cocos2d.h"
#include "models/CardModel.h"
#include <functional>

/**
 * @class CardView
 * @brief ����չʾ���ſ��Ƶ���ͼ�㣬����CardModel�����ݻ��ƿ�����۲������û������¼���
 *
 * CardView������ʾ����ͼ������ɫ�����ֵ�Ԫ�أ���֧�ֵ���¼��ص���
 * ����̳���cocos2d::Node��֧�ִ�����Ӧ��λ�ñ任��
 */
class CardView : public cocos2d::Node
{
public:

    // ��������
    /** ���Ʊ������ */
    static const float cardW;
    /** ���Ʊ����߶� */
    static const float cardH;
    /** ��ɫͼ���� */
    static const float suitW;
    /** ��ɫͼ��߶� */
    static const float suitH;
    /** С���ֿ�� */
    static const float smallW;
    /** С���ָ߶� */
    static const float smallH;
    /** �����ֿ�� */
    static const float bigW;
    /** �����ָ߶� */
    static const float bigH;

public:
    /**
     * @brief ʹ��CardModel����CardViewʵ��
     * @param model ��������ģ�͵�����ָ��
     * @return CardViewʵ��ָ�룬ʧ�ܷ���nullptr
     */
    static CardView* create(const std::shared_ptr<CardModel>& model);

    /**
     * @brief ��ʼ��CardView
     * @param model ��������ģ������ָ��
     * @return ��ʼ���Ƿ�ɹ�
     */
    virtual bool init(const std::shared_ptr<CardModel>& model);

    /**
     * @brief ����ģ�͸��¿�����ͼ��ʾ
     */
    void updateView();

    /**
     * @brief ���ÿ��Ʊ����ʱ�Ļص�����
     * @param callback ����¼��ص������뿨��ID
     */
    void setClickCallback(const std::function<void(int)>& callback);

    /**
     * @brief ��ȡ��ǰ����ID
     * @return ����ID����
     */
    int getCardId() const { return _cardId; }

protected:
    CardView();
    virtual ~CardView();

    /**
     * @brief ������ʼ�¼�����
     * @param touch ��������
     * @param event �¼�����
     * @return �Ƿ������¼�
     */
    bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);

    /**
     * @brief �����ƶ��¼�������ǰΪ�գ�
     * @param touch ��������
     * @param event �¼�����
     */
    void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);

    /**
     * @brief ���������¼�����
     * @param touch ��������
     * @param event �¼�����
     */
    void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);

    /**
     * @brief ���ƿ��Ʊ���
     * @return ��������ָ�룬ʧ�ܷ���nullptr
     */
    cocos2d::Sprite* drawBackground();

    /**
     * @brief ���ƻ�ɫͼ��
     * @param parent �����ڵ㣬ͨ���ǿ��Ʊ���sprite
     */
    void drawSuit(cocos2d::Sprite* parent);

    /**
     * @brief �������֣������ֻ�С���֣�
     * @param parent ���ڵ㣬һ��Ϊ��������
     * @param color ������ɫ�ַ�������"red"��"black"
     * @param numberStr �����ַ�������"A","10"��
     * @param isBig �Ƿ�Ϊ�����֣�trueΪ�����֣�falseΪС����
     */
    void drawNumber(cocos2d::Sprite* parent, const std::string& color, const std::string& numberStr, bool isBig);

private:
    int _cardId;                                         ///< ����ID
    std::shared_ptr<CardModel> _cardModel;              ///< ��������ģ��
    cocos2d::Vec2 _originalPosition;                     ///< ���Ƴ�ʼλ�ã����ڻ�ԭ
    std::function<void(int)> _clickCallback;             ///< ����¼��ص�����
};

#endif // CARDVIEW_H
