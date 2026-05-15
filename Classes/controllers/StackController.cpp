#include "controllers/StackController.h"
#include "services/UndoService.h"

StackController::StackController(GameModel* model, CardController* cardCtrl, UndoManager* undoMgr)
    : _gameModel(model)
    , _cardCtrl(cardCtrl)
    , _undoManager(undoMgr)
    , _lastFromIndex(-1) {
}

bool StackController::onCardClicked(int cardId, ActionCompleteCallback onComplete) {
    if (!_cardCtrl || !_gameModel || !_undoManager) {
        return false;
    }

    if (!_cardCtrl->canFlipToStackTop(cardId)) {
        return false;
    }

    int fromIndex = _gameModel->findStackCardIndex(cardId);
    if (fromIndex < 0) {
        return false;
    }

    _lastFromIndex = fromIndex;

    int toIndex = _gameModel->getStackTopIndex();

    UndoModel undo = UndoService::createStackFlipUndo(cardId, fromIndex, toIndex);
    _undoManager->pushUndo(undo);

    CardModel* card = _gameModel->removeStackCardAt(fromIndex);
    if (card) {
        _gameModel->addStackCard(card);
    }

    if (onComplete) {
        onComplete(cardId);
    }

    return true;
}

int StackController::getCardOriginalIndex(int cardId) const {
    return _lastFromIndex;
}
