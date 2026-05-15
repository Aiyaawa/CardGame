#include "views/CardView.h"
#include "configs/models/CardResConfig.h"

USING_NS_CC;

static const float kCardWidth = 150.0f;
static const float kCardHeight = 210.0f;

float CardView::getCardWidth() {
    return kCardWidth;
}

float CardView::getCardHeight() {
    return kCardHeight;
}

CardView* CardView::create(const CardModel* model) {
    CardView* view = new CardView();
    if (view && view->initWithModel(model)) {
        view->autorelease();
        return view;
    }
    CC_SAFE_DELETE(view);
    return nullptr;
}

bool CardView::initWithModel(const CardModel* model) {
    if (!Node::init()) {
        return false;
    }

    if (!model) {
        return false;
    }

    _cardId = model->getId();
    CardSuitType suit = model->getSuit();
    CardFaceType face = model->getFace();

    setContentSize(Size(kCardWidth, kCardHeight));
    setAnchorPoint(Vec2(0.5f, 0.5f));

    _bgSprite = Sprite::create(CardResConfig::getCardBackgroundPath());
    if (_bgSprite) {
        _bgSprite->setPosition(Vec2(kCardWidth / 2, kCardHeight / 2));
        Size bgSize = _bgSprite->getContentSize();
        float scaleX = kCardWidth / bgSize.width;
        float scaleY = kCardHeight / bgSize.height;
        _bgSprite->setScale(scaleX, scaleY);
        addChild(_bgSprite, 0);
    }

    std::string bigNumPath = CardResConfig::getBigNumberPath(suit, face);
    _bigNumSprite = Sprite::create(bigNumPath);
    if (_bigNumSprite) {
        _bigNumSprite->setPosition(Vec2(kCardWidth / 2, kCardHeight / 2 - 10));
        addChild(_bigNumSprite, 1);
    }

    std::string smallNumPath = CardResConfig::getSmallNumberPath(suit, face);
    _smallNumSprite = Sprite::create(smallNumPath);
    if (_smallNumSprite) {
        _smallNumSprite->setPosition(Vec2(28, kCardHeight - 28));
        addChild(_smallNumSprite, 2);
    }

    std::string suitPath = CardResConfig::getSuitPath(suit);
    _suitSprite = Sprite::create(suitPath);
    if (_suitSprite) {
        _suitSprite->setPosition(Vec2(kCardWidth - 28, kCardHeight - 28));
        addChild(_suitSprite, 2);
    }

    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->setSwallowTouches(true);
    touchListener->onTouchBegan = CC_CALLBACK_2(CardView::onTouchBegan, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

    return true;
}

int CardView::getCardId() const {
    return _cardId;
}

void CardView::setClickCallback(CardClickCallback callback) {
    _clickCallback = callback;
}

void CardView::setInteractive(bool interactive) {
    _interactive = interactive;
}

void CardView::playMoveToAction(const Vec2& targetPos, float duration,
                                 const std::function<void(Node*)>& callback) {
    Vec2 localTarget = getParent()->convertToNodeSpace(targetPos);
    auto moveTo = MoveTo::create(duration, localTarget);
    if (callback) {
        auto callFunc = CallFuncN::create(callback);
        auto sequence = Sequence::create(moveTo, callFunc, nullptr);
        runAction(sequence);
    } else {
        runAction(moveTo);
    }
}

bool CardView::onTouchBegan(Touch* touch, Event* event) {
    if (!_interactive) {
        return false;
    }
    Vec2 touchPos = touch->getLocation();
    Vec2 localPos = convertToNodeSpace(touchPos);
    Rect cardRect(0, 0, kCardWidth, kCardHeight);
    if (cardRect.containsPoint(localPos)) {
        if (_clickCallback) {
            _clickCallback(_cardId);
        }
        return true;
    }
    return false;
}
