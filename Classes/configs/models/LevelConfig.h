#ifndef __LEVEL_CONFIG_H__
#define __LEVEL_CONFIG_H__

#include <vector>
#include <string>
#include "configs/models/CardEnums.h"

/**
 * @brief 单张卡牌配置数据
 * 描述关卡中一张卡牌的初始花色、点数及位置
 */
struct CardConfig {
    CardSuitType suit;  // 花色
    CardFaceType face;  // 点数
    int row;            // 所在行（仅桌面牌使用）
    int col;            // 所在列（仅桌面牌使用）
};

/**
 * @brief 关卡配置数据类
 * 存储单个关卡的完整静态配置，包含桌面牌和手牌区的初始卡牌布局
 * 仅存储配置数据，不处理动态逻辑
 */
class LevelConfig {
public:
    /**
     * @brief 获取关卡ID
     * @return 关卡唯一标识
     */
    int getLevelId() const;

    /**
     * @brief 设置关卡ID
     * @param id 关卡唯一标识
     */
    void setLevelId(int id);

    /**
     * @brief 获取桌面牌配置列表
     * @return 桌面牌配置的常量引用
     */
    const std::vector<CardConfig>& getPlayFieldCards() const;

    /**
     * @brief 添加一张桌面牌配置
     * @param config 卡牌配置数据
     */
    void addPlayFieldCard(const CardConfig& config);

    /**
     * @brief 获取手牌区配置列表
     * @return 手牌区配置的常量引用
     */
    const std::vector<CardConfig>& getStackCards() const;

    /**
     * @brief 添加一张手牌区配置
     * @param config 卡牌配置数据
     */
    void addStackCard(const CardConfig& config);

private:
    int _levelId = 0;                       // 关卡ID
    std::vector<CardConfig> _playFieldCards; // 桌面牌配置
    std::vector<CardConfig> _stackCards;     // 手牌区配置
};

#endif // __LEVEL_CONFIG_H__
