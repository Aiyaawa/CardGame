#ifndef __STACK_CONTROLLER_H__
#define __STACK_CONTROLLER_H__

#include "models/GameModel.h"
#include "managers/UndoManager.h"
#include "controllers/CardController.h"
#include <functional>

/**
 * @brief 手牌区控制器
 * 处理手牌区卡牌点击事件，校验翻牌规则，协调模型更新与视图动画
 * 依赖CardController进行翻牌校验，依赖UndoManager记录回退
 */
class StackController {
public:
    /**
     * @brief 动画完成回调类型
     * @param cardId 操作的卡牌ID
     */
    typedef std::function<void(int)> ActionCompleteCallback;

    /**
     * @brief 构造函数
     * @param model 游戏数据模型指针
     * @param cardCtrl 卡牌控制器指针
     * @param undoMgr 回退管理器指针
     */
    StackController(GameModel* model, CardController* cardCtrl, UndoManager* undoMgr);

    /**
     * @brief 处理手牌区卡牌点击
     * @param cardId 被点击的卡牌ID
     * @param onComplete 动画完成回调
     * @return 操作成功返回true（翻牌成功并开始动画）
     */
    bool onCardClicked(int cardId, ActionCompleteCallback onComplete = nullptr);

    /**
     * @brief 获取被操作卡牌的原索引（用于动画）
     * @param cardId 卡牌ID
     * @return 原索引，无效返回-1
     */
    int getCardOriginalIndex(int cardId) const;

private:
    GameModel* _gameModel;        // 游戏数据模型
    CardController* _cardCtrl;    // 卡牌控制器
    UndoManager* _undoManager;    // 回退管理器
    int _lastFromIndex;           // 最近操作的卡牌原索引
};

#endif // __STACK_CONTROLLER_H__
