#include "MultiMapIterator.h"
#include "MultiMap.h"
#include <iostream>

using namespace std;

// Constructor
// best = average = worst = teta 1
MultiMapIterator::MultiMapIterator(const MultiMap& c): col(c) {
    // set iterator to point to the first key node
    currentKeyNode = col.head;

    // verificam daca multimap e empty daca nu, setam currValNode la valoarea valueHead
    if (currentKeyNode != nullptr) {
        currentValueNode = currentKeyNode->valueHead;
    } else {
        // daca multimap e empty nu exista valori pe care sa le itereze
        currentValueNode = nullptr;
    }
}

// ret elem. curent
// best = average = worst = teta 1
TElem MultiMapIterator::getCurrent() const {
    if (!valid()) throw std::exception();
    return {currentKeyNode->key, currentValueNode->value};
}

// validam iteratorul
// best = average = worst = teta 1
bool MultiMapIterator::valid() const {
    return currentKeyNode != nullptr && currentValueNode != nullptr;
}

// trecem la urm elem
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

// trecem la primul elem
// best = average = worst = teta 1
void MultiMapIterator::first() {
    currentKeyNode = col.head;
    currentValueNode = currentKeyNode ? currentKeyNode->valueHead : nullptr;
}