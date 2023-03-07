#include "int_buffer.h"
#include "int_sorted.h"
#include <algorithm>

// Ska lämna en garanti att så fort man konstruerar ett objekt av den här typen
// så håller den reda på en uppsättning element som alltid är sorterade
// Kopieringskonstruktor. Gör sorteringen i samband med konstruktion
int_sorted::int_sorted(const int* source, size_t size) : m_buf(source, size) {
    if (size > 1) {
        int_sorted tmp = sort(source, source + size);
        m_buf = std::move(tmp.m_buf); // tmp is rvalue reference; kommer att destrueras
    }
}

size_t int_sorted::size() const {
    return m_buf.size();
}

int* int_sorted::insert(int value) {
    int_sorted tmp(&value, 1);
    m_buf = std::move(merge(tmp).m_buf);

    return std::find(m_buf.begin(), m_buf.end(), value);
}

const int* int_sorted::begin() const {
    return m_buf.begin();
}

const int* int_sorted::end() const {
    return m_buf.end();
}

int_sorted int_sorted::merge(const int_sorted & merge_with) const {
    int_buffer merged_buffer(size() + merge_with.size()); // Endast int_buffer skapar resursen. Tar size som inparameter

    const int* iter1 = begin(); // Är av typen int_sorted
    const int* iter2 = merge_with.begin();
    int* iter3 = merged_buffer.begin(); // Vi ändrar dess tillstånd. Är av typen int_buffer

    // Så länge som båda buffrar har element kvar att iterera igenom
    while (iter1 != end() && iter2 != merge_with.end()) {
        if (*iter1 < *iter2) {
            *iter3 = *iter1;
            iter1++, iter3++;
        }
        else {
            *iter3 = *iter2;
            iter2++, iter3++;
        }
    }

    // Om någon av buffrarna har element kvar
    while (iter1 != end()) {
        *iter3 = *iter1;
        iter1++, iter3++;
    }
    while (iter2 != merge_with.end()) {
        *iter3 = *iter2;
        iter2++, iter3++;
    }

    int_sorted ret(nullptr, 0); // Giltigt tillstånd
    ret.m_buf = std::move(merged_buffer);

    return ret;
}

int_sorted int_sorted::sort(const int* begin, const int* end) {
    if (begin == end) { // Tom
        return int_sorted(nullptr, 0);
    }
    if (begin == end - 1) {
        return int_sorted(begin, 1);
    }
    ptrdiff_t half = (end - begin) / 2; // Signed integer type of the result of substracting two pointers
    const int* mid = begin + half;

    return sort(begin, mid).merge(sort(mid, end));
}