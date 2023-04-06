/**
 * Safely contain multiple elements of the same type.
 *
 * USAGE:
 *  Array<int> numbers;
 *  numbers.append(0);
 *  for (uint8_t i = 0; i < numbers.size(); i++) {
 *      numbers[0] += 1;
 *  }
 *
 * Team #4546
 *  \author Catalina Andrea Araya Figueroa
 *  \author Mehdi Benouhoud
 *  \author Laurent Bourgon
 *  \author Ihsane Majdoubi
 *
 * \date March 24, 2023
 */

#ifndef ARRAY_H
#define ARRAY_H

#include <avr/io.h>
#include <stdlib.h>

template <typename Element, uint8_t maximumSize = 32>
class Array
{
public:
    Array() = default;

    Array(Element elements[], uint8_t nElements)
    {
        for (uint8_t i = 0; i < nElements; i++) {
            append(elements[i]);
        }
    }

    Element &operator[](const uint8_t rowIndex)
    {
        return elements_[rowIndex];
    }

    const Element &operator[](const uint8_t rowIndex) const
    {
        return elements_[rowIndex];
    }

    void append(const Element &point)
    {
        elements_[nElements_] = point;
        nElements_++;
    }

    void remove()
    {
        nElements_--;
    }

    uint8_t size() const
    {
        return nElements_;
    }

    void sort(__compar_fn_t sortFunction)
    {
        qsort(elements_, nElements_, sizeof(Element), sortFunction);
    }

private:
    Element elements_[maximumSize];
    uint8_t nElements_ = 0;
};

#endif
