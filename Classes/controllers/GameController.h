#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <memory>
#include "models/GameModel.h"
#include "views/GameView.h"
#include "managers/UndoManager.h"

/**
 * @class GameController
 * @brief 游戏主控制器，负责协调 Model、View 和撤销管理逻辑。
 *
 * GameController 负责：
 * - 根据关卡 ID 初始化并启动游戏
 * - 处理用户点击牌和撤销操作
 * - 与 GameModel 交互以更新游戏状态
 * - 驱动 GameView 播放相应动画
 * - 记录与回放游戏日志（调试用）
 *
 * 使用场景：
 * 在应用启动后，通过 create() 构造并调用 init()，然后调用 startGame()。
 */
class GameController {
public:
    /**
     * @brief 静态构造方法
     * @param model 已创建好的游戏数据模型
     * @return GameController 的共享指针
     */
    static std::shared_ptr<GameController> create(const std::shared_ptr<GameModel>& model);

    /**
     * @brief 初始化控制器，设置 View 回调
     * @param view 游戏界面视图
     * @return 初始化成功返回 true
     */
    bool init(const std::shared_ptr<GameView>& view);

    /**
     * @brief 启动游戏，加载关卡并刷新界面
     * @param levelId 关卡编号
     */
    void startGame(int levelId);

    /**
     * @brief 处理用户点击某张牌的逻辑
     * @param cardId 被点击卡牌的唯一 ID
     */
    void handleCardClick(int cardId);

    /**
     * @brief 处理用户点击“撤销”按钮的逻辑
     */
    void handleUndoClick();

    /**
     * @brief 输出当前游戏状态到日志（调试用）
     */
    void logGameState() const;

    virtual ~GameController();

    /**
     * @brief 构造函数，需要传入数据模型
     * @param model 游戏数据模型
     */
    GameController(const std::shared_ptr<GameModel>& model);

protected:
    /**
     * @brief 检查某张牌是否可以移动到托盘
     * @param cardId 卡牌 ID
     * @return 可以移动返回 true
     */
    bool _canMatchToTray(int cardId) const;

    /**
     * @brief 将卡牌从主牌堆移动到托盘，并记录撤销信息
     * @param cardId 卡牌 ID
     */
    void _matchCardToTray(int cardId);

    /**
     * @brief 判断某张牌是否位于主牌堆顶层
     * @param cardId 卡牌 ID
     * @return 在顶层返回 true
     */
    bool _isTopPlayfieldCard(int cardId) const;

private:
    std::shared_ptr<UndoManager> _undoManager;  ///< 撤销操作管理器
    std::shared_ptr<GameModel>   _gameModel;    ///< 游戏数据模型
    std::shared_ptr<GameView>    _gameView;     ///< 游戏界面视图
};

#endif // GAMECONTROLLER_H
