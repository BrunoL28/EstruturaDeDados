#ifndef INSERTIONSORT_HPP
#define INSERTIONSORT_HPP

enum SortingType {
    ORDENADO,
    DESORDENADO,
    INVERSAMENTE_ORDENADO,
    PARCIALMENTE_ORDENADO
};

void swap ( type_t * x, type_t * y );
void insertionSort ( type_t * array, size_t size );
void printArray ( const type_t * array, size_t size );
void initializeArray ( type_t * array, size_t size, SortingType type );
bool isSorted ( const type_t * array, size_t size );
void test ( size_t size, SortingType type, bool print );
void usage ( char * const argv[] );

#endif //INSERTIONSORT_HPP