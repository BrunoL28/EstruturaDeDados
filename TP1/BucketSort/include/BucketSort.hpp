#ifndef BUCKETSORT_HPP
#define BUCKETSORT_HPP

enum SortingType {
    ORDENADO,
    DESORDENADO,
    INVERSAMENTE_ORDENADO,
    PARCIALMENTE_ORDENADO
};

void swap ( type_t * x, type_t * y );
void bucketSort ( type_t * array, size_t size, size_t bucketSize );
void printArray ( type_t * array, size_t size );
void initializeArray ( type_t * array, size_t size, SortingType type );
bool isSorted ( type_t * array, size_t size );
void test ( size_t size, SortingType type, size_t bucketSize, bool print );
void usage ( char * const argv[] );

#endif // BUCKETSORT_HPP