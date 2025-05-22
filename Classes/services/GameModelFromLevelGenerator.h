#ifndef GAMEMODELFROMLEVELGENERATOR_H
#define GAMEMODELFROMLEVELGENERATOR_H

#include "models/GameModel.h"
#include "configs/models/LevelConfig.h"

/**
 * @class GameModelFromLevelGenerator
 * @brief 根据关卡配置生成 GameModel 的工具类
 *
 * 该类用于从 JSON 格式的关卡配置文件中读取卡牌布局数据，
 * 构造并初始化 GameModel 实例，供控制器和视图使用。
 */
class GameModelFromLevelGenerator {
public:
    GameModelFromLevelGenerator();
    virtual ~GameModelFromLevelGenerator();

    /**
     * @brief 生成指定关卡 ID 对应的 GameModel 实例
     * @param levelId 关卡编号
     * @return 成功时返回初始化完成的 GameModel 指针；否则返回 nullptr
     */
    static GameModel* generateGameModel(int levelId);
};

#endif // GAMEMODELFROMLEVELGENERATOR_H
