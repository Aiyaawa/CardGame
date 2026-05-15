#include "models/UndoModel.h"
#include "cocos2d.h"

UndoModel::UndoModel()
    : _type(UndoType::STACK_FLIP)
    , _cardId(0)
    , _fromArea(CardArea::STACK)
    , _fromRow(0)
    , _fromCol(0)
    , _fromIndex(0)
    , _toArea(CardArea::STACK)
    , _toRow(0)
    , _toCol(0)
    , _toIndex(0) {
}

UndoModel::UndoModel(UndoType type, int cardId,
                     CardArea fromArea, int fromRow, int fromCol, int fromIndex,
                     CardArea toArea, int toRow, int toCol, int toIndex)
    : _type(type)
    , _cardId(cardId)
    , _fromArea(fromArea)
    , _fromRow(fromRow)
    , _fromCol(fromCol)
    , _fromIndex(fromIndex)
    , _toArea(toArea)
    , _toRow(toRow)
    , _toCol(toCol)
    , _toIndex(toIndex) {
}

UndoType UndoModel::getType() const {
    return _type;
}

int UndoModel::getCardId() const {
    return _cardId;
}

CardArea UndoModel::getFromArea() const {
    return _fromArea;
}

int UndoModel::getFromRow() const {
    return _fromRow;
}

int UndoModel::getFromCol() const {
    return _fromCol;
}

int UndoModel::getFromIndex() const {
    return _fromIndex;
}

CardArea UndoModel::getToArea() const {
    return _toArea;
}

int UndoModel::getToRow() const {
    return _toRow;
}

int UndoModel::getToCol() const {
    return _toCol;
}

int UndoModel::getToIndex() const {
    return _toIndex;
}

std::string UndoModel::serialize() const {
    char buf[128];
    snprintf(buf, sizeof(buf), "%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",
        static_cast<int>(_type), _cardId,
        static_cast<int>(_fromArea), _fromRow, _fromCol, _fromIndex,
        static_cast<int>(_toArea), _toRow, _toCol, _toIndex);
    return std::string(buf);
}

UndoModel UndoModel::deserialize(const std::string& data) {
    int typeVal = 0, cardId = 0;
    int fromAreaVal = 0, fromRow = 0, fromCol = 0, fromIndex = 0;
    int toAreaVal = 0, toRow = 0, toCol = 0, toIndex = 0;
    sscanf(data.c_str(), "%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",
        &typeVal, &cardId, &fromAreaVal, &fromRow, &fromCol, &fromIndex,
        &toAreaVal, &toRow, &toCol, &toIndex);
    return UndoModel(static_cast<UndoType>(typeVal), cardId,
                     static_cast<CardArea>(fromAreaVal), fromRow, fromCol, fromIndex,
                     static_cast<CardArea>(toAreaVal), toRow, toCol, toIndex);
}
