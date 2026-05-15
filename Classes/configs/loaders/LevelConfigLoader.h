#ifndef __LEVEL_CONFIG_LOADER_H__
#define __LEVEL_CONFIG_LOADER_H__

#include <string>
#include "configs/models/LevelConfig.h"

/**
 * @brief 关卡配置加载器
 * 负责从JSON文件解析关卡配置数据，生成LevelConfig对象
 * 仅处理配置加载逻辑，不持有动态数据
 */
class LevelConfigLoader {
public:
    /**
     * @brief 从JSON文件加载关卡配置
     * @param jsonPath JSON文件路径（相对于Resources目录）
     * @return 解析后的关卡配置对象
     */
    static LevelConfig load(const std::string& jsonPath);

private:
    /**
     * @brief 将整数值转换为花色枚举
     * @param suitValue JSON中的花色整数值
     * @return 对应的花色枚举
     */
    static CardSuitType intToSuit(int suitValue);

    /**
     * @brief 将整数值转换为点数枚举
     * @param faceValue JSON中的点数整数值
     * @return 对应的点数枚举
     */
    static CardFaceType intToFace(int faceValue);
};

#endif // __LEVEL_CONFIG_LOADER_H__
