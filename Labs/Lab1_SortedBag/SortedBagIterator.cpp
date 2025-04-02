#include "SortedBagIterator.h"
#include "SortedBag.h"
#include <exception>

using namespace std;

//////bc = wc = avg = theta(1)
SortedBagIterator::SortedBagIterator(const SortedBag& b) : bag(b) {
	this->first();
}

///bc = wc = avg = theta(1)
TComp SortedBagIterator::getCurrent() {
	if (!this->valid()) {
		throw exception();
	}
	return this->bag.dynamicArray[this->currentIndex];
}

///bc = wc = avg = theta(1)
bool SortedBagIterator::valid() {
	return this->currentIndex < this->bag.length;
}

///bc = wc = avg = theta(1)
void SortedBagIterator::next() {
	if (!this->valid()) {
		throw exception();
	}
	this->currentIndex++;
}

///bc = wc = avg = theta(1)
void SortedBagIterator::first() {
	this->currentIndex = 0;
}