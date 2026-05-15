#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"

/**
 * @brief 游戏主场景
 * 创建GameView和GameController，启动游戏循环
 */
class GameScene : public cocos2d::Scene {
public:
    /**
     * @brief 创建游戏场景
     * @return Scene实例指针
     */
    static cocos2d::Scene* createScene();

    /**
     * @brief 初始化场景
     * @return 初始化成功返回true
     */
    bool init() override;

    CREATE_FUNC(GameScene);
};

#endif // __GAME_SCENE_H__
