#include "configs/models/LevelConfig.h"

int LevelConfig::getLevelId() const {
    return _levelId;
}

void LevelConfig::setLevelId(int id) {
    _levelId = id;
}

const std::vector<CardConfig>& LevelConfig::getPlayFieldCards() const {
    return _playFieldCards;
}

void LevelConfig::addPlayFieldCard(const CardConfig& config) {
    _playFieldCards.push_back(config);
}

const std::vector<CardConfig>& LevelConfig::getStackCards() const {
    return _stackCards;
}

void LevelConfig::addStackCard(const CardConfig& config) {
    _stackCards.push_back(config);
}
