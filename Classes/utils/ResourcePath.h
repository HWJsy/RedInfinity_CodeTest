#ifndef RESOURCEPATH_H
#define RESOURCEPATH_H

#include <string>

/**
 * @class ResourcePath
 * @brief 资源路径管理工具类
 *
 * 该类用于统一获取项目中各种资源的完整路径，
 * 方便跨平台资源访问和管理。
 */
class ResourcePath
{
public:
    /**
     * @brief 获取卡牌资源文件的完整路径
     * @param filename 卡牌资源文件名（带扩展名）
     * @return 资源完整路径字符串
     */
    static std::string getCardPath(const std::string& filename);

    /**
     * @brief 获取花色资源文件的完整路径
     * @param filename 花色资源文件名（带扩展名）
     * @return 资源完整路径字符串
     */
    static std::string getSuitPath(const std::string& filename);

    /**
     * @brief 获取数字资源文件的完整路径
     * @param filename 数字资源文件名（带扩展名）
     * @return 资源完整路径字符串
     */
    static std::string getNumberPath(const std::string& filename);

    /**
     * @brief 获取 UI 资源文件的完整路径
     * @param filename UI 资源文件名（带扩展名）
     * @return 资源完整路径字符串
     */
    static std::string getUIPath(const std::string& filename);

    /**
     * @brief 获取字体资源文件的完整路径
     * @param filename 字体资源文件名（带扩展名）
     * @return 资源完整路径字符串
     */
    static std::string getFontPath(const std::string& filename);

    /**
     * @brief 获取指定关卡配置文件的完整路径
     * @param levelId 关卡编号
     * @return 关卡配置文件完整路径字符串
     */
    static std::string getLevelConfigPath(int levelId);

private:
    /**
     * @brief 获取平台相关的资源根目录路径
     * @return 资源根目录字符串
     */
    static std::string getResourceRootPath();
};

#endif // RESOURCEPATH_H
