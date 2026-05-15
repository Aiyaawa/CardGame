#include "services/GameModelFromLevelGenerator.h"

GameModel* GameModelFromLevelGenerator::generate(const LevelConfig& config) {
    GameModel* model = new GameModel();
    int cardIdCounter = 0;

    const auto& pfCards = config.getPlayFieldCards();
    for (const auto& cc : pfCards) {
        CardModel* card = new CardModel(cc.suit, cc.face, cardIdCounter++);
        model->addPlayFieldCard(card, cc.row, cc.col);
    }

    const auto& skCards = config.getStackCards();
    for (const auto& cc : skCards) {
        CardModel* card = new CardModel(cc.suit, cc.face, cardIdCounter++);
        model->addStackCard(card);
    }

    return model;
}
