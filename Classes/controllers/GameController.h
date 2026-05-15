#ifndef __GAME_CONTROLLER_H__
#define __GAME_CONTROLLER_H__

#include "cocos2d.h"
#include "models/GameModel.h"
#include "managers/UndoManager.h"
#include "controllers/CardController.h"
#include "controllers/PlayFieldController.h"
#include "controllers/StackController.h"
#include "views/GameView.h"

/**
 * @brief 游戏主控制器
 * 协调模型与视图，处理用户操作、业务逻辑、动画调用
 * 依赖services/managers，是整个MVC架构的核心协调者
 */
class GameController {
public:
    /**
     * @brief 构造函数
     * @param view 游戏主视图指针
     */
    GameController(GameView* view);

    /**
     * @brief 析构函数
     */
    ~GameController();

    /**
     * @brief 初始化游戏（从默认关卡配置加载）
     */
    void initGame();

    /**
     * @brief 处理桌面牌点击
     * @param cardId 被点击的卡牌ID
     */
    void onPlayFieldCardClicked(int cardId);

    /**
     * @brief 处理手牌区卡牌点击
     * @param cardId 被点击的卡牌ID
     */
    void onStackCardClicked(int cardId);

    /**
     * @brief 处理回退按钮点击
     */
    void onUndoClicked();

private:
    static const float kAnimDuration;  // MoveTo动画时长

    /**
     * @brief 注册视图回调
     */
    void registerViewCallbacks();

    /**
     * @brief 刷新整个视图
     */
    void refreshView();

    /**
     * @brief 更新回退按钮状态
     */
    void updateUndoButtonState();

    GameView* _gameView;                  // 游戏主视图
    GameModel* _gameModel;                // 游戏数据模型
    UndoManager* _undoManager;            // 回退管理器
    CardController* _cardController;      // 卡牌控制器
    PlayFieldController* _pfController;   // 桌面牌区控制器
    StackController* _stackController;    // 手牌区控制器
    bool _isAnimating;                    // 是否正在播放动画
    bool _isAlive;                        // 对象是否存活（防止动画回调访问已销毁对象）
};

#endif // __GAME_CONTROLLER_H__
