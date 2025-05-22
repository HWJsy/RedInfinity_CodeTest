#ifndef RESOURCEPATH_H
#define RESOURCEPATH_H

#include <string>

class ResourcePath
{
public:
    // 获取卡牌资源路径
    static std::string getCardPath(const std::string& filename);

    // 获取花色资源路径
    static std::string getSuitPath(const std::string& filename);

    // 获取数字资源路径
    static std::string getNumberPath(const std::string& filename);

    // 获取UI资源路径
    static std::string getUIPath(const std::string& filename);

    // 获取字体资源路径
    static std::string getFontPath(const std::string& filename);

    // 获取关卡配置文件路径
    static std::string getLevelConfigPath(int levelId);

private:
    // 根据平台获取资源根路径
    static std::string getResourceRootPath();
};

#endif