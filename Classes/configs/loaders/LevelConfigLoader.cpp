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

        CCLOG("Level config loaded: %s", content.c_str()); // 打印JSON内容用于调试

        Document doc;
        doc.Parse(content.c_str());

        if (doc.HasParseError()) {
            CCLOGERROR("Level config parse error: %s", filePath.c_str());
            return nullptr;
        }

        // 解析Playfield和Stack字段
        parsePlayfield(doc, config);
        parseStack(doc, config);

        return config;
    }

    void LevelConfigLoader::parsePlayfield(const Document& doc, std::shared_ptr<LevelConfig>& config) {
        if (doc.HasMember("Playfield") && doc["Playfield"].IsArray()) {
            const rapidjson::Value& playfieldArr = doc["Playfield"];
            for (SizeType i = 0; i < playfieldArr.Size(); ++i) {
                const rapidjson::Value& cardObj = playfieldArr[i];
                CardConfig cfg;
                cfg.face = cardObj["CardFace"].GetInt();
                cfg.suit = cardObj["CardSuit"].GetInt();

                cfg.pos.x = cardObj["Position"]["x"].GetFloat() - CardView::cardW;
                cfg.pos.y = cardObj["Position"]["y"].GetFloat() - CardView::cardH;

                config->addPlayfieldCard(cfg);
            }
        }
    }

    void LevelConfigLoader::parseStack(const Document& doc, std::shared_ptr<LevelConfig>& config) {
        if (doc.HasMember("Stack") && doc["Stack"].IsArray()) {
            const rapidjson::Value& stackArr = doc["Stack"];
            for (SizeType i = 0; i < stackArr.Size(); ++i) {
                const rapidjson::Value& cardObj = stackArr[i];
                CardConfig cfg;
                cfg.face = cardObj["CardFace"].GetInt();
                cfg.suit = cardObj["CardSuit"].GetInt();
                cfg.pos = Vec2::ZERO; // 备用牌堆位置由模型决定
                config->addStockCard(cfg);
            }
        }
    }

} // namespace config
