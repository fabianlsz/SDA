#include "SortedBag.h"
#include "SortedBagIterator.h"
//best case Theta(n), wc - Theta(n), avg - Theta(n)
void SortedBag::resize() {
    this->capacity *= 2;
    TComp* newElements = new TComp[this->capacity];

    for (int i = 0; i < this->length; i++) {
        newElements[i] = this->dynamicArray[i];
    }

    delete[] this->dynamicArray;
    this->dynamicArray = newElements;
}

SortedBag::SortedBag(Relation r) {
    this->capacity = 10;
    this->length = 0;
    this->dynamicArray = new TComp[this->capacity];
    this->relation = r;
}
///bc - Theta(1) adauga la sfarsit fara mutari
///wc - theta(n) daca il pune la inceput
///avg - O(n)
void SortedBag::add(TComp e) {
    // daca lungimea bag-ului = capacitatea trebuie sa incrementam lungimea vectorului
    if (this->length == this->capacity) {
        resize();
    }

    int pos = 0;
    while (pos < this->length && this->relation(this->dynamicArray[pos], e)) {
        pos++;
    }

    for (int i = this->length; i > pos; i--) {
        this->dynamicArray[i] = this->dynamicArray[i - 1];
    }

    this->dynamicArray[pos] = e;
    this->length++;
}

///bc - O(1) daca e primul elem
///wc theta(n) daca e ultimul eleme
///avg O(n)

bool SortedBag::remove(TComp e) {
    for (int i = 0; i < this->length; i++) {
        if (this->dynamicArray[i] == e) {
            // daca exista elementul procced, altfel o sa dea return false
            for (int j = i; j < this->length - 1; j++) {
                this->dynamicArray[j] = this->dynamicArray[j + 1];
                // elementul curent devine elem. curr.+1
            }
            this->length--;
            // decrementam lungimea cu 1
            return true;
            // daca a fost gasit elementul va fi returnam true, daca nu false
        }
    }
    return false;
}

///bc - Theta(1) daca e primul elem
///wc theta(n) daca nu ex elem sau e ultimukl
///avg O(n)
bool SortedBag::search(TComp elem) const {
    for (int i = 0; i < this->length; i++) {
        if (this->dynamicArray[i] == elem) {
            return true;
        }
    }
    return false;
}

///bc - theta(1) elem nu exista
///wc theta(n) daca toate elem sunt egale
///avg O(n)
int SortedBag::nrOccurrences(TComp elem) const {
    int c = 0;
    for (int i = 0; i < this->length; i++) {
        if (this->dynamicArray[i] == elem) {
            c++;
        }
    }
    return c;
}

///bc = wc = avg = theta(1)
int SortedBag::size() const {
    return this->length;
}

///bc = wc = avg = theta(1)
bool SortedBag::isEmpty() const {
    return this->length == 0;
}

///bc = wc = avg = theta(1)
SortedBagIterator SortedBag::iterator() const {
    return SortedBagIterator(*this);
}

///bc = wc = avg = theta(n)
SortedBag::~SortedBag() {
    delete[] this->dynamicArray;
}

//stergi toate aparitiile unui elem pe reprezentare nu pe operatiile in interfata
///bc - theta(n) daca nu exista elementul e in array se face o singura parcurgee fara mutari
///wc - theta(n^2) daca toate cele n elemente = e, atunci fiecare stergere inseamna o mutare a tuturor elem ramase
///avg - daca elementul e apare de t ori, se muta ~n/2 elem -> t x O(n) = O(tn)
///avg continuare - daca t = O(n) avem O(n^2), daca t e mic avem O(n)
void SortedBag::removeAllOccurrences(TComp e) {
    int i = 0;
    while (i<this->length) {
        if (this->dynamicArray[i] == e) {
            for (int j = i;j<this->length-1; j++ ) {
                this->dynamicArray[j] = this->dynamicArray[j + 1];
            }
            this->length--;
        }
        else
            i++;
    }
}
