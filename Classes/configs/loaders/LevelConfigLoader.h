#pragma once
#include <memory>
#include "../models/LevelConfig.h"
#include "utils/ResourcePath.h"

namespace config {

    /**
     * @class LevelConfigLoader
     * @brief ������عؿ������ļ�����
     *
     * �������ڶ�ȡ�洢��JSON�ļ��еĹؿ�������Ϣ��
     * ������ΪLevelConfig���󣬹���Ϸ�߼�ʹ�á�
     */
    class LevelConfigLoader {
    public:
        /**
         * @brief ���ݹؿ�ID���عؿ�����
         * @param levelId �ؿ����
         * @return �ؿ����ö���Ĺ���ָ�룬ʧ�ܷ���nullptr
         */
        static std::shared_ptr<LevelConfig> loadLevelConfig(int levelId);

    private:
        /**
         * @brief ����Playfield�ֶΣ�������������������
         * @param doc JSON�ĵ�����
         * @param config Ŀ��LevelConfig����
         */
        static void parsePlayfield(const rapidjson::Document& doc, std::shared_ptr<LevelConfig>& config);

        /**
         * @brief ����Stack�ֶΣ����ر����ƶѿ�������
         * @param doc JSON�ĵ�����
         * @param config Ŀ��LevelConfig����
         */
        static void parseStack(const rapidjson::Document& doc, std::shared_ptr<LevelConfig>& config);
    };

} // namespace config
