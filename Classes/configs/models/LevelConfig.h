#ifndef LEVELCONFIG_H
#define LEVELCONFIG_H

#include "cocos2d.h"
#include <vector>
#include "json/document.h"
#include "json/stringbuffer.h"
#include "json/writer.h"

USING_NS_CC;
struct CardConfig
{
    int face;           // ������ֵ
    int suit;           // ��ɫ
    cocos2d::Vec2 pos;  // λ��
};

class LevelConfig
{
public:
    LevelConfig();
    virtual ~LevelConfig();

    // ���ļ���������
    bool loadFromFile(const std::string& filePath);

    // ��ȡ���ƶ�����
    const std::vector<CardConfig>& getPlayfieldCards() const { return _playfieldCards; }

    // ��ȡ�����ƶ�����
    const std::vector<CardConfig>& getStockCards() const { return _stockCards; }

    //������ƶѿ�������
    void addPlayfieldCard(const CardConfig& card);

    //��ӱ����ƶѿ�������
    void addStockCard(const CardConfig& card);
private:
    std::vector<CardConfig> _playfieldCards; // ���ƶ�����
    std::vector<CardConfig> _stockCards;     // �����ƶ�����
};

#endif