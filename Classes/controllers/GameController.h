#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <memory>
#include "models/GameModel.h"
#include "views/GameView.h"
#include "managers/UndoManager.h"

class GameController {
public:
    static std::shared_ptr<GameController> create(const std::shared_ptr<GameModel>& model);
    bool init(const std::shared_ptr<GameView>& view);
    void startGame(int levelId);
    void handleCardClick(int cardId);
    void handleUndoClick();
    ~GameController();
    GameController(const std::shared_ptr<GameModel>& model);
    void logGameState() const;

protected:
    bool canMatchToTray(int cardId) const;
    void matchCardToTray(int cardId);
    bool isTopPlayfieldCard(int cardId) const;

private:
    

    std::shared_ptr<UndoManager> _undoManager;
    std::shared_ptr<GameModel> _gameModel;
    std::shared_ptr<GameView>  _gameView;


};

#endif
