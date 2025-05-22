#ifndef LEVELCONFIG_H
#define LEVELCONFIG_H

#include "cocos2d.h"
#include <vector>
#include "json/document.h"
#include "json/stringbuffer.h"
#include "json/writer.h"

USING_NS_CC;
struct CardConfig
{
    int face;           // 牌面数值
    int suit;           // 花色
    cocos2d::Vec2 pos;  // 位置
};

class LevelConfig
{
public:
    LevelConfig();
    virtual ~LevelConfig();

    // 从文件加载配置
    bool loadFromFile(const std::string& filePath);

    // 获取主牌堆配置
    const std::vector<CardConfig>& getPlayfieldCards() const { return _playfieldCards; }

    // 获取备用牌堆配置
    const std::vector<CardConfig>& getStockCards() const { return _stockCards; }

    //添加主牌堆卡牌配置
    void addPlayfieldCard(const CardConfig& card);

    //添加备用牌堆卡牌配置
    void addStockCard(const CardConfig& card);
private:
    std::vector<CardConfig> _playfieldCards; // 主牌堆配置
    std::vector<CardConfig> _stockCards;     // 备用牌堆配置
};

#endif