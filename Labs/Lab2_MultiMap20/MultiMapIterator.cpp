#include "MultiMapIterator.h"
#include "MultiMap.h"
#include <iostream>

using namespace std;

// Constructor
// best = average = worst = teta 1
MultiMapIterator::MultiMapIterator(const MultiMap& c): col(c) {
    // Set the iterator to point to the first key node in the MultiMap
    currentKeyNode = col.head;

    // Check if the MultiMap is empty. If not, set currentValueNode to the head of the value list for the first key.
    if (currentKeyNode != nullptr) {
        currentValueNode = currentKeyNode->valueHead;
    } else {
        // If the MultiMap is empty, there are no values to iterate over
        currentValueNode = nullptr;
    }
}

// Returns the current element
// best = average = worst = teta 1
TElem MultiMapIterator::getCurrent() const {
    if (!valid()) throw std::exception();
    return {currentKeyNode->key, currentValueNode->value};
}

// Checks if the iterator is valid
// best = average = worst = teta 1
bool MultiMapIterator::valid() const {
    return currentKeyNode != nullptr && currentValueNode != nullptr;
}

// Moves to the next element
// best = average = worst = teta 1
void MultiMapIterator::next() {
    if (!valid()) throw std::exception();

    if (currentValueNode->next) {
        currentValueNode = currentValueNode->next;
    } else {
        currentKeyNode = currentKeyNode->next;
        currentValueNode = currentKeyNode ? currentKeyNode->valueHead : nullptr;
    }
}

// Moves to the first element
// best = average = worst = teta 1
void MultiMapIterator::first() {
    currentKeyNode = col.head;
    currentValueNode = currentKeyNode ? currentKeyNode->valueHead : nullptr;
}