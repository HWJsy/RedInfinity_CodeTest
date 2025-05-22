#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include "cocos2d.h"
#include <map>
#include <memory>
#include <functional>
#include "models/CardModel.h"
#include "models/GameModel.h"

USING_NS_CC;

class CardView;

/**
 * @class GameView
 * @brief 游戏主视图层，负责卡牌界面的显示与交互处理。
 *
 * GameView 根据底层 GameModel 提供的卡牌数据，构建和维护游戏界面中
 * 不同区域（牌区、牌堆、托盘等）中卡牌的视图。支持点击事件和撤销操作。
 *
 * 主要职责：
 * - 创建并布局各游戏区域的 UI 组件
 * - 根据模型数据刷新视图
 * - 管理卡牌视图的缓存，方便快速更新和动画播放
 * - 提供卡牌点击和撤销按钮的回调接口
 */
class GameView : public cocos2d::Layer
{
public:
    /**
     * @brief 使用智能指针创建 GameView 对象
     * @param model 底层游戏模型对象的共享指针
     * @return GameView 指针（cocos2d::Ref 管理）
     */
    static GameView* create(const std::shared_ptr<GameModel>& model);

    /**
     * @brief 使用 std::shared_ptr 创建 GameView 对象
     * @param model 底层游戏模型对象的共享指针
     * @return std::shared_ptr<GameView>
     */
    static std::shared_ptr<GameView> createShared(const std::shared_ptr<GameModel>& model);

    /**
     * @brief 初始化函数，绑定模型并创建界面元素
     * @param model 底层游戏模型对象的共享指针
     * @return 初始化是否成功
     */
    virtual bool init(const std::shared_ptr<GameModel>& model);

    /**
     * @brief 设置卡牌点击回调函数
     * @param cb 回调函数，参数为被点击卡牌的 ID
     */
    void setCardClickCallback(const std::function<void(int)>& cb);

    /**
     * @brief 设置撤销按钮点击回调函数
     * @param cb 无参回调函数
     */
    void setUndoClickCallback(const std::function<void()>& cb);

    /**
     * @brief 刷新整个游戏视图，包括所有卡牌区域
     */
    void updateView();

    /**
     * @brief 获取当前牌区卡牌视图映射
     * @return 牌区卡牌ID到CardView指针的映射（不允许修改）
     */
    const std::map<int, CardView*>& getPlayfieldViews() const;

    /**
     * @brief 获取当前剩余牌堆卡牌视图映射
     * @return 剩余牌堆卡牌ID到CardView指针的映射（不允许修改）
     */
    const std::map<int, CardView*>& getStockViews() const;

    /**
     * @brief 获取当前托盘顶牌视图
     * @return 托盘顶牌 CardView 指针的引用
     */
    CardView*& getTrayTopView();

    /**
     * @brief 获取托盘历史卡牌视图映射
     * @return 托盘历史卡牌ID到CardView指针的映射（不允许修改）
     */
    const std::map<int, CardView*>& getTrayHistoryViews() const;

    /**
     * @brief 根据卡牌ID获取对应的CardView对象指针
     * @param cardId 卡牌唯一ID
     * @return 对应卡牌的 CardView 指针，找不到返回 nullptr
     */
    static CardView* getCardViewById(int cardId);

    /**
     * @brief 播放卡牌移动到托盘顶的位置动画
     * @param cardId 需要移动的卡牌ID
     */
    void playMoveToAnimation(int cardId);

    /** 常量：托盘顶牌位置（绝对坐标） */
    static const Vec2 kTrayTopPosition;

    /** 常量：剩余牌堆起始位置（绝对坐标） */
    static const Vec2 kStockOrigin;

protected:
    /**
     * @brief 创建游戏界面 UI 布局，包括背景、各卡牌区域和按钮
     * 分解函数确保单一职责
     */
    void createUI();
    void createBackground();
    void createPlayfield();
    void createStockArea();
    void createTrayArea();
    void createUndoButton();

    /**
     * @brief 分段刷新各个区域卡牌视图，供 updateView 调用
     */
    void updatePlayfieldCards();
    void updateStockCards();
    void updateTrayTopCard();
    void updateTrayHistory();

    /**
     * @brief 撤销按钮点击事件响应
     * @param sender 按钮对象指针
     */
    void onUndoButtonClicked(Ref* sender);

private:
    std::shared_ptr<GameModel> _gameModel;  ///< 底层游戏数据模型

    Node* _playfieldNode;    ///< 牌区节点，用于承载牌区卡牌视图
    Node* _stockNode;        ///< 剩余牌堆节点
    Node* _trayNode;         ///< 托盘节点（顶牌和历史牌）
    Node* _overlayNode;      ///< 动画覆盖层，置顶显示动画过程中的卡牌

    Menu* _ui;               ///< UI 菜单节点，包含撤销按钮等

    // 各区域卡牌视图缓存，方便快速查找和更新
    static std::map<int, CardView*> _playfieldViews;
    static std::map<int, CardView*> _stockViews;
    static CardView* _trayTopView;
    static std::map<int, CardView*> _trayHistoryViews;

    // 交互回调函数
    std::function<void(int)> _cardClickCallback;
    std::function<void()> _undoClickCallback;
};

#endif // GAMEVIEW_H
