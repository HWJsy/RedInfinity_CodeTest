#include "LevelConfig.h"

LevelConfig::LevelConfig()
{
}

LevelConfig::~LevelConfig()
{
}

bool LevelConfig::loadFromFile(const std::string& filePath)
{
    // ��ȡ�ļ�����
    std::string content = FileUtils::getInstance()->getStringFromFile(filePath);
    if (content.empty()) {
        CCLOGERROR("Failed to load level config: %s", filePath.c_str());
        return false;
    }

    // ����JSON
    rapidjson::Document doc;
    doc.Parse(content.c_str());

    if (doc.HasParseError()) {
        CCLOGERROR("JSON parse error: %s", doc.GetParseError());
        return false;
    }

    // �������ƶ�����
    if (doc.HasMember("Playfield") && doc["Playfield"].IsArray()) {
        const rapidjson::Value& playfieldArray = doc["Playfield"];
        for (rapidjson::SizeType i = 0; i < playfieldArray.Size(); i++) {
            const rapidjson::Value& cardObj = playfieldArray[i];

            CardConfig cardCfg;
            cardCfg.face = cardObj["CardFace"].GetInt();
            cardCfg.suit = cardObj["CardSuit"].GetInt();

            const rapidjson::Value& posObj = cardObj["Position"];
            cardCfg.pos.x = posObj["x"].GetFloat();
            cardCfg.pos.y = posObj["y"].GetFloat();

            _playfieldCards.push_back(cardCfg);
        }
    }

    // ���������ƶ�����
    if (doc.HasMember("Stack") && doc["Stack"].IsArray()) {
        const rapidjson::Value& stackArray = doc["Stack"];
        for (rapidjson::SizeType i = 0; i < stackArray.Size(); i++) {
            const rapidjson::Value& cardObj = stackArray[i];

            CardConfig cardCfg;
            cardCfg.face = cardObj["CardFace"].GetInt();
            cardCfg.suit = cardObj["CardSuit"].GetInt();

            // �����ƶѳ�ʼλ�ÿ��Ժ��ԣ���Ϸ���Զ��ڷ�
            cardCfg.pos = cocos2d::Vec2::ZERO;

            _stockCards.push_back(cardCfg);
        }
    }

    return true;
}

void LevelConfig::addPlayfieldCard(const CardConfig& card)
{
    _playfieldCards.push_back(card);
}

void LevelConfig::addStockCard(const CardConfig& card)
{
    _stockCards.push_back(card);
}