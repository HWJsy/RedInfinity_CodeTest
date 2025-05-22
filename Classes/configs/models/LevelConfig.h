#ifndef LEVELCONFIG_H
#define LEVELCONFIG_H

#include "cocos2d.h"
#include <vector>
#include "json/document.h"

/**
 * @class CardConfig
 * @brief 卡牌的基本配置结构体，包含牌面值、花色和位置信息。
 */
struct CardConfig {
    int face;           ///< 牌面数值
    int suit;           ///< 花色
    cocos2d::Vec2 pos;  ///< 卡牌在场景中的位置
};

/**
 * @class LevelConfig
 * @brief 表示一个关卡的卡牌配置，包括主牌堆和备用牌堆。
 *
 * 本类负责存储和解析指定关卡的卡牌布局，用于初始化游戏模型。
 * 支持从 JSON 文件加载配置。
 */
class LevelConfig {
public:
    LevelConfig();
    virtual ~LevelConfig();

    /**
     * @brief 从 JSON 文件加载关卡配置。
     * @param filePath 文件路径
     * @return 加载成功返回 true，失败返回 false
     */
    bool loadFromFile(const std::string& filePath);

    /**
     * @brief 获取主牌堆的卡牌配置。
     * @return 主牌堆卡牌列表
     */
    const std::vector<CardConfig>& getPlayfieldCards() const { return _playfieldCards; }

    /**
     * @brief 获取备用牌堆的卡牌配置。
     * @return 备用牌堆卡牌列表
     */
    const std::vector<CardConfig>& getStockCards() const { return _stockCards; }

    /**
     * @brief 添加一张主牌堆卡牌。
     * @param card 卡牌配置信息
     */
    void addPlayfieldCard(const CardConfig& card);

    /**
     * @brief 添加一张备用牌堆卡牌。
     * @param card 卡牌配置信息
     */
    void addStockCard(const CardConfig& card);

private:
    std::vector<CardConfig> _playfieldCards; ///< 主牌堆配置
    std::vector<CardConfig> _stockCards;     ///< 备用牌堆配置
};

#endif // LEVELCONFIG_H
