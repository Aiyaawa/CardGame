#ifndef __CARD_ENUMS_H__
#define __CARD_ENUMS_H__

/**
 * @brief 卡牌花色枚举
 * 定义卡牌的四种花色类型
 */
enum class CardSuitType {
    CST_HEARTS = 0,   // 红心
    CST_DIAMONDS = 1,  // 方块
    CST_CLUBS = 2,     // 梅花
    CST_SPADES = 3     // 黑桃
};

/**
 * @brief 卡牌点数枚举
 * 定义卡牌的13种点数类型
 */
enum class CardFaceType {
    CFT_ACE = 1,
    CFT_2 = 2,
    CFT_3 = 3,
    CFT_4 = 4,
    CFT_5 = 5,
    CFT_6 = 6,
    CFT_7 = 7,
    CFT_8 = 8,
    CFT_9 = 9,
    CFT_10 = 10,
    CFT_JACK = 11,
    CFT_QUEEN = 12,
    CFT_KING = 13
};

/**
 * @brief 卡牌所在区域枚举
 * 标识卡牌当前位于桌面牌区还是手牌区
 */
enum class CardArea {
    PLAY_FIELD,  // 桌面牌区
    STACK        // 手牌区（堆牌区）
};

/**
 * @brief 回退操作类型枚举
 * 记录操作类型，用于回退时区分处理
 */
enum class UndoType {
    STACK_FLIP,       // 手牌区翻牌替换
    PLAY_FIELD_MATCH  // 桌面牌匹配
};

#endif // __CARD_ENUMS_H__
