#include "configs/models/CardResConfig.h"
#include "cocos2d.h"

USING_NS_CC;

std::string CardResConfig::getCardBackgroundPath() {
    return "res/card_general.png";
}

std::string CardResConfig::getBigNumberPath(CardSuitType suit, CardFaceType face) {
    std::string color = isRedSuit(suit) ? "red" : "black";
    std::string name = faceToResName(face);
    return "res/number/big_" + color + "_" + name + ".png";
}

std::string CardResConfig::getSmallNumberPath(CardSuitType suit, CardFaceType face) {
    std::string color = isRedSuit(suit) ? "red" : "black";
    std::string name = faceToResName(face);
    return "res/number/small_" + color + "_" + name + ".png";
}

std::string CardResConfig::getSuitPath(CardSuitType suit) {
    switch (suit) {
        case CardSuitType::CST_HEARTS:   return "res/suits/heart.png";
        case CardSuitType::CST_DIAMONDS: return "res/suits/diamond.png";
        case CardSuitType::CST_CLUBS:    return "res/suits/club.png";
        case CardSuitType::CST_SPADES:   return "res/suits/spade.png";
        default:                          return "";
    }
}

bool CardResConfig::isRedSuit(CardSuitType suit) {
    return suit == CardSuitType::CST_HEARTS || suit == CardSuitType::CST_DIAMONDS;
}

std::string CardResConfig::faceToResName(CardFaceType face) {
    switch (face) {
        case CardFaceType::CFT_ACE:   return "A";
        case CardFaceType::CFT_2:     return "2";
        case CardFaceType::CFT_3:     return "3";
        case CardFaceType::CFT_4:     return "4";
        case CardFaceType::CFT_5:     return "5";
        case CardFaceType::CFT_6:     return "6";
        case CardFaceType::CFT_7:     return "7";
        case CardFaceType::CFT_8:     return "8";
        case CardFaceType::CFT_9:     return "9";
        case CardFaceType::CFT_10:    return "10";
        case CardFaceType::CFT_JACK:  return "J";
        case CardFaceType::CFT_QUEEN: return "Q";
        case CardFaceType::CFT_KING:  return "K";
        default:                       return "";
    }
}
