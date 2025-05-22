#ifndef CARDVIEW_H
#define CARDVIEW_H

#include "cocos2d.h"
#include "models/CardModel.h"
#include "GameView.h"
class CardView : public cocos2d::Node
{
public:
    // ��������
    static const float cardW;
    static const float cardH;
    static const float suitW;
    static const float suitH;
    static const float smallW;
    static const float smallH;
    static const float bigW;
    static const float bigH;

    // ��������
    static CardView* create(const std::shared_ptr<CardModel>& model);

    // ��ʼ������
    virtual bool init(const std::shared_ptr<CardModel>& model);

    // ������ͼ״̬
    void updateView();

    // ���õ���ص�
    void setClickCallback(const std::function<void(int cardId)>& callback);

    // ��ȡ����ID
    int getCardId() const { return _cardId; }

protected:
    CardView();
    virtual ~CardView();

    // �����¼�����
    bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
    void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
    void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);

private:
    int _cardId;                              // ����ID
    std::shared_ptr<CardModel> _cardModel;    // ����ģ��
    cocos2d::Vec2 _originalPosition;          // ԭʼλ��
    std::function<void(int)> _clickCallback;  // ����ص�
};

#endif // CARDVIEW_H
