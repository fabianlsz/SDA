#include "MultiMap.h"
#include "MultiMapIterator.h"
#include <exception>
#include <iostream>

using namespace std;

// Constructor
MultiMap::MultiMap() {
    this->head = nullptr;
    this->tail = nullptr;
    this->totalSize = 0;
}

// Adds a key-value pair to the multimap
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
int MultiMap::size() const {
    return totalSize;
}

// Checks whether the multimap is empty
bool MultiMap::isEmpty() const {
    return totalSize == 0;
}

// Destructor
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
KeyNode* MultiMap::findKeyNode(TKey key) const {
    KeyNode* current = head;
    while (current) {
        if (current->key == key) return current;
        current = current->next;
    }
    return nullptr;
}

// Helper to delete a ValueNode list
void MultiMap::deleteValueList(ValueNode* valueHead) {
    while (valueHead) {
        ValueNode* nextValueNode = valueHead->next;
        delete valueHead;
        valueHead = nextValueNode;
    }
}