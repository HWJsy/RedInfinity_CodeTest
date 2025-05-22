#ifndef RESOURCEPATH_H
#define RESOURCEPATH_H

#include <string>

class ResourcePath
{
public:
    // ��ȡ������Դ·��
    static std::string getCardPath(const std::string& filename);

    // ��ȡ��ɫ��Դ·��
    static std::string getSuitPath(const std::string& filename);

    // ��ȡ������Դ·��
    static std::string getNumberPath(const std::string& filename);

    // ��ȡUI��Դ·��
    static std::string getUIPath(const std::string& filename);

    // ��ȡ������Դ·��
    static std::string getFontPath(const std::string& filename);

    // ��ȡ�ؿ������ļ�·��
    static std::string getLevelConfigPath(int levelId);

private:
    // ����ƽ̨��ȡ��Դ��·��
    static std::string getResourceRootPath();
};

#endif