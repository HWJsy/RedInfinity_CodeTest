#include "GameModelFromLevelGenerator.h"
#include "models/CardModel.h"
#include "configs/loaders/LevelConfigLoader.h"  // ?? 新增
USING_NS_CC;

GameModel* GameModelFromLevelGenerator::generateGameModel(int levelId)
{
    // 1. 通过 Loader 读取并解析 JSON
    auto levelConfig = config::LevelConfigLoader::loadLevelConfig(levelId);
    if (!levelConfig) {
        CCLOGERROR("GameModelGenerator: failed to load LevelConfig for level %d", levelId);
        return nullptr;
    }

    // 2. 创建并初始化 GameModel
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

    // 3. 填充 Playfield 区
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

    // 4. 填充 Stock 区
    for (const auto& cardCfg : levelConfig->getStockCards()) {
        auto card = std::make_shared<CardModel>(
            cardId++,
            static_cast<CardFaceType>(cardCfg.face),
            static_cast<CardSuitType>(cardCfg.suit)
        );
        // 位置由 Controller 布局
        gameModel->addCardToStock(card);
    }

    // 5. 从 Stock 抽一张生成 Tray 顶牌
    if (!gameModel->stockToTray()) {
        CCLOGERROR("GameModelGenerator: failed to draw initial card from stock");
        delete gameModel;
        return nullptr;
    }

    return gameModel;
}
