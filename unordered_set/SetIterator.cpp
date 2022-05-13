#include <exception>

#include "SetIterator.h"
#include "Set.h"


SetIterator::SetIterator(const Set& m) : set(m), index(-1)
{
    for (int i = 0; i < set.capacity; ++i)
        if (std::get<1>(set.data[i]) == 2)
        {
            index = i;
            break;
        }
}


void SetIterator::first()
{
    index = -1;
    for (int i = 0; i < set.capacity; ++i)
        if (std::get<1>(set.data[i]) == 2)
        {
            index = i;
            break;
        }
}


void SetIterator::next()
{
    if (!valid())
        throw std::exception();
    while (((++index) < set.capacity) && (std::get<1>(set.data[index]) != 2));
    if (index == set.capacity)
        index = -1;
}


TElem SetIterator::getCurrent()
{
    if (!valid())
        throw std::exception();
    return std::get<0>(set.data[index]);
}

bool SetIterator::valid() const
{
	return index != -1;
}



