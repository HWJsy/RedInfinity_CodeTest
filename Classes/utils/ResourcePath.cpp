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
    // 根据不同平台返回不同的资源根路径
#ifdef CC_TARGET_PLATFORM_WIN32
    return "Resources/";
#elif defined(CC_TARGET_PLATFORM_ANDROID) || defined(CC_TARGET_PLATFORM_IOS)
    return ""; // 在移动平台上，资源直接位于应用包根目录
#else
    return ""; // 默认返回空
#endif
}