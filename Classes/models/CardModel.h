#ifndef __CARD_MODEL_H__
#define __CARD_MODEL_H__

#include "configs/models/CardEnums.h"
#include <string>

/**
 * @brief 卡牌数据模型
 * 存储单张卡牌的运行时数据，包括花色、点数和唯一标识
 * 支持序列化/反序列化，适配游戏存档
 */
class CardModel {
public:
    CardModel();
    CardModel(CardSuitType suit, CardFaceType face, int id);

    /**
     * @brief 获取花色
     * @return 花色枚举值
     */
    CardSuitType getSuit() const;

    /**
     * @brief 获取点数
     * @return 点数枚举值
     */
    CardFaceType getFace() const;

    /**
     * @brief 获取卡牌唯一ID
     * @return 卡牌ID
     */
    int getId() const;

    /**
     * @brief 获取点数的整数值（用于匹配计算）
     * @return 点数整数值（1~13）
     */
    int getFaceValue() const;

    /**
     * @brief 序列化为字符串
     * @return 序列化后的字符串
     */
    std::string serialize() const;

    /**
     * @brief 从字符串反序列化
     * @param data 序列化字符串
     * @return 反序列化后的CardModel对象
     */
    static CardModel deserialize(const std::string& data);

private:
    CardSuitType _suit;  // 花色
    CardFaceType _face;  // 点数
    int _id;             // 唯一标识
};

#endif // __CARD_MODEL_H__
