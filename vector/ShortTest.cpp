#include "ShortTest.h"
#include "SortedBag.h"
#include "SortedBagIterator.h"
#include "CustomSortedBagIterator.h"
#include <assert.h>
#include <iostream>

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

	assert(sb.size() == 6);
	assert(sb.nrOccurrences(5) == 2);

	assert(sb.remove(5) == true);
	assert(sb.size() == 5);

	assert(sb.search(6) == true);
	assert(sb.isEmpty() == false);

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

void testCustomIterator()
{
    const int arr[] = { 1, 1, 1, 2, 2, 2, 4, 4, 4, 5, 5, 5, 11, 11 };
    const int len = sizeof(arr) / sizeof(int);
    SortedBag sb(relation1);
    for (int i = 0; i < len; ++i)
    {
        sb.add(arr[i]);
    }
    const int start = 2;
    const int step = 5;
    CustomSortedBagIterator it = sb.custom_iterator(start, step);
    for (int i = start; i < len; i += step, it.next())
    {
        assert(arr[i] == it.getCurrent());
    }
}

