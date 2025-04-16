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

// adaugam o pereche de de key-values in multimap
// best: teta 1 (key already exists and the value is added to an empty key value list)
// avg: O(n+m) (traverseaza key list O(n) si adauga valoarea la fin. listei de valori O(m)
// avg: O(n+m) (traverseaza key list O(n) si adauga valoarea la fin. listei de valori O(m)
void MultiMap::add(TKey c, TValue v) {
    KeyNode* keyNode = findKeyNode(c);
    if (!keyNode) {
        // cream un nou keyNode
        KeyNode* newKeyNode = new KeyNode{c, nullptr, nullptr, nullptr};
        if (!head) {
            head = tail = newKeyNode;
        } else {
            tail->next = newKeyNode;
            newKeyNode->prev = tail;
            tail = newKeyNode;
        }
        // cream un valueKey pentru keyNode
        newKeyNode->valueHead = new ValueNode{v, nullptr, nullptr};
    } else {
        // adaugam un valueNode la lista curenta a cheii
        ValueNode* current = keyNode->valueHead;
        while (current->next) current = current->next;
        current->next = new ValueNode{v, nullptr, current};
    }
    totalSize++;
}

// stergem o pereche de key-values din multimap
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

// ret vector of values asociat unui key
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

// returneaza nr de perechi din multimap
//best=avg=worst: teta 1
int MultiMap::size() const {
    return totalSize;
}

// verifica daca multimap e empty
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

// helper care ne ajuta la functia de delete
// best: teta 1
// worst = avg teta(m), traverseaza si sterge toate nodurile din lista, m=nr valori
void MultiMap::deleteValueList(ValueNode* valueHead) {
    while (valueHead) {
        ValueNode* nextValueNode = valueHead->next;
        delete valueHead;
        valueHead = nextValueNode;
    }
}

// returneaza iteratorul pt multimap
// b = avg = w: teta 1
MultiMapIterator MultiMap::iterator() const {
    return MultiMapIterator(*this);
}


///functie care sa returnere numarul de valori pe care il are o cheie,
///de exemplu daca ai cheia a=3 si b=2 returneaza a:3 si b:2

//best teta n
//worst teta n+m
//avg = worst

vector<pair<TKey, int>> MultiMap::countValuesPerKey() const {
    vector<pair<TKey, int>> result;

    KeyNode* currentKeyNode = head;

    // parcurgem fiecare nod de cheie
    while (currentKeyNode != nullptr) {
        int valueCount = 0;

        // parcurgem lista de val pt cheia curente
        ValueNode* currentValueNode = currentKeyNode->valueHead;
        while (currentValueNode != nullptr) {
            valueCount++; // crestem contorul pt fiecare valoare gasita
            currentValueNode = currentValueNode->next;
        }

        result.push_back(make_pair(currentKeyNode->key, valueCount));

        currentKeyNode = currentKeyNode->next;
    }

    return result;
}