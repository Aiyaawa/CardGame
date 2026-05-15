#ifndef __GAME_MODEL_H__
#define __GAME_MODEL_H__

#include <vector>
#include "models/CardModel.h"
#include "configs/models/CardEnums.h"

/**
 * @brief 桌面卡牌位置信息
 * 存储卡牌在桌面牌区的行列位置
 */
struct PlayFieldCardInfo {
    CardModel* card;  // 卡牌数据指针
    int row;          // 行索引
    int col;          // 列索引
};

/**
 * @brief 游戏数据模型
 * 存储游戏运行时的全部动态数据，包括桌面牌区卡牌列表和手牌区卡牌列表
 * 支持序列化/反序列化，适配游戏存档
 * 仅存储数据，不包含业务逻辑
 */
class GameModel {
public:
    GameModel();
    ~GameModel();

    /**
     * @brief 添加桌面牌
     * @param card 卡牌数据（所有权转移给GameModel）
     * @param row 行索引
     * @param col 列索引
     */
    void addPlayFieldCard(CardModel* card, int row, int col);

    /**
     * @brief 移除桌面牌（根据卡牌ID）
     * @param cardId 要移除的卡牌ID
     * @return 被移除的卡牌指针，调用者负责释放；未找到返回nullptr
     */
    CardModel* removePlayFieldCard(int cardId);

    /**
     * @brief 根据卡牌ID查找桌面牌信息
     * @param cardId 卡牌ID
     * @return 桌面牌信息指针，未找到返回nullptr
     */
    PlayFieldCardInfo* findPlayFieldCard(int cardId);

    /**
     * @brief 获取所有桌面牌信息
     * @return 桌面牌信息列表的常量引用
     */
    const std::vector<PlayFieldCardInfo>& getAllPlayFieldCards() const;

    /**
     * @brief 添加手牌区卡牌（添加到末尾，即顶部）
     * @param card 卡牌数据（所有权转移给GameModel）
     */
    void addStackCard(CardModel* card);

    /**
     * @brief 根据索引移除手牌区卡牌
     * @param index 卡牌在列表中的索引
     * @return 被移除的卡牌指针，调用者负责释放
     */
    CardModel* removeStackCardAt(int index);

    /**
     * @brief 根据卡牌ID查找手牌区卡牌索引
     * @param cardId 卡牌ID
     * @return 索引值，未找到返回-1
     */
    int findStackCardIndex(int cardId) const;

    /**
     * @brief 获取手牌区顶部卡牌（列表最后一个元素）
     * @return 顶部卡牌指针，无卡牌时返回nullptr
     */
    CardModel* getStackTopCard() const;

    /**
     * @brief 获取手牌区顶部卡牌索引
     * @return 顶部索引，无卡牌时返回-1
     */
    int getStackTopIndex() const;

    /**
     * @brief 获取所有手牌区卡牌
     * @return 卡牌列表的常量引用
     */
    const std::vector<CardModel*>& getAllStackCards() const;

    /**
     * @brief 根据ID获取手牌区卡牌
     * @param cardId 卡牌ID
     * @return 卡牌指针，未找到返回nullptr
     */
    CardModel* getStackCardById(int cardId) const;

    /**
     * @brief 序列化为字符串
     * @return 序列化后的字符串
     */
    std::string serialize() const;

    /**
     * @brief 从字符串反序列化
     * @param data 序列化字符串
     * @return 反序列化后的GameModel对象
     */
    static GameModel deserialize(const std::string& data);

private:
    std::vector<PlayFieldCardInfo> _playFieldCards;  // 桌面牌列表
    std::vector<CardModel*> _stackCards;              // 手牌区卡牌列表（末尾为顶部）
};

#endif // __GAME_MODEL_H__
