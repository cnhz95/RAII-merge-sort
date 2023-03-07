#include "int_buffer.h"
#include <algorithm>
#include <cassert>

void int_buffer::swap(int_buffer& rhs) { // Kan återanvändas
    // Behöver komma åt de privata medlemmarna. Gör den till en medlemsfunktion; skickar implicit med this
    std::swap(m_buffer, rhs.m_buffer);
    std::swap(m_size, rhs.m_size);
}

// Typomvandlingskonstruerare. Enda stället som skapar resursen
int_buffer::int_buffer(size_t size) : m_size(size), m_buffer(new int[size]) {} // Resursen samt undantagsgaratier

// Skapar en kopia av en befintlig integer array, med stark undantagsgaranti via konstrueraren
int_buffer::int_buffer(const int* source, size_t size) : int_buffer(size) { // Återanvänder konstrueraren för att skapa minnesytan
    std::copy(source, source + size, m_buffer); // first, last, dest garanterad giltig pekare
}

/*
int_buffer::int_buffer(const int_buffer& rhs) : int_buffer(rhs.m_size) {
	std::copy(rhs.m_buffer, rhs.m_buffer + m_size, m_buffer);
}*/

// copy construct. Kopian måste tas från någonting som är ett lvalue
int_buffer::int_buffer(const int_buffer& rhs) : int_buffer(rhs.m_buffer, rhs.size()) {} // Återanvänder kopieraren då vi har en källa, ett antal element och en buffer

// move construct. rhs kommer att destrueras. Snor från rhs och rhs tar över det nuvarande giltiga tillståndet
int_buffer::int_buffer(int_buffer&& rhs) noexcept : m_buffer(nullptr), m_size(0) {
    swap(rhs); // Tar rhs resurs och lämnar rhs i ett giltigt tillstånd
}

// copy assign. Idiom copy-swap
int_buffer& int_buffer::operator=(const int_buffer& rhs) { // Kopian förblir orörd
    int_buffer tmp(rhs); // Skapar en kopia. tmp kommer att destrueras
    swap(tmp); // Stjäl kopian; tar ansvaret för den och lämnar den i ett giltigt tillstånd
    return *this;
}

// move assign. Ej const då vi förändrar dess interna tillstånd
int_buffer& int_buffer::operator=(int_buffer&& rhs) noexcept {
    swap(rhs);
    return *this;
}

/*
// Löser samma uppgift som de två ovan
// Kompilatorn får välja move eller copy beroende på om argumentet är ett lvalue eller ett rvalue
int_buffer& int_buffer::operator=(int_buffer rhs) {
	swap(rhs);
	return *this;
}*/

int& int_buffer::operator[](size_t index) {
    assert(index >= 0 && index < m_size);
    return m_buffer[index];
}

const int& int_buffer::operator[](size_t index) const {
    assert(index >= 0 && index < m_size);
    return m_buffer[index];
}

size_t int_buffer::size() const {
    return m_size;
}

int* int_buffer::begin() { // Kan ändra innehållet i bufferten
    return m_buffer;
}

int* int_buffer::end() {
    return m_buffer + m_size;
}

const int* int_buffer::begin() const { // Garanti att int_buffer instansen har samma tillstånd före och efter anropet
    return m_buffer;
}

const int* int_buffer::end() const {
    return m_buffer + m_size;
}

int_buffer::~int_buffer() {
    delete[] m_buffer; // Ger tillbaka resursen
}