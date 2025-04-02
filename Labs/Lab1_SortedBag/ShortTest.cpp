#include "ShortTest.h"
#include "SortedBag.h"
#include "SortedBagIterator.h"
#include <assert.h>

bool relation1(TComp e1, TComp e2) {
	return e1 <= e2;
}

void testAll() {
	SortedBag sb(relation1);
	sb.add(5);
	sb.add(6);
	sb.add(0);
	sb.add(5);
	sb.add(10);
	sb.add(8);
	sb.add(8);
	sb.add(8);
	sb.add(8);
	sb.add(8);
	sb.add(8);
	sb.add(8);
	sb.add(8);

	assert(sb.size() == 13);
	assert(sb.nrOccurrences(5) == 2);

	assert(sb.remove(5) == true);
	assert(sb.size() == 12);

	assert(sb.search(6) == true);
	assert(sb.isEmpty() == false);

	sb.removeAllOccurrences(8);
	assert(sb.search(8) == false);
	assert(sb.nrOccurrences(8) == 0);
	assert(sb.size() == 4);

	SortedBagIterator it = sb.iterator();
	assert(it.valid() == true);
	while (it.valid()) {
		it.getCurrent();
		it.next();
	}
	assert(it.valid() == false);
	it.first();
	assert(it.valid() == true);

}

