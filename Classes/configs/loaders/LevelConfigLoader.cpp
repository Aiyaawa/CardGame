#include "configs/loaders/LevelConfigLoader.h"
#include "cocos2d.h"
#include "json/rapidjson.h"
#include "json/document.h"

USING_NS_CC;

LevelConfig LevelConfigLoader::load(const std::string& jsonPath) {
    LevelConfig config;

    std::string fullPath = FileUtils::getInstance()->fullPathForFilename(jsonPath);
    std::string content = FileUtils::getInstance()->getStringFromFile(fullPath);

    if (content.empty()) {
        CCLOG("LevelConfigLoader: failed to load json file: %s", jsonPath.c_str());
        return config;
    }

    rapidjson::Document doc;
    doc.Parse<0>(content.c_str());

    if (doc.HasParseError()) {
        CCLOG("LevelConfigLoader: JSON parse error in file: %s", jsonPath.c_str());
        return config;
    }

    if (doc.HasMember("levelId") && doc["levelId"].IsInt()) {
        config.setLevelId(doc["levelId"].GetInt());
    }

    if (doc.HasMember("playFieldCards") && doc["playFieldCards"].IsArray()) {
        const auto& arr = doc["playFieldCards"];
        for (rapidjson::SizeType i = 0; i < arr.Size(); ++i) {
            const auto& item = arr[i];
            CardConfig cc;
            cc.suit = intToSuit(item["suit"].GetInt());
            cc.face = intToFace(item["face"].GetInt());
            cc.row = item["row"].GetInt();
            cc.col = item["col"].GetInt();
            config.addPlayFieldCard(cc);
        }
    }

    if (doc.HasMember("stackCards") && doc["stackCards"].IsArray()) {
        const auto& arr = doc["stackCards"];
        for (rapidjson::SizeType i = 0; i < arr.Size(); ++i) {
            const auto& item = arr[i];
            CardConfig cc;
            cc.suit = intToSuit(item["suit"].GetInt());
            cc.face = intToFace(item["face"].GetInt());
            cc.row = 0;
            cc.col = 0;
            config.addStackCard(cc);
        }
    }

    return config;
}

CardSuitType LevelConfigLoader::intToSuit(int suitValue) {
    return static_cast<CardSuitType>(suitValue);
}

CardFaceType LevelConfigLoader::intToFace(int faceValue) {
    return static_cast<CardFaceType>(faceValue);
}
