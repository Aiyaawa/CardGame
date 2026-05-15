#include "views/PlayFieldView.h"
#include "views/CardView.h"

USING_NS_CC;

PlayFieldView* PlayFieldView::create() {
    PlayFieldView* view = new PlayFieldView();
    if (view && view->init()) {
        view->autorelease();
        return view;
    }
    CC_SAFE_DELETE(view);
    return nullptr;
}

bool PlayFieldView::init() {
    if (!Node::init()) {
        return false;
    }
    setAnchorPoint(Vec2(0, 0));
    updateLayout();
    return true;
}

void PlayFieldView::updateLayout() {
    Size visibleSize = Director::getInstance()->getVisibleSize();
    _viewHeight = visibleSize.height * 1500.0f / 2080.0f;

    setContentSize(Size(visibleSize.width, _viewHeight));

    float colWidth = visibleSize.width / 4.0f;
    _colCenterX[0] = colWidth;
    _colCenterX[1] = colWidth * 3.0f;

    _startY = _viewHeight * 0.72f;
    _gapY = _viewHeight * 0.18f;
}

void PlayFieldView::refreshView(const GameModel* model) {
    if (!model) {
        return;
    }

    for (auto& pair : _cardViews) {
        if (pair.second) {
            pair.second->removeFromParent();
        }
    }
    _cardViews.clear();

    const auto& cards = model->getAllPlayFieldCards();
    for (const auto& info : cards) {
        if (!info.card) {
            continue;
        }
        CardView* cardView = CardView::create(info.card);
        if (!cardView) {
            continue;
        }
        Vec2 pos = getCardPosition(info.row, info.col);
        cardView->setPosition(pos);
        cardView->setClickCallback([this](int cardId) {
            if (_clickCallback) {
                _clickCallback(cardId);
            }
        });
        addChild(cardView);
        _cardViews[info.card->getId()] = cardView;
    }
}

void PlayFieldView::setCardClickCallback(PlayFieldCardClickCallback callback) {
    _clickCallback = callback;
}

void PlayFieldView::removeCardView(int cardId) {
    auto it = _cardViews.find(cardId);
    if (it != _cardViews.end()) {
        if (it->second) {
            it->second->removeFromParent();
        }
        _cardViews.erase(it);
    }
}

Vec2 PlayFieldView::getCardWorldPosition(int cardId) const {
    auto it = _cardViews.find(cardId);
    if (it != _cardViews.end() && it->second) {
        return it->second->convertToWorldSpace(Vec2::ZERO);
    }
    return Vec2::ZERO;
}

Vec2 PlayFieldView::getCardPosition(int row, int col) const {
    float x = _colCenterX[col];
    float y = _startY - row * _gapY;
    return Vec2(x, y);
}
