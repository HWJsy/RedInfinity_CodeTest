#pragma once
#include <memory>
#include "../models/LevelConfig.h"
#include "utils/ResourcePath.h"

namespace config {
    class LevelConfigLoader {
    public:
        static std::shared_ptr<LevelConfig> loadLevelConfig(int levelId);
    };
}