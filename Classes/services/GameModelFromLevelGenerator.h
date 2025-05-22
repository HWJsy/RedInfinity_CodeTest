#ifndef GAMEMODELFROMLEVELGENERATOR_H
#define GAMEMODELFROMLEVELGENERATOR_H

#include "models/GameModel.h"
#include "configs/models/LevelConfig.h"

/**
 * @class GameModelFromLevelGenerator
 * @brief ���ݹؿ��������� GameModel �Ĺ�����
 *
 * �������ڴ� JSON ��ʽ�Ĺؿ������ļ��ж�ȡ���Ʋ������ݣ�
 * ���첢��ʼ�� GameModel ʵ����������������ͼʹ�á�
 */
class GameModelFromLevelGenerator {
public:
    GameModelFromLevelGenerator();
    virtual ~GameModelFromLevelGenerator();

    /**
     * @brief ����ָ���ؿ� ID ��Ӧ�� GameModel ʵ��
     * @param levelId �ؿ����
     * @return �ɹ�ʱ���س�ʼ����ɵ� GameModel ָ�룻���򷵻� nullptr
     */
    static GameModel* generateGameModel(int levelId);
};

#endif // GAMEMODELFROMLEVELGENERATOR_H
