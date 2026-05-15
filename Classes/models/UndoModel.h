#ifndef __UNDO_MODEL_H__
#define __UNDO_MODEL_H__

#include "configs/models/CardEnums.h"
#include <string>

/**
 * @brief 回退操作记录模型
 * 记录每一步操作的卡牌原位置、目标位置和状态变化
 * 用于支持连续撤销操作，支持序列化/反序列化
 */
class UndoModel {
public:
    UndoModel();
    UndoModel(UndoType type, int cardId,
              CardArea fromArea, int fromRow, int fromCol, int fromIndex,
              CardArea toArea, int toRow, int toCol, int toIndex);

    /**
     * @brief 获取操作类型
     * @return 回退操作类型枚举
     */
    UndoType getType() const;

    /**
     * @brief 获取操作的卡牌ID
     * @return 卡牌唯一ID
     */
    int getCardId() const;

    /**
     * @brief 获取来源区域
     * @return 卡牌操作前的区域
     */
    CardArea getFromArea() const;

    /**
     * @brief 获取来源行（桌面牌区使用）
     * @return 行索引
     */
    int getFromRow() const;

    /**
     * @brief 获取来源列（桌面牌区使用）
     * @return 列索引
     */
    int getFromCol() const;

    /**
     * @brief 获取来源索引（手牌区使用）
     * @return 手牌区列表中的索引
     */
    int getFromIndex() const;

    /**
     * @brief 获取目标区域
     * @return 卡牌操作后的区域
     */
    CardArea getToArea() const;

    /**
     * @brief 获取目标行
     * @return 行索引
     */
    int getToRow() const;

    /**
     * @brief 获取目标列
     * @return 列索引
     */
    int getToCol() const;

    /**
     * @brief 获取目标索引
     * @return 手牌区列表中的索引
     */
    int getToIndex() const;

    /**
     * @brief 序列化为字符串
     * @return 序列化后的字符串
     */
    std::string serialize() const;

    /**
     * @brief 从字符串反序列化
     * @param data 序列化字符串
     * @return 反序列化后的UndoModel对象
     */
    static UndoModel deserialize(const std::string& data);

private:
    UndoType _type;     // 操作类型
    int _cardId;        // 卡牌ID
    CardArea _fromArea; // 来源区域
    int _fromRow;       // 来源行
    int _fromCol;       // 来源列
    int _fromIndex;     // 来源索引
    CardArea _toArea;   // 目标区域
    int _toRow;         // 目标行
    int _toCol;         // 目标列
    int _toIndex;       // 目标索引
};

#endif // __UNDO_MODEL_H__
