#include "SortedBag.h"
#include "SortedBagIterator.h"
#include "CustomSortedBagIterator.h"
#include <exception>

SortedBag::SortedBag(Relation r) : length(0), capacity(0), element_count(0), data(nullptr), relation(r)
{
}

void SortedBag::add(TComp e)
{
    ++element_count;
    // Already existing case
    for (int i = 0; i < length; ++i)
    {
        if (std::get<0>(data[i]) == e)
        {
            ++std::get<1>(data[i]);
            return;
        }
    }
    // Append case
    if ((length + 1) > capacity)
    {
        capacity = (length + 1) << 1;
        auto* new_data = new std::tuple<TElem, int>[capacity];
        for (int i = 0; i < length; ++i)
        {
            new_data[i] = data[i];
        }
        if (data != nullptr)
        {
            delete[] data;
        }
        data = new_data;
    }
    data[++length - 1] = std::make_tuple(e, 1);
    // Keep the bag sorted
    for (int i = length - 1; i > 0; --i)
    {
        if (!relation(std::get<0>(data[i - 1]), std::get<0>(data[i])))
        {
            auto temp = data[i - 1];
            data[i - 1] = data[i];
            data[i] = temp;
        }
    }
}


bool SortedBag::remove(TComp e)
{
    for (int i = 0; i < length; ++i)
    {
        if (std::get<0>(data[i]) == e)
        {
            --element_count;
            --std::get<1>(data[i]);
            if (std::get<1>(data[i]) == 0)
            {
                for (int j = i + 1; j < length; ++j)
                {
                    data[j - 1] = data[j];
                }
                if (--length == 0)
                {
                    delete[] data;
                    data = nullptr;
                    capacity = 0;
                }
                if ((length << 2) < capacity)
                {
                    capacity = length << 1;
                    std::tuple<TElem, int>* new_data = new std::tuple<TElem, int>[capacity];
                    for (int i = 0; i < length; ++i)
                    {
                        new_data[i] = data[i];
                    }
                    delete[] data;
                    data = new_data;
                }
            }
            return true;
        }
    }
    return false;
}

bool SortedBag::search(TComp elem) const
{
    int left = 0, right = length - 1;
    while (left <= right)
    {
        const int middle = (left + right) / 2;
        if (relation(std::get<0>(data[middle]), elem) || std::get<0>(data[middle]) == elem)
        {
            left = middle + 1;
        }
        else
        {
            right = middle - 1;
        }
    }

    if (right < 0)
    {
        return false;
    }

    return std::get<0>(data[right]) == elem;
}


int SortedBag::nrOccurrences(TComp elem) const
{
    int left = 0, right = length - 1;
    while (left <= right)
    {
        const int middle = (left + right) / 2;
        if (relation(std::get<0>(data[middle]), elem) || std::get<0>(data[middle]) == elem)
        {
            left = middle + 1;
        }
        else
        {
            right = middle - 1;
        }
    }

    if (right < 0)
    {
        return 0;
    }

    if (std::get<0>(data[right]) == elem)
    {
        return std::get<1>(data[right]);
    }

    return 0;
}



int SortedBag::size() const
{
    return element_count;
}


bool SortedBag::isEmpty() const
{
    return element_count == 0;
}


SortedBagIterator SortedBag::iterator() const
{
	return SortedBagIterator(*this);
}

CustomSortedBagIterator SortedBag::custom_iterator(int start, int step) const
{
    return CustomSortedBagIterator(*this, start, step);
}

SortedBag::~SortedBag()
{
    if (data != nullptr)
    {
        delete[] data;
    }
}
