#include "services/UndoService.h"

UndoModel UndoService::createStackFlipUndo(int cardId, int fromIndex, int toIndex) {
    return UndoModel(
        UndoType::STACK_FLIP,
        cardId,
        CardArea::STACK, 0, 0, fromIndex,
        CardArea::STACK, 0, 0, toIndex
    );
}

UndoModel UndoService::createPlayFieldMatchUndo(int cardId, int fromRow, int fromCol, int toIndex) {
    return UndoModel(
        UndoType::PLAY_FIELD_MATCH,
        cardId,
        CardArea::PLAY_FIELD, fromRow, fromCol, 0,
        CardArea::STACK, 0, 0, toIndex
    );
}

CardModel* UndoService::applyUndo(const UndoModel& undo, GameModel* model) {
    if (!model) {
        return nullptr;
    }

    int cardId = undo.getCardId();
    CardModel* card = nullptr;

    if (undo.getType() == UndoType::STACK_FLIP) {
        int currentTopIndex = model->getStackTopIndex();
        if (currentTopIndex < 0) {
            return nullptr;
        }
        card = model->removeStackCardAt(currentTopIndex);
        if (!card) {
            return nullptr;
        }
        int fromIndex = undo.getFromIndex();
        auto& stackCards = const_cast<std::vector<CardModel*>&>(model->getAllStackCards());
        if (fromIndex >= static_cast<int>(stackCards.size())) {
            stackCards.push_back(card);
        } else {
            stackCards.insert(stackCards.begin() + fromIndex, card);
        }
    } else if (undo.getType() == UndoType::PLAY_FIELD_MATCH) {
        int currentTopIndex = model->getStackTopIndex();
        if (currentTopIndex < 0) {
            return nullptr;
        }
        card = model->removeStackCardAt(currentTopIndex);
        if (!card) {
            return nullptr;
        }
        model->addPlayFieldCard(card, undo.getFromRow(), undo.getFromCol());
    }

    return card;
}
