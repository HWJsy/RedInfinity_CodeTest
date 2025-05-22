#ifndef LEVELCONFIG_H
#define LEVELCONFIG_H

#include "cocos2d.h"
#include <vector>
#include "json/document.h"

/**
 * @class CardConfig
 * @brief ���ƵĻ������ýṹ�壬��������ֵ����ɫ��λ����Ϣ��
 */
struct CardConfig {
    int face;           ///< ������ֵ
    int suit;           ///< ��ɫ
    cocos2d::Vec2 pos;  ///< �����ڳ����е�λ��
};

/**
 * @class LevelConfig
 * @brief ��ʾһ���ؿ��Ŀ������ã��������ƶѺͱ����ƶѡ�
 *
 * ���ฺ��洢�ͽ���ָ���ؿ��Ŀ��Ʋ��֣����ڳ�ʼ����Ϸģ�͡�
 * ֧�ִ� JSON �ļ��������á�
 */
class LevelConfig {
public:
    LevelConfig();
    virtual ~LevelConfig();

    /**
     * @brief �� JSON �ļ����عؿ����á�
     * @param filePath �ļ�·��
     * @return ���سɹ����� true��ʧ�ܷ��� false
     */
    bool loadFromFile(const std::string& filePath);

    /**
     * @brief ��ȡ���ƶѵĿ������á�
     * @return ���ƶѿ����б�
     */
    const std::vector<CardConfig>& getPlayfieldCards() const { return _playfieldCards; }

    /**
     * @brief ��ȡ�����ƶѵĿ������á�
     * @return �����ƶѿ����б�
     */
    const std::vector<CardConfig>& getStockCards() const { return _stockCards; }

    /**
     * @brief ���һ�����ƶѿ��ơ�
     * @param card ����������Ϣ
     */
    void addPlayfieldCard(const CardConfig& card);

    /**
     * @brief ���һ�ű����ƶѿ��ơ�
     * @param card ����������Ϣ
     */
    void addStockCard(const CardConfig& card);

private:
    std::vector<CardConfig> _playfieldCards; ///< ���ƶ�����
    std::vector<CardConfig> _stockCards;     ///< �����ƶ�����
};

#endif // LEVELCONFIG_H
