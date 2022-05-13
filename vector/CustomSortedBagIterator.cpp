//
// Created by Marc on 4/1/2022.
//

#include "CustomSortedBagIterator.h"
#include <exception>

CustomSortedBagIterator::CustomSortedBagIterator(const SortedBag& b, int start, int step) : bag(b), index(0), frequency(start), step(step)
{
    while ((index < bag.length) && (frequency >= std::get<1>(bag.data[index])))
    {
        frequency -= std::get<1>(bag.data[index]);
        ++index;
    }
}

TElem CustomSortedBagIterator::getCurrent()
{
    if (!valid())
    {
        throw std::exception();
    }

    return std::get<0>(bag.data[index]);
}

bool CustomSortedBagIterator::valid()
{
    return index < bag.length;
}

void CustomSortedBagIterator::next()
{
    if (!valid())
    {
        throw std::exception();
    }

    frequency += step;
    while ((index < bag.length) && (frequency >= std::get<1>(bag.data[index])))
    {
        frequency -= std::get<1>(bag.data[index]);
        ++index;
    }
}

void CustomSortedBagIterator::first()
{
    index = frequency = 0;
}