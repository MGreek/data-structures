#include "SortedBagIterator.h"
#include "SortedBag.h"
#include <exception>

using namespace std;

SortedBagIterator::SortedBagIterator(const SortedBag& b) : bag(b), index(0), frequency(0)
{
}

TComp SortedBagIterator::getCurrent()
{
    if (!valid())
    {
        throw std::exception();
    }

    return std::get<0>(bag.data[index]);
}

bool SortedBagIterator::valid()
{
	return index < bag.length;
}

void SortedBagIterator::next()
{
    if (!valid())
    {
        throw std::exception();
    }

    if (++frequency == std::get<1>(bag.data[index]))
    {
        ++index;
        frequency = 0;
    }
}

void SortedBagIterator::first()
{
	index = frequency = 0;
}

