#ifndef __CARD_UTILS_H__
#define __CARD_UTILS_H__

#include "configs/models/CardEnums.h"

/**
 * @brief 卡牌工具类
 * 提供卡牌相关的通用功能，无业务逻辑，无状态
 */
class CardUtils {
public:
    /**
     * @brief 判断花色是否为红色
     * @param suit 花色枚举
     * @return 红色花色返回true
     */
    static bool isRedSuit(CardSuitType suit);

    /**
     * @brief 计算两张牌点数差的绝对值
     * @param face1 第一张牌点数
     * @param face2 第二张牌点数
     * @return 点数差的绝对值
     */
    static int faceDiff(CardFaceType face1, CardFaceType face2);

    /**
     * @brief 判断两张牌是否匹配（点数差为1）
     * @param face1 第一张牌点数
     * @param face2 第二张牌点数
     * @return 匹配返回true
     */
    static bool isMatch(CardFaceType face1, CardFaceType face2);

    /**
     * @brief 将花色枚举转换为中文名称
     * @param suit 花色枚举
     * @return 花色中文名称
     */
    static const char* suitToName(CardSuitType suit);

    /**
     * @brief 将点数枚举转换为显示字符串
     * @param face 点数枚举
     * @return 点数显示字符串
     */
    static const char* faceToName(CardFaceType face);
};

#endif // __CARD_UTILS_H__
