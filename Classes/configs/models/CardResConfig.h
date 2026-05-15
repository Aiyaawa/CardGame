#ifndef __CARD_RES_CONFIG_H__
#define __CARD_RES_CONFIG_H__

#include <string>
#include "configs/models/CardEnums.h"

/**
 * @brief 卡牌资源配置类
 * 管理卡牌图片资源的路径映射，关联CardView的纹理加载逻辑
 * 资源目录结构：res/number/(big|small)_(red|black)_(点数).png
 *              res/suits/(花色).png
 *              res/card_general.png
 */
class CardResConfig {
public:
    /**
     * @brief 获取卡牌背景图路径
     * @return 背景图资源路径
     */
    static std::string getCardBackgroundPath();

    /**
     * @brief 获取大数字资源路径（居中显示）
     * @param suit 花色类型，决定红/黑色
     * @param face 点数类型，决定数字
     * @return 大数字图片资源路径
     */
    static std::string getBigNumberPath(CardSuitType suit, CardFaceType face);

    /**
     * @brief 获取小数字资源路径（左上角显示）
     * @param suit 花色类型，决定红/黑色
     * @param face 点数类型，决定数字
     * @return 小数字图片资源路径
     */
    static std::string getSmallNumberPath(CardSuitType suit, CardFaceType face);

    /**
     * @brief 获取花色图标资源路径（右上角显示）
     * @param suit 花色类型
     * @return 花色图标资源路径
     */
    static std::string getSuitPath(CardSuitType suit);

private:
    /**
     * @brief 判断花色是否为红色
     * @param suit 花色类型
     * @return 红色花色返回true，黑色花色返回false
     */
    static bool isRedSuit(CardSuitType suit);

    /**
     * @brief 将点数枚举转换为资源文件名中的字符串
     * @param face 点数类型
     * @return 对应的资源文件名字符串（如"A"、"2"、"J"等）
     */
    static std::string faceToResName(CardFaceType face);
};

#endif // __CARD_RES_CONFIG_H__
