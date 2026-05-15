#ifndef __CARD_CONTROLLER_H__
#define __CARD_CONTROLLER_H__

#include "models/CardModel.h"
#include "models/GameModel.h"
#include "utils/CardUtils.h"

/**
 * @brief 卡牌控制器
 * 负责单张卡牌的操作校验，如匹配判断等
 * 依赖services/utils，不直接操作视图
 */
class CardController {
public:
    /**
     * @brief 构造函数
     * @param model 游戏数据模型指针（不持有所有权）
     */
    CardController(GameModel* model);

    /**
     * @brief 判断桌面牌是否与手牌区顶部牌匹配
     * @param cardId 桌面牌ID
     * @return 匹配返回true（点数差为1）
     */
    bool canMatchWithStackTop(int cardId) const;

    /**
     * @brief 判断手牌区卡牌是否可以翻到顶部
     * @param cardId 手牌区卡牌ID
     * @return 非顶部卡牌返回true
     */
    bool canFlipToStackTop(int cardId) const;

private:
    GameModel* _gameModel;  // 游戏数据模型指针
};

#endif // __CARD_CONTROLLER_H__
