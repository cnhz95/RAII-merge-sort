#ifndef BUFFER_INT_SORTED_H
#define BUFFER_INT_SORTED_H

#include "int_buffer.h"
#include <cstddef>

// Klassen ska inte hantera något dynamiskt minne, det sköter buffern

class int_sorted {
public:
    int_sorted() = delete; // Anger explicit att ingen defaultkonstruktor ska finnas
    int_sorted(const int* source, size_t size);
    size_t size() const;
    int* insert(int value);
    const int* begin() const;
    const int* end() const;
    int_sorted merge(const int_sorted& merge_with) const;

private:
    int_sorted sort(const int* begin, const int* end);

    int_buffer m_buf;
};

#endif