#ifndef __STACK_VIEW_H__
#define __STACK_VIEW_H__

#include "cocos2d.h"
#include "models/GameModel.h"
#include "views/CardView.h"
#include <functional>
#include <unordered_map>

class StackView : public cocos2d::Node {
public:
    typedef std::function<void(int)> StackCardClickCallback;

    static StackView* create();

    bool init() override;

    void refreshView(const GameModel* model);

    void setCardClickCallback(StackCardClickCallback callback);

    cocos2d::Vec2 getCardWorldPosition(int cardId) const;

    cocos2d::Vec2 getTopCardWorldPosition() const;

    cocos2d::Vec2 getCardPosition(int index, int totalCount) const;

    CardView* getCardView(int cardId) const;

    void removeCardView(int cardId);

private:
    float _viewHeight;
    float _centerY;
    float _reserveStartX;
    float _baseCardX;
    float _stackOffsetX;

    void updateLayout();

    std::unordered_map<int, CardView*> _cardViews;
    StackCardClickCallback _clickCallback;
};

#endif
