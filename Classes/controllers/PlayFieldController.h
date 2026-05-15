#ifndef __PLAY_FIELD_CONTROLLER_H__
#define __PLAY_FIELD_CONTROLLER_H__

#include "models/GameModel.h"
#include "managers/UndoManager.h"
#include "controllers/CardController.h"
#include <functional>

/**
 * @brief 桌面牌区控制器
 * 处理桌面牌点击事件，校验匹配规则，协调模型更新与视图动画
 * 依赖CardController进行匹配校验，依赖UndoManager记录回退
 */
class PlayFieldController {
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
    PlayFieldController(GameModel* model, CardController* cardCtrl, UndoManager* undoMgr);

    /**
     * @brief 处理桌面牌点击
     * @param cardId 被点击的卡牌ID
     * @param onComplete 动画完成回调
     * @return 操作成功返回true（匹配成功并开始动画）
     */
    bool onCardClicked(int cardId, ActionCompleteCallback onComplete = nullptr);

    /**
     * @brief 获取被操作卡牌的原位置信息（用于动画）
     * @param cardId 卡牌ID
     * @return 行列信息（-1表示无效）
     */
    void getCardOriginalPosition(int cardId, int& outRow, int& outCol) const;

private:
    GameModel* _gameModel;        // 游戏数据模型
    CardController* _cardCtrl;    // 卡牌控制器
    UndoManager* _undoManager;    // 回退管理器
    int _lastFromRow;             // 最近操作的卡牌原行
    int _lastFromCol;             // 最近操作的卡牌原列
};

#endif // __PLAY_FIELD_CONTROLLER_H__
