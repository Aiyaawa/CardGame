#ifndef __GAME_VIEW_H__
#define __GAME_VIEW_H__

#include "cocos2d.h"
#include "views/PlayFieldView.h"
#include "views/StackView.h"
#include <functional>

/**
 * @brief 游戏主视图
 * 组合桌面牌区视图和手牌区视图，提供回退按钮
 * 捕获回退按钮点击事件，通过回调通知控制器
 * 可持有const控制器/模型指针，无业务逻辑
 */
class GameView : public cocos2d::Layer {
public:
    /**
     * @brief 回退按钮点击回调类型
     */
    typedef std::function<void()> UndoClickCallback;

    /**
     * @brief 桌面牌点击回调类型
     */
    typedef std::function<void(int)> PlayFieldCardClickCallback;

    /**
     * @brief 手牌区卡牌点击回调类型
     */
    typedef std::function<void(int)> StackCardClickCallback;

    /**
     * @brief 创建游戏主视图
     * @return GameView实例指针
     */
    static GameView* create();

    /**
     * @brief 初始化
     * @return 初始化成功返回true
     */
    bool init() override;

    /**
     * @brief 获取桌面牌区视图
     * @return PlayFieldView指针
     */
    PlayFieldView* getPlayFieldView() const;

    /**
     * @brief 获取手牌区视图
     * @return StackView指针
     */
    StackView* getStackView() const;

    /**
     * @brief 设置回退按钮点击回调
     * @param callback 回退回调函数
     */
    void setUndoClickCallback(UndoClickCallback callback);

    /**
     * @brief 设置桌面牌点击回调
     * @param callback 点击回调函数
     */
    void setPlayFieldCardClickCallback(PlayFieldCardClickCallback callback);

    /**
     * @brief 设置手牌区卡牌点击回调
     * @param callback 点击回调函数
     */
    void setStackCardClickCallback(StackCardClickCallback callback);

    /**
     * @brief 设置回退按钮是否可用
     * @param enabled true为可用
     */
    void setUndoButtonEnabled(bool enabled);

    /**
     * @brief 获取动画临时层（用于跨区域移动卡牌的动画）
     * @return 动画层节点指针
     */
    cocos2d::Node* getAnimationLayer() const;

    /**
     * @brief 回退按钮点击事件处理
     */
    void onUndoClicked();

private:
    PlayFieldView* _playFieldView = nullptr;  // 桌面牌区视图
    StackView* _stackView = nullptr;          // 手牌区视图
    cocos2d::Node* _animationLayer = nullptr; // 动画临时层
    cocos2d::MenuItem* _undoMenuItem = nullptr; // 回退按钮菜单项
    UndoClickCallback _undoCallback;          // 回退回调
};

#endif // __GAME_VIEW_H__
