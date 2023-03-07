#include "int_buffer.h"
#include "int_sorted.h"
#include <iostream>
#include <algorithm>
#include <chrono>

void f(int_buffer buf) {
    // Tilldelar buffern värdet 1 och uppåt
    for (int* i = buf.begin(), val = 1; i != buf.end(); i++) { // Icke-const begin och end funktionerna anropas
        *i = val++;
    }
    // Skriver ut innehållet i buffern
    for (const int* i = buf.begin(); i != buf.end(); i++) { // Icke-const begin och end funktionerna anropas
        std::cout << *i << " ";
    }
    std::cout << '\n';
}

// Eftersom range-for fungerar för alla instanser som har
// deklarationer av begin och end så fungerar den även för int_buffer
void print(const int_sorted& buf) {
    for (auto e : buf) {
        std::cout << e << " ";
    }
    std::cout << '\n';
}

void insert_random(int_sorted& buf, int size) {
    for (int i = 0; i < size; i++) {
        buf.insert(rand() % 100);
    }
}

void fill_random(int* begin, int* end) {
    for (int* i = begin; i != end; i++) {
        *i = rand();
    }
}

void selection_sort(int* begin, int* end) {
    for (int* i = begin; i != end; i++) {
        int* index_min = i;
        for (int* j = i + 1; j != end; j++) {
            if (*j < *index_min) { // Hittade ett mindre element
                index_min = j;
            }
        }
        std::swap(*i, *index_min); // Sorterar buffern ett element i taget
    }
}

int main() {
    srand(time(0));

    // Uppgift 1

    f(int_buffer(10)); // en-argumentskonstrueraren anropas



    // Uppgift 2

    int_sorted buf(nullptr, 0);
    insert_random(buf, 200);
    print(buf);



    // Uppgift 3

    constexpr int SIZE = 400000;
    int_buffer buf1(SIZE);
    fill_random(buf1.begin(), buf1.end());
    int_buffer buf2 = buf1;
    int_buffer buf3 = buf1;


    // 0,75 sekunder i snitt på 5 försök
    auto t0 = std::chrono::high_resolution_clock::now();
    std::sort(buf1.begin(), buf1.end());
    auto t1 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> time_span = t1 - t0;

    std::cout << "STL sort: " << time_span.count() << " sekunder\n";


    // 1,83 sekunder i snitt på 5 försök
    t0 = std::chrono::high_resolution_clock::now();
    int_sorted buf4(buf3.begin(), buf3.size());
    t1 = std::chrono::high_resolution_clock::now();
    time_span = t1 - t0;

    std::cout << "Merge sort: " << time_span.count() << " sekunder\n";


    // Ungefär 180 sekunder. O(n^2)
    t0 = std::chrono::high_resolution_clock::now();
    selection_sort(buf2.begin(), buf2.end());
    t1 = std::chrono::high_resolution_clock::now();
    time_span = t1 - t0;

    std::cout << "Selection sort: " << time_span.count() << " sekunder\n";

    return 0;
}