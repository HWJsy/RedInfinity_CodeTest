#pragma once
#include <memory>
#include "../models/LevelConfig.h"
#include "utils/ResourcePath.h"

namespace config {

    /**
     * @class LevelConfigLoader
     * @brief 负责加载关卡配置文件的类
     *
     * 该类用于读取存储在JSON文件中的关卡配置信息，
     * 并解析为LevelConfig对象，供游戏逻辑使用。
     */
    class LevelConfigLoader {
    public:
        /**
         * @brief 根据关卡ID加载关卡配置
         * @param levelId 关卡编号
         * @return 关卡配置对象的共享指针，失败返回nullptr
         */
        static std::shared_ptr<LevelConfig> loadLevelConfig(int levelId);

    private:
        /**
         * @brief 解析Playfield字段，加载主牌区卡牌配置
         * @param doc JSON文档对象
         * @param config 目标LevelConfig对象
         */
        static void parsePlayfield(const rapidjson::Document& doc, std::shared_ptr<LevelConfig>& config);

        /**
         * @brief 解析Stack字段，加载备用牌堆卡牌配置
         * @param doc JSON文档对象
         * @param config 目标LevelConfig对象
         */
        static void parseStack(const rapidjson::Document& doc, std::shared_ptr<LevelConfig>& config);
    };

} // namespace config
