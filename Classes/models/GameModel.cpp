#include "models/GameModel.h"
#include "cocos2d.h"

GameModel::GameModel() {
}

GameModel::~GameModel() {
    for (auto& info : _playFieldCards) {
        CC_SAFE_DELETE(info.card);
    }
    _playFieldCards.clear();
    for (auto& card : _stackCards) {
        CC_SAFE_DELETE(card);
    }
    _stackCards.clear();
}

void GameModel::addPlayFieldCard(CardModel* card, int row, int col) {
    PlayFieldCardInfo info;
    info.card = card;
    info.row = row;
    info.col = col;
    _playFieldCards.push_back(info);
}

CardModel* GameModel::removePlayFieldCard(int cardId) {
    for (auto it = _playFieldCards.begin(); it != _playFieldCards.end(); ++it) {
        if (it->card && it->card->getId() == cardId) {
            CardModel* card = it->card;
            it->card = nullptr;
            _playFieldCards.erase(it);
            return card;
        }
    }
    return nullptr;
}

PlayFieldCardInfo* GameModel::findPlayFieldCard(int cardId) {
    for (auto& info : _playFieldCards) {
        if (info.card && info.card->getId() == cardId) {
            return &info;
        }
    }
    return nullptr;
}

const std::vector<PlayFieldCardInfo>& GameModel::getAllPlayFieldCards() const {
    return _playFieldCards;
}

void GameModel::addStackCard(CardModel* card) {
    _stackCards.push_back(card);
}

CardModel* GameModel::removeStackCardAt(int index) {
    if (index < 0 || index >= static_cast<int>(_stackCards.size())) {
        return nullptr;
    }
    CardModel* card = _stackCards[index];
    _stackCards.erase(_stackCards.begin() + index);
    return card;
}

int GameModel::findStackCardIndex(int cardId) const {
    for (int i = 0; i < static_cast<int>(_stackCards.size()); ++i) {
        if (_stackCards[i] && _stackCards[i]->getId() == cardId) {
            return i;
        }
    }
    return -1;
}

CardModel* GameModel::getStackTopCard() const {
    if (_stackCards.empty()) {
        return nullptr;
    }
    return _stackCards.back();
}

int GameModel::getStackTopIndex() const {
    if (_stackCards.empty()) {
        return -1;
    }
    return static_cast<int>(_stackCards.size()) - 1;
}

const std::vector<CardModel*>& GameModel::getAllStackCards() const {
    return _stackCards;
}

CardModel* GameModel::getStackCardById(int cardId) const {
    for (auto* card : _stackCards) {
        if (card && card->getId() == cardId) {
            return card;
        }
    }
    return nullptr;
}

std::string GameModel::serialize() const {
    std::string result;
    result += "PF:";
    for (const auto& info : _playFieldCards) {
        if (info.card) {
            result += info.card->serialize();
            result += "|";
            char posBuf[32];
            snprintf(posBuf, sizeof(posBuf), "%d,%d;", info.row, info.col);
            result += posBuf;
        }
    }
    result += "SK:";
    for (const auto* card : _stackCards) {
        if (card) {
            result += card->serialize() + ";";
        }
    }
    return result;
}

GameModel GameModel::deserialize(const std::string& data) {
    GameModel model;
    size_t pfPos = data.find("PF:");
    size_t skPos = data.find("SK:");
    if (pfPos == std::string::npos || skPos == std::string::npos) {
        return model;
    }

    std::string pfData = data.substr(pfPos + 3, skPos - pfPos - 3);
    std::string skData = data.substr(skPos + 3);

    if (!pfData.empty()) {
        size_t start = 0;
        size_t end = pfData.find(';');
        while (end != std::string::npos) {
            std::string entry = pfData.substr(start, end - start);
            size_t pipePos = entry.find('|');
            if (pipePos != std::string::npos) {
                std::string cardData = entry.substr(0, pipePos);
                std::string posData = entry.substr(pipePos + 1);
                CardModel* card = new CardModel(CardModel::deserialize(cardData));
                int row = 0, col = 0;
                sscanf(posData.c_str(), "%d,%d", &row, &col);
                model.addPlayFieldCard(card, row, col);
            }
            start = end + 1;
            end = pfData.find(';', start);
        }
    }

    if (!skData.empty()) {
        size_t start = 0;
        size_t end = skData.find(';');
        while (end != std::string::npos) {
            std::string cardData = skData.substr(start, end - start);
            if (!cardData.empty()) {
                CardModel* card = new CardModel(CardModel::deserialize(cardData));
                model.addStackCard(card);
            }
            start = end + 1;
            end = skData.find(';', start);
        }
    }

    return model;
}
