#include "managers/UndoManager.h"

UndoManager::UndoManager() {
}

void UndoManager::pushUndo(const UndoModel& undo) {
    _undoStack.push_back(undo);
}

UndoModel UndoManager::popUndo() {
    if (_undoStack.empty()) {
        return UndoModel();
    }
    UndoModel undo = _undoStack.back();
    _undoStack.pop_back();
    return undo;
}

bool UndoManager::canUndo() const {
    return !_undoStack.empty();
}

void UndoManager::clear() {
    _undoStack.clear();
}

int UndoManager::getUndoCount() const {
    return static_cast<int>(_undoStack.size());
}
