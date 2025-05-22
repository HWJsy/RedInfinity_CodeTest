#ifndef GAMEMODELFROMLEVELGENERATOR_H
#define GAMEMODELFROMLEVELGENERATOR_H

#include "models/GameModel.h"
#include "configs/models/LevelConfig.h"

class GameModelFromLevelGenerator
{
public:
    GameModelFromLevelGenerator();
    virtual ~GameModelFromLevelGenerator();

    // �ӹؿ�����������Ϸģ��
    static GameModel* generateGameModel(int levelId);
};

#endif