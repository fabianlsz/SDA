#include "ShortTest.h"
#include "MultiMap.h"
#include "MultiMapIterator.h"
#include <assert.h>
#include <vector>
#include <iostream>

using namespace std;

void testAll() {
	MultiMap m;
	m.add(1, 100);
	m.add(2, 200);
	m.add(3, 300);
	m.add(1, 500);
	m.add(2, 600);
	m.add(4, 800);

	assert(m.size() == 6);

	assert(m.remove(5, 600) == false);
	assert(m.remove(1, 500) == true);

	assert(m.size() == 5);

	vector<TValue> v;
	v = m.search(6);
	assert(v.size() == 0);

	v = m.search(1);
	assert(v.size() == 1);

	assert(m.isEmpty() == false);

	MultiMapIterator im = m.iterator();
	assert(im.valid() == true);
	while (im.valid()) {
		im.getCurrent();
		im.next();
	}
	assert(im.valid() == false);
	im.first();
	assert(im.valid() == true);

	cout << "test countValuesPerKey" << endl;

	MultiMap m2;
	m2.add(1, 100);
	m2.add(1, 200);
	m2.add(2, 300);
	m2.add(2, 400);
	m2.add(2, 500);
	m2.add(3, 600);

	vector<pair<TKey, int>> result = m2.countValuesPerKey();

	assert(result.size() == 3); // avem 3 chei

	assert(result[0].first == 1 && result[0].second == 2); // cheia 1 are 2 valori
	assert(result[1].first == 2 && result[1].second == 3); // cheia 2 are 3 valori
	assert(result[2].first == 3 && result[2].second == 1); // cheia 3 are 1 valoare

}