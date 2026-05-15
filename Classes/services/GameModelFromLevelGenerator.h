#ifndef __GAME_MODEL_FROM_LEVEL_GENERATOR_H__
#define __GAME_MODEL_FROM_LEVEL_GENERATOR_H__

#include "configs/models/LevelConfig.h"
#include "models/GameModel.h"

/**
 * @brief 关卡配置转游戏模型服务
 * 无状态服务，将LevelConfig静态配置转换为GameModel运行时数据
 * 不持有数据，仅通过参数操作数据
 */
class GameModelFromLevelGenerator {
public:
    /**
     * @brief 从关卡配置生成游戏模型
     * @param config 关卡配置数据
     * @return 生成的GameModel对象（调用者负责释放）
     */
    static GameModel* generate(const LevelConfig& config);
};

#endif // __GAME_MODEL_FROM_LEVEL_GENERATOR_H__
