#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <memory>
#include "models/GameModel.h"
#include "views/GameView.h"
#include "managers/UndoManager.h"

/**
 * @class GameController
 * @brief ��Ϸ��������������Э�� Model��View �ͳ��������߼���
 *
 * GameController ����
 * - ���ݹؿ� ID ��ʼ����������Ϸ
 * - �����û�����ƺͳ�������
 * - �� GameModel �����Ը�����Ϸ״̬
 * - ���� GameView ������Ӧ����
 * - ��¼��ط���Ϸ��־�������ã�
 *
 * ʹ�ó�����
 * ��Ӧ��������ͨ�� create() ���첢���� init()��Ȼ����� startGame()��
 */
class GameController {
public:
    /**
     * @brief ��̬���췽��
     * @param model �Ѵ����õ���Ϸ����ģ��
     * @return GameController �Ĺ���ָ��
     */
    static std::shared_ptr<GameController> create(const std::shared_ptr<GameModel>& model);

    /**
     * @brief ��ʼ�������������� View �ص�
     * @param view ��Ϸ������ͼ
     * @return ��ʼ���ɹ����� true
     */
    bool init(const std::shared_ptr<GameView>& view);

    /**
     * @brief ������Ϸ�����عؿ���ˢ�½���
     * @param levelId �ؿ����
     */
    void startGame(int levelId);

    /**
     * @brief �����û����ĳ���Ƶ��߼�
     * @param cardId ��������Ƶ�Ψһ ID
     */
    void handleCardClick(int cardId);

    /**
     * @brief �����û��������������ť���߼�
     */
    void handleUndoClick();

    /**
     * @brief �����ǰ��Ϸ״̬����־�������ã�
     */
    void logGameState() const;

    virtual ~GameController();

    /**
     * @brief ���캯������Ҫ��������ģ��
     * @param model ��Ϸ����ģ��
     */
    GameController(const std::shared_ptr<GameModel>& model);

protected:
    /**
     * @brief ���ĳ�����Ƿ�����ƶ�������
     * @param cardId ���� ID
     * @return �����ƶ����� true
     */
    bool _canMatchToTray(int cardId) const;

    /**
     * @brief �����ƴ����ƶ��ƶ������̣�����¼������Ϣ
     * @param cardId ���� ID
     */
    void _matchCardToTray(int cardId);

    /**
     * @brief �ж�ĳ�����Ƿ�λ�����ƶѶ���
     * @param cardId ���� ID
     * @return �ڶ��㷵�� true
     */
    bool _isTopPlayfieldCard(int cardId) const;

private:
    std::shared_ptr<UndoManager> _undoManager;  ///< ��������������
    std::shared_ptr<GameModel>   _gameModel;    ///< ��Ϸ����ģ��
    std::shared_ptr<GameView>    _gameView;     ///< ��Ϸ������ͼ
};

#endif // GAMECONTROLLER_H
