#ifndef __UNDO_SERVICE_H__
#define __UNDO_SERVICE_H__

#include "models/UndoModel.h"
#include "models/GameModel.h"
#include "configs/models/CardEnums.h"

/**
 * @brief 回退服务
 * 无状态服务，处理回退数据的创建与回退操作的执行
 * 不持有数据，仅通过参数操作数据
 */
class UndoService {
public:
    /**
     * @brief 创建手牌区翻牌操作的回退记录
     * @param cardId 被翻动的卡牌ID
     * @param fromIndex 卡牌在手牌区的原始索引
     * @param toIndex 卡牌移动到的目标索引（顶部）
     * @return 回退记录对象
     */
    static UndoModel createStackFlipUndo(int cardId, int fromIndex, int toIndex);

    /**
     * @brief 创建桌面牌匹配操作的回退记录
     * @param cardId 被匹配的桌面牌ID
     * @param fromRow 桌面牌原始行
     * @param fromCol 桌面牌原始列
     * @param toIndex 移动到手牌区的目标索引（顶部）
     * @return 回退记录对象
     */
    static UndoModel createPlayFieldMatchUndo(int cardId, int fromRow, int fromCol, int toIndex);

    /**
     * @brief 执行回退操作，恢复GameModel数据
     * @param undo 回退记录
     * @param model 游戏数据模型
     * @return 回退的卡牌指针（用于动画定位）
     */
    static CardModel* applyUndo(const UndoModel& undo, GameModel* model);
};

#endif // __UNDO_SERVICE_H__
