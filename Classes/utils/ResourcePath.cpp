#include "ResourcePath.h"
#include "cocos2d.h"

USING_NS_CC;

std::string ResourcePath::getCardPath(const std::string& filename)
{
    return getResourceRootPath() + "res/" + filename;
}

std::string ResourcePath::getSuitPath(const std::string& filename)
{
    return getResourceRootPath() + "res/suits/" + filename;
}

std::string ResourcePath::getNumberPath(const std::string& filename)
{
    return getResourceRootPath() + "res/number/" + filename;
}

std::string ResourcePath::getUIPath(const std::string& filename)
{
    return getResourceRootPath() + "ui/" + filename;
}

std::string ResourcePath::getFontPath(const std::string& filename)
{
    return getResourceRootPath() + "fonts/" + filename;
}

std::string ResourcePath::getLevelConfigPath(int levelId)
{
    return getResourceRootPath() + "levels/level_" + std::to_string(levelId) + ".json";
}

std::string ResourcePath::getResourceRootPath()
{
    #ifdef CC_TARGET_PLATFORM_WIN32
        // Windows 平台资源路径
        return "Resources/";
    #elif defined(CC_TARGET_PLATFORM_ANDROID) || defined(CC_TARGET_PLATFORM_IOS)
        // 移动平台资源路径，通常在包内根目录
        return "";
    #else
        // 其他平台，默认空字符串
        return "";
    #endif
}
