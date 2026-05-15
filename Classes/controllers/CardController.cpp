#include "controllers/CardController.h"

CardController::CardController(GameModel* model)
    : _gameModel(model) {
}

bool CardController::canMatchWithStackTop(int cardId) const {
    if (!_gameModel) {
        return false;
    }

    PlayFieldCardInfo* pfInfo = _gameModel->findPlayFieldCard(cardId);
    if (!pfInfo || !pfInfo->card) {
        return false;
    }

    CardModel* topCard = _gameModel->getStackTopCard();
    if (!topCard) {
        return false;
    }

    return CardUtils::isMatch(pfInfo->card->getFace(), topCard->getFace());
}

bool CardController::canFlipToStackTop(int cardId) const {
    if (!_gameModel) {
        return false;
    }

    CardModel* topCard = _gameModel->getStackTopCard();
    if (!topCard || topCard->getId() == cardId) {
        return false;
    }

    int index = _gameModel->findStackCardIndex(cardId);
    return index >= 0;
}
