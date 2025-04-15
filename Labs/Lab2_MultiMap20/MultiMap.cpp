#include "MultiMap.h"
#include "MultiMapIterator.h"
#include <exception>
#include <iostream>
#include <vector> // Ensure vector is included for usage

using namespace std;

// Constructor
// best = average = worst = teta 1
MultiMap::MultiMap() {
    this->head = nullptr;
    this->tail = nullptr;
    this->totalSize = 0;
}

// Adds a key-value pair to the multimap
// best: teta 1 (key already exists and the value is added to an empty key value list)
// avg: O(n+m) (traverseaza key list O(n) si adauga valoarea la fin. listei de valori O(m)
// avg: O(n+m) (traverseaza key list O(n) si adauga valoarea la fin. listei de valori O(m)
void MultiMap::add(TKey c, TValue v) {
    KeyNode* keyNode = findKeyNode(c);
    if (!keyNode) {
        // Create a new KeyNode
        KeyNode* newKeyNode = new KeyNode{c, nullptr, nullptr, nullptr};
        if (!head) {
            head = tail = newKeyNode;
        } else {
            tail->next = newKeyNode;
            newKeyNode->prev = tail;
            tail = newKeyNode;
        }
        // Create a ValueNode for the new key
        newKeyNode->valueHead = new ValueNode{v, nullptr, nullptr};
    } else {
        // Append a ValueNode to the existing key's list
        ValueNode* current = keyNode->valueHead;
        while (current->next) current = current->next;
        current->next = new ValueNode{v, nullptr, current};
    }
    totalSize++;
}

// Removes a key-value pair from the multimap
//best: teta 1
// worst = avg O(n+m_) la fel ca si la add motivul
bool MultiMap::remove(TKey c, TValue v) {
    KeyNode* keyNode = findKeyNode(c);
    if (!keyNode) return false;

    ValueNode* valueNode = keyNode->valueHead;
    while (valueNode && valueNode->value != v) valueNode = valueNode->next;

    if (!valueNode) return false;

    if (valueNode->prev) valueNode->prev->next = valueNode->next;
    else keyNode->valueHead = valueNode->next;

    if (valueNode->next) valueNode->next->prev = valueNode->prev;

    delete valueNode;
    totalSize--;

    if (!keyNode->valueHead) {
        if (keyNode->prev) keyNode->prev->next = keyNode->next;
        else head = keyNode->next;

        if (keyNode->next) keyNode->next->prev = keyNode->prev;
        else tail = keyNode->prev;

        delete keyNode;
    }

    return true;
}

// Returns the vector of values associated with a key
// best: teta 1
// avg = worst la fel motivul ca si mai sus
std::vector<TValue> MultiMap::search(TKey c) const {
    std::vector<TValue> result;
    KeyNode* keyNode = findKeyNode(c);
    if (!keyNode) return result;

    ValueNode* valueNode = keyNode->valueHead;
    while (valueNode) {
        result.push_back(valueNode->value);
        valueNode = valueNode->next;
    }

    return result;
}

// Returns the number of pairs in the multimap
//best=avg=worst: teta 1
int MultiMap::size() const {
    return totalSize;
}

// Checks whether the multimap is empty
//best=avg=worst: teta 1
bool MultiMap::isEmpty() const {
    return totalSize == 0;
}

// Destructor
// best: teta 1 daca multimap e empty
//average = worst: O(n+m)
MultiMap::~MultiMap() {
    while (head) {
        KeyNode* nextKeyNode = head->next;
        deleteValueList(head->valueHead);
        delete head;
        head = nextKeyNode;
    }
    head = tail = nullptr;
}

// Helper to find a KeyNode by key
// bst teta 1 daca key e prima din lista
//average teta n - traverseaza aprox. jumatate din lista pentru gasirea key-ului
//worst teta n daca key e ultima din lista
KeyNode* MultiMap::findKeyNode(TKey key) const {
    KeyNode* current = head;
    while (current) {
        if (current->key == key) return current;
        current = current->next;
    }
    return nullptr;
}

// Helper to delete a ValueNode list
// best: teta 1
// worst = avg teta(m), traverseaza si sterge toate nodurile din lista, m=nr valori
void MultiMap::deleteValueList(ValueNode* valueHead) {
    while (valueHead) {
        ValueNode* nextValueNode = valueHead->next;
        delete valueHead;
        valueHead = nextValueNode;
    }
}

// Returns an iterator for the multimap
// b = avg = w: teta 1
MultiMapIterator MultiMap::iterator() const {
    return MultiMapIterator(*this);
}