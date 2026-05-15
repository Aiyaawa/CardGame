#include "views/GameView.h"

USING_NS_CC;

GameView* GameView::create() {
    GameView* view = new GameView();
    if (view && view->init()) {
        view->autorelease();
        return view;
    }
    CC_SAFE_DELETE(view);
    return nullptr;
}

bool GameView::init() {
    if (!Layer::init()) {
        return false;
    }

    Size visibleSize = Director::getInstance()->getVisibleSize();

    float stackHeight = visibleSize.height * 580.0f / 2080.0f;
    float dividerY = stackHeight;

    auto playFieldBg = DrawNode::create();
    Vec2 pfVertices[4] = {
        Vec2(0, dividerY),
        Vec2(visibleSize.width, dividerY),
        Vec2(visibleSize.width, visibleSize.height),
        Vec2(0, visibleSize.height)
    };
    Color4F pfColor(180.0f / 255.0f, 150.0f / 255.0f, 100.0f / 255.0f, 1.0f);
    playFieldBg->drawPolygon(pfVertices, 4, pfColor, 0, pfColor);
    addChild(playFieldBg, -1);

    _playFieldView = PlayFieldView::create();
    if (_playFieldView) {
        _playFieldView->setPosition(Vec2(0, dividerY));
        addChild(_playFieldView, 1);
    }

    auto divider = DrawNode::create();
    divider->drawLine(Vec2(0, dividerY), Vec2(visibleSize.width, dividerY), Color4F(0.3f, 0.3f, 0.3f, 0.5f));
    divider->setLineWidth(3.0f);
    addChild(divider, 2);

    auto stackBg = DrawNode::create();
    Vec2 skVertices[4] = {
        Vec2(0, 0),
        Vec2(visibleSize.width, 0),
        Vec2(visibleSize.width, dividerY),
        Vec2(0, dividerY)
    };
    Color4F skColor(140.0f / 255.0f, 80.0f / 255.0f, 160.0f / 255.0f, 1.0f);
    stackBg->drawPolygon(skVertices, 4, skColor, 0, skColor);
    addChild(stackBg, -1);

    _stackView = StackView::create();
    if (_stackView) {
        _stackView->setPosition(Vec2(0, 0));
        addChild(_stackView, 1);
    }

    _animationLayer = Node::create();
    if (_animationLayer) {
        addChild(_animationLayer, 100);
    }

    auto undoLabel = Label::createWithSystemFont("回退", "Arial", 36);
    auto undoNormal = MenuItemLabel::create(undoLabel);
    auto undoSelected = MenuItemLabel::create(
        Label::createWithSystemFont("回退", "Arial", 36));
    undoSelected->setColor(Color3B(200, 200, 200));

    _undoMenuItem = MenuItemSprite::create(undoNormal, undoSelected,
        CC_CALLBACK_0(GameView::onUndoClicked, this));
    if (_undoMenuItem) {
        _undoMenuItem->setPosition(Vec2(visibleSize.width - 100, stackHeight * 0.5f));
    }

    auto menu = Menu::create(_undoMenuItem, nullptr);
    if (menu) {
        menu->setPosition(Vec2::ZERO);
        addChild(menu, 10);
    }

    return true;
}

PlayFieldView* GameView::getPlayFieldView() const {
    return _playFieldView;
}

StackView* GameView::getStackView() const {
    return _stackView;
}

void GameView::setUndoClickCallback(UndoClickCallback callback) {
    _undoCallback = callback;
}

void GameView::setPlayFieldCardClickCallback(PlayFieldCardClickCallback callback) {
    if (_playFieldView) {
        _playFieldView->setCardClickCallback(callback);
    }
}

void GameView::setStackCardClickCallback(StackCardClickCallback callback) {
    if (_stackView) {
        _stackView->setCardClickCallback(callback);
    }
}

void GameView::setUndoButtonEnabled(bool enabled) {
    if (_undoMenuItem) {
        _undoMenuItem->setEnabled(enabled);
        _undoMenuItem->setOpacity(enabled ? 255 : 100);
    }
}

Node* GameView::getAnimationLayer() const {
    return _animationLayer;
}

void GameView::onUndoClicked() {
    if (_undoCallback) {
        _undoCallback();
    }
}
