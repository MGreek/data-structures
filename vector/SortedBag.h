#pragma once
//DO NOT INCLUDE SORTEDBAGITERATOR

#include <tuple>

//DO NOT CHANGE THIS PART
typedef int TComp;
typedef TComp TElem;
typedef bool(*Relation)(TComp, TComp);
#define NULL_TCOMP -11111;

class SortedBagIterator;
class CustomSortedBagIterator;

class SortedBag {
	friend class SortedBagIterator;
    friend class CustomSortedBagIterator;

private:
    int length, capacity, element_count;

    std::tuple<TElem, int>* data;

    Relation  relation;

public:
	//constructor
	SortedBag(Relation r);

	//adds an element to the sorted bag
    //best case: O(1)
    //average and worst case: O(n)
	void add(TComp e);

	//removes one occurence of an element from a sorted bag
	//returns true if an eleent was removed, false otherwise (if e was not part of the sorted bag)
    //best case: O(1)
    //average and worst case: O(n)
    bool remove(TComp e);

	//checks if an element appearch is the sorted bag
    //best case: O(1)
    // average and worst case: O(log(n))
    bool search(TComp e) const;

	//returns the number of occurrences for an element in the sorted bag
    //best case: O(1)
    //average and worst case: O(log(n))
    int nrOccurrences(TComp e) const;

	//returns the number of elements from the sorted bag
	//all cases: O(1)
    int size() const;

	//returns an iterator for this sorted bag
    //all cases: O(1)
	SortedBagIterator iterator() const;

    //returns a custom iterator for this sorted bag
    //all cases: O(1)
    CustomSortedBagIterator custom_iterator(int start, int step) const;

	//checks if the sorted bag is empty
    //all cases: O(1)
	bool isEmpty() const;

	//destructor
	~SortedBag();
};