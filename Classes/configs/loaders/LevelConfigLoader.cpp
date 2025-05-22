#include "LevelConfigLoader.h"
#include "cocos2d.h"
#include "json/document.h"
#include "json/rapidjson.h"
#include "views/CardView.h"
using namespace cocos2d;
using namespace rapidjson;

namespace config {
    std::shared_ptr<LevelConfig> LevelConfigLoader::loadLevelConfig(int levelId) {
        auto config = std::make_shared<LevelConfig>();
        std::string filePath = ResourcePath::getLevelConfigPath(levelId);

        std::string content = FileUtils::getInstance()->getStringFromFile(filePath);

        if (content.empty()) {
            CCLOGERROR("Level config file not found or empty: %s", filePath.c_str());
            return nullptr;
        }

        CCLOG("Level config loaded: %s", content.c_str()); //打印 JSON ,内容用于调试

        Document doc;
        doc.Parse(content.c_str());
        
        if (doc.HasParseError()) {
            CCLOGERROR("Level config parse error: %s", filePath.c_str());
            return nullptr;
        }

        // 解析主牌区卡牌
        if (doc.HasMember("Playfield") && doc["Playfield"].IsArray()) {
            const rapidjson::Value& playfieldArr = doc["Playfield"];
            for (SizeType i = 0; i < playfieldArr.Size(); ++i) {
                const rapidjson::Value& cardObj = playfieldArr[i];
                CardConfig cfg;
                //获取卡面信息
                cfg.face = cardObj["CardFace"].GetInt();
                cfg.suit = cardObj["CardSuit"].GetInt();

                // 获取坐标
                cfg.pos.x = cardObj["Position"]["x"].GetFloat() - CardView::cardW;
                cfg.pos.y = cardObj["Position"]["y"].GetFloat() - CardView::cardH;

                config->addPlayfieldCard(cfg);
            }
        }

        // 解析备用牌堆
        if (doc.HasMember("Stack") && doc["Stack"].IsArray()) {
            const rapidjson::Value& stackArr = doc["Stack"];
            for (SizeType i = 0; i < stackArr.Size(); ++i) {
                const rapidjson::Value& cardObj = stackArr[i];
                CardConfig cfg;
                cfg.face = cardObj["CardFace"].GetInt();
                cfg.suit = cardObj["CardSuit"].GetInt();
                cfg.pos = Vec2::ZERO; // 备用牌堆初始位置由模型处理
                config->addStockCard(cfg);
            }
        }

        return config;
    }
}