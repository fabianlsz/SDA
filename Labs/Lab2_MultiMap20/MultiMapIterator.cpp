#include "MultiMapIterator.h"
#include "MultiMap.h"
#include <exception>

using namespace std;

// Constructor
MultiMapIterator::MultiMapIterator(const MultiMap& c) : col(c) {
	currentKeyNode = col.head;
	currentValueNode = currentKeyNode ? currentKeyNode->valueHead : nullptr;
}

// Get the current key-value pair
TElem MultiMapIterator::getCurrent() const {
	if (!valid()) throw exception();
	return {currentKeyNode->key, currentValueNode->value};
}

// Check if the iterator is valid
bool MultiMapIterator::valid() const {
	return currentKeyNode && currentValueNode;
}

// Move to the next key-value pair
void MultiMapIterator::next() {
	if (!valid()) throw exception();

	currentValueNode = currentValueNode->next;
	if (!currentValueNode) {
		currentKeyNode = currentKeyNode->next;
		currentValueNode = currentKeyNode ? currentKeyNode->valueHead : nullptr;
	}
}

// Reset the iterator to the first element
void MultiMapIterator::first() {
	currentKeyNode = col.head;
	currentValueNode = currentKeyNode ? currentKeyNode->valueHead : nullptr;
}