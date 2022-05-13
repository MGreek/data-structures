#pragma once
#include "SortedBag.h"

class SortedBag;

class CustomSortedBagIterator
{
    friend class SortedBag;

private:
    const SortedBag& bag;
    CustomSortedBagIterator(const SortedBag& b, int start, int step);

    int index, frequency;
    const int step;

public:
    TComp getCurrent();
    bool valid();
    void next();
    void first();
};

