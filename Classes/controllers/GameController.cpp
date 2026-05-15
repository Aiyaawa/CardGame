#include "controllers/GameController.h"
#include "configs/loaders/LevelConfigLoader.h"
#include "services/GameModelFromLevelGenerator.h"
#include "services/UndoService.h"
#include "views/CardView.h"

USING_NS_CC;

const float GameController::kAnimDuration = 0.3f;

GameController::GameController(GameView* view)
    : _gameView(view)
    , _gameModel(nullptr)
    , _undoManager(nullptr)
    , _cardController(nullptr)
    , _pfController(nullptr)
    , _stackController(nullptr)
    , _isAnimating(false)
    , _isAlive(true) {
}

GameController::~GameController() {
    _isAlive = false;
    CC_SAFE_DELETE(_stackController);
    CC_SAFE_DELETE(_pfController);
    CC_SAFE_DELETE(_cardController);
    CC_SAFE_DELETE(_undoManager);
    CC_SAFE_DELETE(_gameModel);
}

void GameController::initGame() {
    LevelConfig config = LevelConfigLoader::load("res/levels/level_1.json");

    CC_SAFE_DELETE(_gameModel);
    _gameModel = GameModelFromLevelGenerator::generate(config);

    CC_SAFE_DELETE(_undoManager);
    _undoManager = new UndoManager();

    CC_SAFE_DELETE(_cardController);
    _cardController = new CardController(_gameModel);

    CC_SAFE_DELETE(_pfController);
    _pfController = new PlayFieldController(_gameModel, _cardController, _undoManager);

    CC_SAFE_DELETE(_stackController);
    _stackController = new StackController(_gameModel, _cardController, _undoManager);

    registerViewCallbacks();
    refreshView();
    updateUndoButtonState();
}

void GameController::registerViewCallbacks() {
    if (!_gameView) {
        return;
    }

    _gameView->setPlayFieldCardClickCallback(
        CC_CALLBACK_1(GameController::onPlayFieldCardClicked, this));

    _gameView->setStackCardClickCallback(
        CC_CALLBACK_1(GameController::onStackCardClicked, this));

    _gameView->setUndoClickCallback(
        CC_CALLBACK_0(GameController::onUndoClicked, this));
}

void GameController::onPlayFieldCardClicked(int cardId) {
    if (_isAnimating) {
        return;
    }

    if (!_pfController || !_gameView || !_gameModel) {
        return;
    }

    PlayFieldView* pfView = _gameView->getPlayFieldView();
    StackView* skView = _gameView->getStackView();
    if (!pfView || !skView) {
        return;
    }

    Vec2 fromWorldPos = pfView->getCardWorldPosition(cardId);
    Vec2 toWorldPos = skView->getTopCardWorldPosition();

    int fromRow = -1, fromCol = -1;
    PlayFieldCardInfo* pfInfo = _gameModel->findPlayFieldCard(cardId);
    if (pfInfo) {
        fromRow = pfInfo->row;
        fromCol = pfInfo->col;
    }

    bool success = _pfController->onCardClicked(cardId, nullptr);
    if (!success) {
        return;
    }

    _isAnimating = true;

    pfView->removeCardView(cardId);

    CardModel* card = _gameModel->getStackCardById(cardId);
    if (!card) {
        _isAnimating = false;
        return;
    }

    CardView* animCard = CardView::create(card);
    if (!animCard) {
        _isAnimating = false;
        skView->refreshView(_gameModel);
        return;
    }

    Node* animLayer = _gameView->getAnimationLayer();
    Vec2 localPos = animLayer->convertToNodeSpace(fromWorldPos);
    animCard->setPosition(localPos + Vec2(CardView::getCardWidth() / 2, CardView::getCardHeight() / 2));
    animLayer->addChild(animCard);

    Vec2 targetLocalPos = animLayer->convertToNodeSpace(toWorldPos)
                          + Vec2(CardView::getCardWidth() / 2, CardView::getCardHeight() / 2);

    auto moveTo = MoveTo::create(kAnimDuration, targetLocalPos);
    auto callFunc = CallFuncN::create([this, animCard](Node* node) {
        if (!_isAlive) return;
        animCard->removeFromParent();
        if (_gameView && _gameModel) {
            StackView* skView = _gameView->getStackView();
            if (skView) {
                skView->refreshView(_gameModel);
            }
        }
        _isAnimating = false;
        updateUndoButtonState();
    });
    auto sequence = Sequence::create(moveTo, callFunc, nullptr);
    animCard->runAction(sequence);
}

