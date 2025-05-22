#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include "cocos2d.h"
#include <map>
#include <memory>
#include "models/CardModel.h"
#include "models/GameModel.h"
USING_NS_CC;

class CardView;

class GameView : public cocos2d::Layer
{
public:
    // 创建函数
    static GameView* create(const std::shared_ptr<GameModel>& model);
    static std::shared_ptr<GameView> createShared(const std::shared_ptr<GameModel>& model);

    virtual bool init(const std::shared_ptr<GameModel>& model);

    // 点击回调设置
    void setCardClickCallback(const std::function<void(int)>& cb) { _cardClickCallback = cb; }
    void setUndoClickCallback(const std::function<void()>& cb) { _undoClickCallback = cb; }

    // 刷新整张界面
    void updateView();

    //访问接口
    const std::map<int, CardView*>& getplayfieldViews() { return _playfieldViews; }
    const std::map<int, CardView*>& getstockViews() { return _stockViews; }
    CardView*& gettrayTopView() { return _trayTopView; }
    const std::map<int, CardView*>& gettrayHistoryViews() { return  _trayHistoryViews; }

    // 获取卡牌视图
    static CardView* getCardViewById(int cardId);

    // 常量：顶部牌栈和剩余牌栈的位置
    static const Vec2 kTrayTopPosition;  // 顶部牌栈绝对坐标
    static const Vec2 kStockOrigin;      // 剩余牌栈绝对坐标

    // 播放移动动画
    void playMoveToAnimation(int cardId);

protected:
    // UI 构建
    void createUI();
    void createBackground();
    void createPlayfield();
    void createStockArea();   // 剩余牌区
    void createTrayArea();    // 顶部牌区
    void createUndoButton();

    // 分段刷新
    void updatePlayfieldCards();
    void updateStockCards();
    void updateTrayTopCard();
    void updateTrayHistory(); // 用于撤销动画恢复的历史卡牌

    // 撤销按钮响应
    void onUndoButtonClicked(Ref*);

private:
    std::shared_ptr<GameModel> _gameModel;

    // 渲染层级节点
    Node* _playfieldNode;
    Node* _stockNode;
    Node* _trayNode;
    Node* _overlayNode;     // 动画覆盖用，最上层节点

    Menu* _ui;            // ui界面

    // CardView 缓存
    static std::map<int, CardView*> _playfieldViews;
    static std::map<int, CardView*> _stockViews;
    static CardView* _trayTopView;
    static std::map<int, CardView*> _trayHistoryViews;

    std::function<void(int)> _cardClickCallback;
    std::function<void()> _undoClickCallback;
};

#endif
