#ifndef __UNDO_MANAGER_H__
#define __UNDO_MANAGER_H__

#include <vector>
#include "models/UndoModel.h"

/**
 * @brief 回退管理器
 * 管理回退操作记录栈，支持压栈、弹栈和查询
 * 作为控制器的成员使用，禁止单例，禁止反向依赖控制器
 */
class UndoManager {
public:
    UndoManager();

    /**
     * @brief 压入一条回退记录
     * @param undo 回退记录对象
     */
    void pushUndo(const UndoModel& undo);

    /**
     * @brief 弹出最近一条回退记录
     * @return 回退记录对象，栈为空时返回默认对象
     */
    UndoModel popUndo();

    /**
     * @brief 查询是否可以回退
     * @return 有回退记录返回true
     */
    bool canUndo() const;

    /**
     * @brief 清空所有回退记录
     */
    void clear();

    /**
     * @brief 获取回退记录数量
     * @return 记录数量
     */
    int getUndoCount() const;

private:
    std::vector<UndoModel> _undoStack;  // 回退记录栈
};

#endif // __UNDO_MANAGER_H__
