#include "controllers/PlayFieldController.h"
#include "services/UndoService.h"

PlayFieldController::PlayFieldController(GameModel* model, CardController* cardCtrl, UndoManager* undoMgr)
    : _gameModel(model)
    , _cardCtrl(cardCtrl)
    , _undoManager(undoMgr)
    , _lastFromRow(-1)
    , _lastFromCol(-1) {
}

bool PlayFieldController::onCardClicked(int cardId, ActionCompleteCallback onComplete) {
    if (!_cardCtrl || !_gameModel || !_undoManager) {
        return false;
    }

    if (!_cardCtrl->canMatchWithStackTop(cardId)) {
        return false;
    }

    PlayFieldCardInfo* pfInfo = _gameModel->findPlayFieldCard(cardId);
    if (!pfInfo || !pfInfo->card) {
        return false;
    }

    _lastFromRow = pfInfo->row;
    _lastFromCol = pfInfo->col;

    int toIndex = _gameModel->getStackTopIndex() + 1;

    UndoModel undo = UndoService::createPlayFieldMatchUndo(
        cardId, _lastFromRow, _lastFromCol, toIndex);
    _undoManager->pushUndo(undo);

    CardModel* card = _gameModel->removePlayFieldCard(cardId);
    if (card) {
        _gameModel->addStackCard(card);
    }

    if (onComplete) {
        onComplete(cardId);
    }

    return true;
}

void PlayFieldController::getCardOriginalPosition(int cardId, int& outRow, int& outCol) const {
    outRow = _lastFromRow;
    outCol = _lastFromCol;
}
