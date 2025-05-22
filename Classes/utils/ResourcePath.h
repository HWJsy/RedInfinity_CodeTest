#ifndef RESOURCEPATH_H
#define RESOURCEPATH_H

#include <string>

/**
 * @class ResourcePath
 * @brief ��Դ·����������
 *
 * ��������ͳһ��ȡ��Ŀ�и�����Դ������·����
 * �����ƽ̨��Դ���ʺ͹���
 */
class ResourcePath
{
public:
    /**
     * @brief ��ȡ������Դ�ļ�������·��
     * @param filename ������Դ�ļ���������չ����
     * @return ��Դ����·���ַ���
     */
    static std::string getCardPath(const std::string& filename);

    /**
     * @brief ��ȡ��ɫ��Դ�ļ�������·��
     * @param filename ��ɫ��Դ�ļ���������չ����
     * @return ��Դ����·���ַ���
     */
    static std::string getSuitPath(const std::string& filename);

    /**
     * @brief ��ȡ������Դ�ļ�������·��
     * @param filename ������Դ�ļ���������չ����
     * @return ��Դ����·���ַ���
     */
    static std::string getNumberPath(const std::string& filename);

    /**
     * @brief ��ȡ UI ��Դ�ļ�������·��
     * @param filename UI ��Դ�ļ���������չ����
     * @return ��Դ����·���ַ���
     */
    static std::string getUIPath(const std::string& filename);

    /**
     * @brief ��ȡ������Դ�ļ�������·��
     * @param filename ������Դ�ļ���������չ����
     * @return ��Դ����·���ַ���
     */
    static std::string getFontPath(const std::string& filename);

    /**
     * @brief ��ȡָ���ؿ������ļ�������·��
     * @param levelId �ؿ����
     * @return �ؿ������ļ�����·���ַ���
     */
    static std::string getLevelConfigPath(int levelId);

private:
    /**
     * @brief ��ȡƽ̨��ص���Դ��Ŀ¼·��
     * @return ��Դ��Ŀ¼�ַ���
     */
    static std::string getResourceRootPath();
};

#endif // RESOURCEPATH_H
