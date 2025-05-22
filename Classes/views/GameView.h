#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include "cocos2d.h"
#include <map>
#include <memory>
#include <functional>
#include "models/CardModel.h"
#include "models/GameModel.h"

USING_NS_CC;

class CardView;

/**
 * @class GameView
 * @brief ��Ϸ����ͼ�㣬�����ƽ������ʾ�뽻������
 *
 * GameView ���ݵײ� GameModel �ṩ�Ŀ������ݣ�������ά����Ϸ������
 * ��ͬ�����������ƶѡ����̵ȣ��п��Ƶ���ͼ��֧�ֵ���¼��ͳ���������
 *
 * ��Ҫְ��
 * - ���������ָ���Ϸ����� UI ���
 * - ����ģ������ˢ����ͼ
 * - ��������ͼ�Ļ��棬������ٸ��ºͶ�������
 * - �ṩ���Ƶ���ͳ�����ť�Ļص��ӿ�
 */
class GameView : public cocos2d::Layer
{
public:
    /**
     * @brief ʹ������ָ�봴�� GameView ����
     * @param model �ײ���Ϸģ�Ͷ���Ĺ���ָ��
     * @return GameView ָ�루cocos2d::Ref ����
     */
    static GameView* create(const std::shared_ptr<GameModel>& model);

    /**
     * @brief ʹ�� std::shared_ptr ���� GameView ����
     * @param model �ײ���Ϸģ�Ͷ���Ĺ���ָ��
     * @return std::shared_ptr<GameView>
     */
    static std::shared_ptr<GameView> createShared(const std::shared_ptr<GameModel>& model);

    /**
     * @brief ��ʼ����������ģ�Ͳ���������Ԫ��
     * @param model �ײ���Ϸģ�Ͷ���Ĺ���ָ��
     * @return ��ʼ���Ƿ�ɹ�
     */
    virtual bool init(const std::shared_ptr<GameModel>& model);

    /**
     * @brief ���ÿ��Ƶ���ص�����
     * @param cb �ص�����������Ϊ��������Ƶ� ID
     */
    void setCardClickCallback(const std::function<void(int)>& cb);

    /**
     * @brief ���ó�����ť����ص�����
     * @param cb �޲λص�����
     */
    void setUndoClickCallback(const std::function<void()>& cb);

    /**
     * @brief ˢ��������Ϸ��ͼ���������п�������
     */
    void updateView();

    /**
     * @brief ��ȡ��ǰ����������ͼӳ��
     * @return ��������ID��CardViewָ���ӳ�䣨�������޸ģ�
     */
    const std::map<int, CardView*>& getPlayfieldViews() const;

    /**
     * @brief ��ȡ��ǰʣ���ƶѿ�����ͼӳ��
     * @return ʣ���ƶѿ���ID��CardViewָ���ӳ�䣨�������޸ģ�
     */
    const std::map<int, CardView*>& getStockViews() const;

    /**
     * @brief ��ȡ��ǰ���̶�����ͼ
     * @return ���̶��� CardView ָ�������
     */
    CardView*& getTrayTopView();

    /**
     * @brief ��ȡ������ʷ������ͼӳ��
     * @return ������ʷ����ID��CardViewָ���ӳ�䣨�������޸ģ�
     */
    const std::map<int, CardView*>& getTrayHistoryViews() const;

    /**
     * @brief ���ݿ���ID��ȡ��Ӧ��CardView����ָ��
     * @param cardId ����ΨһID
     * @return ��Ӧ���Ƶ� CardView ָ�룬�Ҳ������� nullptr
     */
    static CardView* getCardViewById(int cardId);

    /**
     * @brief ���ſ����ƶ������̶���λ�ö���
     * @param cardId ��Ҫ�ƶ��Ŀ���ID
     */
    void playMoveToAnimation(int cardId);

    /** ���������̶���λ�ã��������꣩ */
    static const Vec2 kTrayTopPosition;

    /** ������ʣ���ƶ���ʼλ�ã��������꣩ */
    static const Vec2 kStockOrigin;

protected:
    /**
     * @brief ������Ϸ���� UI ���֣���������������������Ͱ�ť
     * �ֽ⺯��ȷ����һְ��
     */
    void createUI();
    void createBackground();
    void createPlayfield();
    void createStockArea();
    void createTrayArea();
    void createUndoButton();

    /**
     * @brief �ֶ�ˢ�¸�����������ͼ���� updateView ����
     */
    void updatePlayfieldCards();
    void updateStockCards();
    void updateTrayTopCard();
    void updateTrayHistory();

    /**
     * @brief ������ť����¼���Ӧ
     * @param sender ��ť����ָ��
     */
    void onUndoButtonClicked(Ref* sender);

private:
    std::shared_ptr<GameModel> _gameModel;  ///< �ײ���Ϸ����ģ��

    Node* _playfieldNode;    ///< �����ڵ㣬���ڳ�������������ͼ
    Node* _stockNode;        ///< ʣ���ƶѽڵ�
    Node* _trayNode;         ///< ���̽ڵ㣨���ƺ���ʷ�ƣ�
    Node* _overlayNode;      ///< �������ǲ㣬�ö���ʾ���������еĿ���

    Menu* _ui;               ///< UI �˵��ڵ㣬����������ť��

    // ����������ͼ���棬������ٲ��Һ͸���
    static std::map<int, CardView*> _playfieldViews;
    static std::map<int, CardView*> _stockViews;
    static CardView* _trayTopView;
    static std::map<int, CardView*> _trayHistoryViews;

    // �����ص�����
    std::function<void(int)> _cardClickCallback;
    std::function<void()> _undoClickCallback;
};

#endif // GAMEVIEW_H
