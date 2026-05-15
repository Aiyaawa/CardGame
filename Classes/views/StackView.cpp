#include "views/StackView.h"
#include "views/CardView.h"

USING_NS_CC;

StackView* StackView::create() {
    StackView* view = new StackView();
    if (view && view->init()) {
        view->autorelease();
        return view;
    }
    CC_SAFE_DELETE(view);
    return nullptr;
}

bool StackView::init() {
    if (!Node::init()) {
        return false;
    }
    setAnchorPoint(Vec2(0, 0));
    updateLayout();
    return true;
}

void StackView::updateLayout() {
    Size visibleSize = Director::getInstance()->getVisibleSize();
    _viewHeight = visibleSize.height * 580.0f / 2080.0f;

    setContentSize(Size(visibleSize.width, _viewHeight));

    _centerY = _viewHeight * 0.5f;
    _reserveStartX = visibleSize.width * 0.18f;
    _baseCardX = visibleSize.width * 0.68f;
    _stackOffsetX = visibleSize.width * 0.07f;
}

void StackView::refreshView(const GameModel* model) {
    if (!model) {
        return;
    }

    for (auto& pair : _cardViews) {
        if (pair.second) {
            pair.second->removeFromParent();
        }
    }
    _cardViews.clear();

    const auto& cards = model->getAllStackCards();
    int total = static_cast<int>(cards.size());
    for (int i = 0; i < total; ++i) {
        if (!cards[i]) {
            continue;
        }
        CardView* cardView = CardView::create(cards[i]);
        if (!cardView) {
            continue;
        }

        bool isTop = (i == total - 1);
        Vec2 pos;

        if (isTop) {
            pos = Vec2(_baseCardX, _centerY);
            cardView->setLocalZOrder(10);
        } else {
            pos = Vec2(_reserveStartX + i * _stackOffsetX, _centerY);
            cardView->setLocalZOrder(i);
        }

        cardView->setPosition(pos);

        cardView->setClickCallback([this](int cardId) {
            if (_clickCallback) {
                _clickCallback(cardId);
            }
        });
        addChild(cardView);
        _cardViews[cards[i]->getId()] = cardView;
    }
}

void StackView::setCardClickCallback(StackCardClickCallback callback) {
    _clickCallback = callback;
}

Vec2 StackView::getCardWorldPosition(int cardId) const {
    auto it = _cardViews.find(cardId);
    if (it != _cardViews.end() && it->second) {
        return it->second->convertToWorldSpace(Vec2::ZERO);
    }
    return Vec2::ZERO;
}

Vec2 StackView::getTopCardWorldPosition() const {
    const auto& cards = _cardViews;
    if (cards.empty()) {
        Vec2 localPos(_baseCardX, _centerY);
        return convertToWorldSpace(localPos);
    }
    CardView* topView = nullptr;
    int maxZ = -1;
    for (auto& pair : cards) {
        if (pair.second && pair.second->getLocalZOrder() > maxZ) {
            maxZ = pair.second->getLocalZOrder();
            topView = pair.second;
        }
    }
    if (topView) {
        return topView->convertToWorldSpace(Vec2::ZERO);
    }
    return Vec2::ZERO;
}

Vec2 StackView::getCardPosition(int index, int totalCount) const {
    bool isTop = (index == totalCount - 1);
    if (isTop) {
        return Vec2(_baseCardX, _centerY);
    }
    return Vec2(_reserveStartX + index * _stackOffsetX, _centerY);
}

CardView* StackView::getCardView(int cardId) const {
    auto it = _cardViews.find(cardId);
    if (it != _cardViews.end()) {
        return it->second;
    }
    return nullptr;
}

void StackView::removeCardView(int cardId) {
    auto it = _cardViews.find(cardId);
    if (it != _cardViews.end()) {
        if (it->second) {
            it->second->removeFromParent();
        }
        _cardViews.erase(it);
    }
}
