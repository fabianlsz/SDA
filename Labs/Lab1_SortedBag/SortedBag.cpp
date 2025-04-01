#include "SortedBag.h"
#include "SortedBagIterator.h"

void SortedBag::resize() {
	this->capacity *=2;
	TComp* newElements = new TComp[this->capacity];
	for (int i=0;i< this->length;i++) {
		newElements[i] = this -> dynamicArray[i];
	}
	delete[] this -> dynamicArray;
	this -> dynamicArray = newElements;
}

SortedBag::SortedBag(Relation r) {
	this->capacity = 10;
	this->length = 0;
	this->dynamicArray = new TComp[this->capacity];
	this->relation = r;
}

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


bool SortedBag::remove(TComp e) {
	for (int i=0; i<this->length; i++) {
		if (this->dynamicArray[i] == e) { //daca exista elementul procced, altfel o sa dea return false
			for (int j=0;j<this->length;j++) {
				this->dynamicArray[j] = this->dynamicArray[j + 1]; //elementul curent devine elem. curr.+1
			}
			this->length--; //decrementam lungimea cu 1
			return true; //daca a fost gasit elementul va fi returnam true, daca nu false
		}
	}
	return false;
}


bool SortedBag::search(TComp elem) const {
	for (int i=0; i<this->length; i++) {
		if (this->dynamicArray[i] == elem) {
			return true;
		}
	}
	return false;
}


int SortedBag::nrOccurrences(TComp elem) const {
	int c = 0;
	for (int i = 0; i < this->length; i++) {
		if (this->dynamicArray[i] == elem) {
			c++;
		}
	}
	return c;
}



int SortedBag::size() const {
	return this->length;
}


bool SortedBag::isEmpty() const {
	return this->length == 0;
}


SortedBagIterator SortedBag::iterator() const {
	return SortedBagIterator(*this);
}


SortedBag::~SortedBag() {
	delete[] this->dynamicArray;
}
