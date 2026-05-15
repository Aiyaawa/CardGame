#include "GameScene.h"
#include "views/GameView.h"
#include "controllers/GameController.h"

USING_NS_CC;

Scene* GameScene::createScene() {
    return GameScene::create();
}

bool GameScene::init() {
    if (!Scene::init()) {
        return false;
    }

    GameView* gameView = GameView::create();
    if (!gameView) {
        return false;
    }
    addChild(gameView);

    GameController* controller = new GameController(gameView);
    controller->initGame();

    return true;
}