void GameController::onStackCardClicked(int cardId) {
    if (_isAnimating) {
        return;
    }

    if (!_stackController || !_gameView || !_gameModel) {
        return;
    }

    StackView* skView = _gameView->getStackView();
    if (!skView) {
        return;
    }

    int fromIndex = _gameModel->findStackCardIndex(cardId);
    Vec2 fromWorldPos = skView->getCardWorldPosition(cardId);

    bool success = _stackController->onCardClicked(cardId, nullptr);
    if (!success) {
        return;
    }

    _isAnimating = true;

    skView->removeCardView(cardId);

    skView->refreshView(_gameModel);

    CardModel* card = _gameModel->getStackCardById(cardId);
    if (!card) {
        _isAnimating = false;
        return;
    }

    CardView* animCard = CardView::create(card);
    if (!animCard) {
        _isAnimating = false;
        return;
    }

    Node* animLayer = _gameView->getAnimationLayer();
    Vec2 localPos = animLayer->convertToNodeSpace(fromWorldPos);
    animCard->setPosition(localPos + Vec2(CardView::getCardWidth() / 2, CardView::getCardHeight() / 2));
    animLayer->addChild(animCard);

    Vec2 topWorldPos = skView->getTopCardWorldPosition();
    Vec2 targetLocalPos = animLayer->convertToNodeSpace(topWorldPos)
                          + Vec2(CardView::getCardWidth() / 2, CardView::getCardHeight() / 2);

    auto moveTo = MoveTo::create(kAnimDuration, targetLocalPos);
    auto callFunc = CallFuncN::create([this, animCard](Node* node) {
        if (!_isAlive) return;
        animCard->removeFromParent();
        if (_gameView && _gameModel) {
            StackView* skView = _gameView->getStackView();
            if (skView) {
                skView->refreshView(_gameModel);
            }
        }
        _isAnimating = false;
        updateUndoButtonState();
    });
    auto sequence = Sequence::create(moveTo, callFunc, nullptr);
    animCard->runAction(sequence);
}

void GameController::onUndoClicked() {
    if (_isAnimating) {
        return;
    }

    if (!_undoManager || !_gameModel || !_gameView) {
        return;
    }

    if (!_undoManager->canUndo()) {
        return;
    }

    UndoModel undo = _undoManager->popUndo();
    int cardId = undo.getCardId();

    StackView* skView = _gameView->getStackView();
    PlayFieldView* pfView = _gameView->getPlayFieldView();
    if (!skView || !pfView) {
        return;
    }

    Vec2 fromWorldPos = skView->getTopCardWorldPosition();

    CardModel* card = UndoService::applyUndo(undo, _gameModel);
    if (!card) {
        return;
    }

    _isAnimating = true;

    skView->refreshView(_gameModel);
    pfView->refreshView(_gameModel);

    Vec2 toWorldPos;
    if (undo.getType() == UndoType::PLAY_FIELD_MATCH) {
        toWorldPos = pfView->getCardWorldPosition(cardId);
        if (toWorldPos.equals(Vec2::ZERO)) {
            toWorldPos = pfView->convertToWorldSpace(
                pfView->getCardPosition(undo.getFromRow(), undo.getFromCol()));
        }
    } else {
        int total = static_cast<int>(_gameModel->getAllStackCards().size());
        toWorldPos = skView->convertToWorldSpace(
            skView->getCardPosition(undo.getFromIndex(), total));
    }

    CardView* animCard = CardView::create(card);
    if (!animCard) {
        _isAnimating = false;
        return;
    }

    Node* animLayer = _gameView->getAnimationLayer();
    Vec2 localPos = animLayer->convertToNodeSpace(fromWorldPos);
    animCard->setPosition(localPos + Vec2(CardView::getCardWidth() / 2, CardView::getCardHeight() / 2));
    animLayer->addChild(animCard);

    Vec2 targetLocalPos = animLayer->convertToNodeSpace(toWorldPos)
                          + Vec2(CardView::getCardWidth() / 2, CardView::getCardHeight() / 2);

    auto moveTo = MoveTo::create(kAnimDuration, targetLocalPos);
    auto callFunc = CallFuncN::create([this, animCard](Node* node) {
        if (!_isAlive) return;
        animCard->removeFromParent();
        if (_gameView && _gameModel) {
            _gameView->getStackView()->refreshView(_gameModel);
            _gameView->getPlayFieldView()->refreshView(_gameModel);
        }
        _isAnimating = false;
        updateUndoButtonState();
    });
    auto sequence = Sequence::create(moveTo, callFunc, nullptr);
    animCard->runAction(sequence);
}

void GameController::refreshView() {
    if (_gameView && _gameModel) {
        PlayFieldView* pfView = _gameView->getPlayFieldView();
        StackView* skView = _gameView->getStackView();
        if (pfView) {
            pfView->refreshView(_gameModel);
        }
        if (skView) {
            skView->refreshView(_gameModel);
        }
    }
}

void GameController::updateUndoButtonState() {
    if (_gameView && _undoManager) {
        _gameView->setUndoButtonEnabled(_undoManager->canUndo());
    }
}
