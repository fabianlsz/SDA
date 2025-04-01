#include "SortedBagIterator.h"
#include "SortedBag.h"
#include <exception>

using namespace std;

SortedBagIterator::SortedBagIterator(const SortedBag& b) : bag(b) {
	this->first();
}

TComp SortedBagIterator::getCurrent() {
	if (!this->valid()) {
		throw exception();
	}
	return this->bag.dynamicArray[this->currentIndex];
}

bool SortedBagIterator::valid() {
	return this->currentIndex < this->bag.length;
}

void SortedBagIterator::next() {
	if (!this->valid()) {
		throw exception();
	}
	this->currentIndex++;
}

void SortedBagIterator::first() {
	this->currentIndex = 0;
}

