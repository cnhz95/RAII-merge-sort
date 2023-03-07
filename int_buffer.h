#ifndef BUFFER_INT_BUFFER_H
#define BUFFER_INT_BUFFER_H

#include <cstddef>

// Tar ansvar för en minnesresurs. En buffer som innehåller värden av typen int
class int_buffer {
public:
    // Konstruktorer
    int_buffer() = delete; // Anger explicit att defaultkonstruerare inte ska finnas
    explicit int_buffer(size_t size);
    int_buffer(const int* source, size_t size);
    int_buffer(const int_buffer& rhs); // copy construct
    int_buffer(int_buffer&& rhs) noexcept; // move construct. rhs is an rvalue reference

    // Destruktor
    ~int_buffer();

    // Operatorer
    int_buffer& operator=(const int_buffer& rhs); // copy assign
    int_buffer& operator=(int_buffer&& rhs) noexcept; // move assign
    //int_buffer& operator=(int_buffer rhs); // rhs = copied_or_moved

    // Accessfunktioner. Ställer en direkt fråga om objektets tillstånd
    int& operator[](size_t index);
    const int& operator[](size_t index) const;
    size_t size() const;
    int* begin(); // Kan ändra innehållet i bufferten
    int* end();
    const int* begin() const;
    const int* end() const;

private:
    void swap(int_buffer& rhs);

    int* m_buffer; // En resurs som håller reda på en minnesyta
    size_t m_size;
};

#endif