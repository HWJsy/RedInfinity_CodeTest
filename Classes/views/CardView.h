#ifndef CARDVIEW_H
#define CARDVIEW_H

#include "cocos2d.h"
#include "models/CardModel.h"
#include <functional>

/**
 * @class CardView
 * @brief 负责展示单张卡牌的视图层，基于CardModel的数据绘制卡牌外观并处理用户交互事件。
 *
 * CardView用于显示卡牌图案、花色、数字等元素，并支持点击事件回调。
 * 该类继承自cocos2d::Node，支持触摸响应和位置变换。
 */
class CardView : public cocos2d::Node
{
public:

    // 常量声明
    /** 卡牌背景宽度 */
    static const float cardW;
    /** 卡牌背景高度 */
    static const float cardH;
    /** 花色图标宽度 */
    static const float suitW;
    /** 花色图标高度 */
    static const float suitH;
    /** 小数字宽度 */
    static const float smallW;
    /** 小数字高度 */
    static const float smallH;
    /** 大数字宽度 */
    static const float bigW;
    /** 大数字高度 */
    static const float bigH;

public:
    /**
     * @brief 使用CardModel创建CardView实例
     * @param model 卡牌数据模型的智能指针
     * @return CardView实例指针，失败返回nullptr
     */
    static CardView* create(const std::shared_ptr<CardModel>& model);

    /**
     * @brief 初始化CardView
     * @param model 卡牌数据模型智能指针
     * @return 初始化是否成功
     */
    virtual bool init(const std::shared_ptr<CardModel>& model);

    /**
     * @brief 根据模型更新卡牌视图显示
     */
    void updateView();

    /**
     * @brief 设置卡牌被点击时的回调函数
     * @param callback 点击事件回调，传入卡牌ID
     */
    void setClickCallback(const std::function<void(int)>& callback);

    /**
     * @brief 获取当前卡牌ID
     * @return 卡牌ID整数
     */
    int getCardId() const { return _cardId; }

protected:
    CardView();
    virtual ~CardView();

    /**
     * @brief 触摸开始事件处理
     * @param touch 触摸对象
     * @param event 事件对象
     * @return 是否吞噬事件
     */
    bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);

    /**
     * @brief 触摸移动事件处理（当前为空）
     * @param touch 触摸对象
     * @param event 事件对象
     */
    void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);

    /**
     * @brief 触摸结束事件处理
     * @param touch 触摸对象
     * @param event 事件对象
     */
    void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);

    /**
     * @brief 绘制卡牌背景
     * @return 背景精灵指针，失败返回nullptr
     */
    cocos2d::Sprite* drawBackground();

    /**
     * @brief 绘制花色图标
     * @param parent 背景节点，通常是卡牌背景sprite
     */
    void drawSuit(cocos2d::Sprite* parent);

    /**
     * @brief 绘制数字（大数字或小数字）
     * @param parent 父节点，一般为背景精灵
     * @param color 字体颜色字符串，如"red"或"black"
     * @param numberStr 数字字符串，如"A","10"等
     * @param isBig 是否为大数字，true为大数字，false为小数字
     */
    void drawNumber(cocos2d::Sprite* parent, const std::string& color, const std::string& numberStr, bool isBig);

private:
    int _cardId;                                         ///< 卡牌ID
    std::shared_ptr<CardModel> _cardModel;              ///< 卡牌数据模型
    cocos2d::Vec2 _originalPosition;                     ///< 卡牌初始位置，用于还原
    std::function<void(int)> _clickCallback;             ///< 点击事件回调函数
};

#endif // CARDVIEW_H
