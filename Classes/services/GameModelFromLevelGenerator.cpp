#include "GameModelFromLevelGenerator.h"
#include "models/CardModel.h"
#include "configs/loaders/LevelConfigLoader.h"  // ?? ����
USING_NS_CC;

GameModel* GameModelFromLevelGenerator::generateGameModel(int levelId)
{
    // 1. ͨ�� Loader ��ȡ������ JSON
    auto levelConfig = config::LevelConfigLoader::loadLevelConfig(levelId);
    if (!levelConfig) {
        CCLOGERROR("GameModelGenerator: failed to load LevelConfig for level %d", levelId);
        return nullptr;
    }

    // 2. ��������ʼ�� GameModel
    auto gameModel = new (std::nothrow) GameModel();
    if (!gameModel) {
        CCLOGERROR("GameModelGenerator: allocation failed");
        return nullptr;
    }
    if (!gameModel->init()) {
        CCLOGERROR("GameModelGenerator: GameModel init failed");
        delete gameModel;
        return nullptr;
    }

    // 3. ��� Playfield ��
    int cardId = 0;
    for (const auto& cardCfg : levelConfig->getPlayfieldCards()) {
        auto card = std::make_shared<CardModel>(
            cardId++,
            static_cast<CardFaceType>(cardCfg.face),
            static_cast<CardSuitType>(cardCfg.suit)
        );
        card->setPosition(cardCfg.pos);
        gameModel->addCardToPlayfield(card);
        CCLOG("Adding playfield card id=%d pos=(%.1f,%.1f)", cardId, cardCfg.pos.x, cardCfg.pos.y);
    }

    // 4. ��� Stock ��
    for (const auto& cardCfg : levelConfig->getStockCards()) {
        auto card = std::make_shared<CardModel>(
            cardId++,
            static_cast<CardFaceType>(cardCfg.face),
            static_cast<CardSuitType>(cardCfg.suit)
        );
        // λ���� Controller ����
        gameModel->addCardToStock(card);
    }

    // 5. �� Stock ��һ������ Tray ����
    if (!gameModel->stockToTray()) {
        CCLOGERROR("GameModelGenerator: failed to draw initial card from stock");
        delete gameModel;
        return nullptr;
    }

    return gameModel;
}
