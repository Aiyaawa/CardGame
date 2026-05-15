#include "utils/CardUtils.h"
#include <cmath>

bool CardUtils::isRedSuit(CardSuitType suit) {
    return suit == CardSuitType::CST_HEARTS || suit == CardSuitType::CST_DIAMONDS;
}

int CardUtils::faceDiff(CardFaceType face1, CardFaceType face2) {
    int v1 = static_cast<int>(face1);
    int v2 = static_cast<int>(face2);
    return std::abs(v1 - v2);
}

bool CardUtils::isMatch(CardFaceType face1, CardFaceType face2) {
    return faceDiff(face1, face2) == 1;
}

const char* CardUtils::suitToName(CardSuitType suit) {
    switch (suit) {
        case CardSuitType::CST_HEARTS:   return "\xe2\x99\xa5";
        case CardSuitType::CST_DIAMONDS: return "\xe2\x99\xa6";
        case CardSuitType::CST_CLUBS:    return "\xe2\x99\xa3";
        case CardSuitType::CST_SPADES:   return "\xe2\x99\xa0";
        default:                          return "";
    }
}

const char* CardUtils::faceToName(CardFaceType face) {
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
