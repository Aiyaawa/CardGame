#ifndef __CARD_VIEW_H__
#define __CARD_VIEW_H__

#include "cocos2d.h"
#include "models/CardModel.h"
#include <functional>

/**
 * @brief 卡牌视图类
 * 负责单张卡牌的UI展示，包含背景、大数字（居中）、小数字（左上角）、花色图标（右上角）
 * 捕获用户点击事件，通过回调通知控制器
 * 可持有const模型指针用于读取显示数据，无业务逻辑
 */
class CardView : public cocos2d::Node {
public:
    /**
     * @brief 卡牌点击回调类型
     * 参数为被点击卡牌的ID
     */
    typedef std::function<void(int)> CardClickCallback;

    /**
     * @brief 创建卡牌视图
     * @param model 卡牌数据模型（仅读取显示信息）
     * @return CardView实例指针
     */
    static CardView* create(const CardModel* model);

    /**
     * @brief 初始化卡牌视图
     * @param model 卡牌数据模型
     * @return 初始化成功返回true
     */
    bool initWithModel(const CardModel* model);

    /**
     * @brief 获取卡牌ID
     * @return 卡牌唯一ID
     */
    int getCardId() const;

    /**
     * @brief 设置点击回调
     * @param callback 点击回调函数
     */
    void setClickCallback(CardClickCallback callback);

    /**
     * @brief 设置卡牌是否可交互
     * @param interactive true为可点击
     */
    void setInteractive(bool interactive);

    /**
     * @brief 播放移动到目标位置的动作
     * @param targetPos 目标世界坐标位置
     * @param duration 动画时长（秒）
     * @param callback 动画完成回调
     */
    void playMoveToAction(const cocos2d::Vec2& targetPos, float duration,
                          const std::function<void(cocos2d::Node*)>& callback = nullptr);

    /**
     * @brief 获取卡牌宽度常量
     * @return 卡牌宽度
     */
    static float getCardWidth();

    /**
     * @brief 获取卡牌高度常量
     * @return 卡牌高度
     */
    static float getCardHeight();

private:
    bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);

    int _cardId = -1;
    CardClickCallback _clickCallback;
    bool _interactive = true;
    cocos2d::Sprite* _bgSprite = nullptr;
    cocos2d::Sprite* _bigNumSprite = nullptr;  // 大数字精灵
    cocos2d::Sprite* _smallNumSprite = nullptr; // 小数字精灵
    cocos2d::Sprite* _suitSprite = nullptr;     // 花色精灵
};

#endif // __CARD_VIEW_H__
