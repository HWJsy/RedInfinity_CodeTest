#ifndef GAMEMODELFROMLEVELGENERATOR_H
#define GAMEMODELFROMLEVELGENERATOR_H

#include "models/GameModel.h"
#include "configs/models/LevelConfig.h"

class GameModelFromLevelGenerator
{
public:
    GameModelFromLevelGenerator();
    virtual ~GameModelFromLevelGenerator();

    // 从关卡配置生成游戏模型
    static GameModel* generateGameModel(int levelId);
};

#endif