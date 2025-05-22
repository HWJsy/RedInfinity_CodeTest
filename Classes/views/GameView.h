#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include "cocos2d.h"
#include <map>
#include <memory>
#include "models/CardModel.h"
#include "models/GameModel.h"
USING_NS_CC;

class CardView;

class GameView : public cocos2d::Layer
{
public:
    // ��������
    static GameView* create(const std::shared_ptr<GameModel>& model);
    static std::shared_ptr<GameView> createShared(const std::shared_ptr<GameModel>& model);

    virtual bool init(const std::shared_ptr<GameModel>& model);

    // ����ص�����
    void setCardClickCallback(const std::function<void(int)>& cb) { _cardClickCallback = cb; }
    void setUndoClickCallback(const std::function<void()>& cb) { _undoClickCallback = cb; }

    // ˢ�����Ž���
    void updateView();

    //���ʽӿ�
    const std::map<int, CardView*>& getplayfieldViews() { return _playfieldViews; }
    const std::map<int, CardView*>& getstockViews() { return _stockViews; }
    CardView*& gettrayTopView() { return _trayTopView; }
    const std::map<int, CardView*>& gettrayHistoryViews() { return  _trayHistoryViews; }

    // ��ȡ������ͼ
    static CardView* getCardViewById(int cardId);

    // ������������ջ��ʣ����ջ��λ��
    static const Vec2 kTrayTopPosition;  // ������ջ��������
    static const Vec2 kStockOrigin;      // ʣ����ջ��������

    // �����ƶ�����
    void playMoveToAnimation(int cardId);

protected:
    // UI ����
    void createUI();
    void createBackground();
    void createPlayfield();
    void createStockArea();   // ʣ������
    void createTrayArea();    // ��������
    void createUndoButton();

    // �ֶ�ˢ��
    void updatePlayfieldCards();
    void updateStockCards();
    void updateTrayTopCard();
    void updateTrayHistory(); // ���ڳ��������ָ�����ʷ����

    // ������ť��Ӧ
    void onUndoButtonClicked(Ref*);

private:
    std::shared_ptr<GameModel> _gameModel;

    // ��Ⱦ�㼶�ڵ�
    Node* _playfieldNode;
    Node* _stockNode;
    Node* _trayNode;
    Node* _overlayNode;     // ���������ã����ϲ�ڵ�

    Menu* _ui;            // ui����

    // CardView ����
    static std::map<int, CardView*> _playfieldViews;
    static std::map<int, CardView*> _stockViews;
    static CardView* _trayTopView;
    static std::map<int, CardView*> _trayHistoryViews;

    std::function<void(int)> _cardClickCallback;
    std::function<void()> _undoClickCallback;
};

#endif
