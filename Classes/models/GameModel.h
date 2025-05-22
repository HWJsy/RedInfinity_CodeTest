#ifndef GAMEMODEL_H
#define GAMEMODEL_H

#include "cocos2d.h"
#include "CardModel.h"
#include <vector>
#include <memory>
#include <map>

USING_NS_CC;

/**
 * @class GameModel
 * @brief ������Ϸ�еĿ���״̬���������ƶѡ�ʣ����ջ�����̣���֧��ƥ���볷��������
 *
 * GameModel ����
 * - �洢���ѯ��ǰ���п���ģ��
 * - �ṩ�������ڲ�ͬ�������ƶ��Ľӿ�
 * - ��鿨���Ƿ��ƥ���ƶ�������
 * - ֧�ּ�¼�ͻָ�����λ�ã��Ա�ʵ�ֳ�������
 *
 * ʹ�ó�����
 * �� GameController �д����󣬵��� init() ���״̬��
 * Ȼ��ͨ�� addCardTo*() ����ʼ���ƣ�ͨ�� stockToTray(), playfieldToTray() �ȷ��������Ϸ�߼���
 */
class GameModel {
public:
    GameModel();
    virtual ~GameModel();

    /**
     * @brief ��ʼ����Ϸģ�ͣ����������������ʷ��¼
     * @return ʼ�շ��� true
     */
    bool init();

    /// @name ���ӿ�
    ///@{
    void addCardToPlayfield(const std::shared_ptr<CardModel>& card); ///< �����Ƽ������ƶ�
    void addCardToStock(const std::shared_ptr<CardModel>& card);     ///< �����Ƽ���ʣ����ջ
    void addCardToTray(const std::shared_ptr<CardModel>& card);     ///< �����Ƽ������̣�������ջ��
    ///@}

    /// @name ���ʽӿ�
    ///@{
    const std::vector<std::shared_ptr<CardModel>>& getPlayfieldCards() const; ///< ��ȡ���ƶ�
    const std::vector<std::shared_ptr<CardModel>>& getStockCards() const;     ///< ��ȡʣ����ջ
    const std::vector<std::shared_ptr<CardModel>>& getTrayCards() const;      ///< ��ȡ���̣���ʷ��ջ��
    std::shared_ptr<CardModel> getTopTrayCard() const;                       ///< ��ȡ���̶���
    ///@}

    /**
     * @brief ��ʣ����ջ����һ������������
     * @return �����ɹ����� true������ false
     */
    bool stockToTray();

    /**
     * @brief �����ƶ���ָ�� ID �Ŀ�����������
     * @param cardId ���� ID
     * @return �����ɹ����� true������ false
     */
    bool playfieldToTray(int cardId);

    /// @name ƥ�����
    ///@{
    bool canMoveToTray(int cardId) const; ///< �ж�ָ�������Ƿ��ƥ�䵽����
    bool matchCardToTray(int cardId);     ///< ִ��ƥ���������¼λ����ʷ
    ///@}

    /// @name ����֧��
    ///@{
    void recordCardPosition(int cardId, const Vec2& pos); ///< ��¼�����ƶ�ǰλ��
    void restoreCardPosition(int cardId, const Vec2& pos);///< �ָ����Ƶ�ָ��λ��
    void undoCardMatch(int cardId, const Vec2& targetPos);///< ����һ��ƥ�����
    void undoCardReplace(int cardId);                      ///< ����һ�����̵�ʣ��ջ���滻����
    ///@}

    /**
     * @brief ��鿨���Ƿ������ƶ���
     * @param cardId ���� ID
     * @return �����ƶ��з��� true
     */
    bool isCardInPlayfield(int cardId) const;

    /**
     * @brief ��ȡָ�����Ƶĵ�ǰλ��
     * @param cardId ���� ID
     * @return ���Ƶ�ǰλ�ã���δ�ҵ����� Vec2::ZERO
     */
    Vec2 getCardPosition(int cardId) const;

    /**
     * @brief ���� ID ��ȡ����ģ��
     * @param cardId ���� ID
     * @return ��Ӧ�� CardModel ָ�룬δ�ҵ����� nullptr
     */
    std::shared_ptr<CardModel> getCardById(int cardId) const;

private:
    std::vector<std::shared_ptr<CardModel>> _playfieldCards;     ///< ���ƶ��б�
    std::vector<std::shared_ptr<CardModel>> _stockCards;         ///< ʣ����ջ�б�
    std::vector<std::shared_ptr<CardModel>> _trayCards;          ///< ������ʷ��ջ�б�
    std::map<int, Vec2>                                     _cardPositionHistory; ///< ����λ����ʷ
    std::map<int, std::shared_ptr<CardModel>>               _cards;                  ///< ID ������ģ�͵�ӳ��
};

#endif // GAMEMODEL_H
