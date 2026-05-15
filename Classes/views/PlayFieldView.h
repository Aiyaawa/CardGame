#ifndef __PLAY_FIELD_VIEW_H__
#define __PLAY_FIELD_VIEW_H__

#include "cocos2d.h"
#include "models/GameModel.h"
#include "views/CardView.h"
#include <functional>
#include <unordered_map>

class PlayFieldView : public cocos2d::Node {
public:
    typedef std::function<void(int)> PlayFieldCardClickCallback;

    static PlayFieldView* create();

    bool init() override;

    void refreshView(const GameModel* model);

    void setCardClickCallback(PlayFieldCardClickCallback callback);

    void removeCardView(int cardId);

    cocos2d::Vec2 getCardWorldPosition(int cardId) const;

    cocos2d::Vec2 getCardPosition(int row, int col) const;

private:
    static const int kPlayFieldCols = 2;
    float _viewHeight;
    float _colCenterX[2];
    float _startY;
    float _gapY;

    void updateLayout();

    std::unordered_map<int, CardView*> _cardViews;
    PlayFieldCardClickCallback _clickCallback;
};

#endif
