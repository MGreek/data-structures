#include "Set.h"
#include "SetIterator.h"

Set::Set() : count(0), capacity(0), data(nullptr)
{
}


bool Set::add(TElem elem)
{
    int start = h1(elem), offset = h2(elem), collision, index;
    for (collision = 0, index = start; collision < capacity; ++collision, index = (index + offset) % capacity)
        if (std::get<1>(data[index]) == 0)
            break;
        else if (std::get<0>(data[index]) == elem)
        {
            if (std::get<1>(data[index]) == 2)
                return false;
            break;
        }
    if ((++count) > (capacity * 0.875))
    {
        const int old_capacity = capacity;
        auto new_data = new std::tuple<TElem, int>[capacity = first_prime(count * 2)];
        for (int i = 0; i < old_capacity; ++i)
            if (std::get<1>(data[i]) == 2)
            {
                start = h1(std::get<0>(data[i])), offset = h2(std::get<0>(data[i]));
                for (index = start; std::get<1>(new_data[index]); index = (index + offset) % capacity);
                std::get<0>(new_data[index]) = std::get<0>(data[i]);
                std::get<1>(new_data[index]) = 2;
            }
        start = h1(elem), offset = h2(elem);
        for (index = start; std::get<1>(new_data[index]); index = (index + offset) % capacity);
        delete[] data;
        data = new_data;
    }
    std::get<0>(data[index]) = elem;
    std::get<1>(data[index]) = 2;
    return true;
}


bool Set::remove(TElem elem)
{
    int start = h1(elem), offset = h2(elem), collision, index;
    for (collision = 0, index = start; collision < capacity; ++collision, index = (index + offset) % capacity)
        if (std::get<1>(data[index]) == 0)
            return false;
        else if (std::get<0>(data[index]) == elem)
        {
            if (std::get<1>(data[index]) == 1)
                return false;
            break;
        }
    if (collision == capacity)
        return false;
    std::get<1>(data[index]) = 1;
    if ((--count) < (capacity * 0.125))
    {
        const int old_capacity = capacity;
        auto new_data = new std::tuple<TElem, int>[capacity = first_prime(count * 2)];
        for (int i = 0; i < old_capacity; ++i)
            if (std::get<1>(data[i]) == 2)
            {
                start = h1(std::get<0>(data[i])), offset = h2(std::get<0>(data[i]));
                for (index = start; std::get<1>(new_data[index]); index = (index + offset) % capacity);
                std::get<0>(new_data[index]) = std::get<0>(data[i]);
                std::get<1>(new_data[index]) = 2;
            }
        delete[] data;
        data = new_data;
    }
    return true;
}

bool Set::search(TElem elem) const
{
    int start = h1(elem), offset = h2(elem), collision, index;
    for (collision = 0, index = start; collision < capacity; ++collision, index = (index + offset) % capacity)
        if (std::get<1>(data[index]) == 0)
            return false;
        else if (std::get<0>(data[index]) == elem)
        {
            if (std::get<1>(data[index]) == 1)
                return false;
            else
                return true;
        }
    return false;
}


int Set::size() const
{
    return count;
}


bool Set::isEmpty() const {
	return count == 0;
}


Set::~Set() {
	delete[] data;
}


SetIterator Set::iterator() const {
	return { *this };
}

int Set::h1(TElem element) const {
    if (capacity <= 0)
        return -1;
    else
        return (capacity + element % capacity) % capacity;
}

int Set::h2(TElem element) const {
    if (capacity <= 1)
        return -1;
    else
        return 1 + ((capacity - 1) + element % (capacity - 1)) % (capacity - 1);
}

int Set::first_prime(int x) {
    if (x < 2)
        return 2;
    for (int d = 2; (d * d) <= x; ++d)
        if ((x % d) == 0)
        {
            d = 1;
            ++x;
        }
    return x;
}


