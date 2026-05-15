#include "models/CardModel.h"
#include "cocos2d.h"

CardModel::CardModel()
    : _suit(CardSuitType::CST_HEARTS)
    , _face(CardFaceType::CFT_ACE)
    , _id(0) {
}

CardModel::CardModel(CardSuitType suit, CardFaceType face, int id)
    : _suit(suit)
    , _face(face)
    , _id(id) {
}

CardSuitType CardModel::getSuit() const {
    return _suit;
}

CardFaceType CardModel::getFace() const {
    return _face;
}

int CardModel::getId() const {
    return _id;
}

int CardModel::getFaceValue() const {
    return static_cast<int>(_face);
}

std::string CardModel::serialize() const {
    char buf[64];
    snprintf(buf, sizeof(buf), "%d,%d,%d", static_cast<int>(_suit), static_cast<int>(_face), _id);
    return std::string(buf);
}

CardModel CardModel::deserialize(const std::string& data) {
    int suitVal = 0, faceVal = 0, id = 0;
    sscanf(data.c_str(), "%d,%d,%d", &suitVal, &faceVal, &id);
    return CardModel(static_cast<CardSuitType>(suitVal), static_cast<CardFaceType>(faceVal), id);
}
