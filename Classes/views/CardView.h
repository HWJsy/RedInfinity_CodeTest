#ifndef CARDVIEW_H
#define CARDVIEW_H

#include "cocos2d.h"
#include "models/CardModel.h"
#include "GameView.h"
class CardView : public cocos2d::Node
{
public:
    // 常量声明
    static const float cardW;
    static const float cardH;
    static const float suitW;
    static const float suitH;
    static const float smallW;
    static const float smallH;
    static const float bigW;
    static const float bigH;

    // 创建函数
    static CardView* create(const std::shared_ptr<CardModel>& model);

    // 初始化函数
    virtual bool init(const std::shared_ptr<CardModel>& model);

    // 更新视图状态
    void updateView();

    // 设置点击回调
    void setClickCallback(const std::function<void(int cardId)>& callback);

    // 获取卡牌ID
    int getCardId() const { return _cardId; }

protected:
    CardView();
    virtual ~CardView();

    // 触摸事件处理
    bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
    void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
    void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);

private:
    int _cardId;                              // 卡牌ID
    std::shared_ptr<CardModel> _cardModel;    // 卡牌模型
    cocos2d::Vec2 _originalPosition;          // 原始位置
    std::function<void(int)> _clickCallback;  // 点击回调
};

#endif // CARDVIEW_H
