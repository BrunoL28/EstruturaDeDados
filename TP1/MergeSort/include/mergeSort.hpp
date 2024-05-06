#ifndef MERGESORT_HPP
#define MERGESORT_HPP

enum SortingType {
    ORDENADO,
    DESORDENADO,
    INVERSAMENTE_ORDENADO,
    PARCIALMENTE_ORDENADO
};

void swap ( type_t * x, type_t * y );
void merge ( type_t array[], type_t a[], size_t a_size, type_t b[], size_t b_size );
void _merge_Sort ( type_t aux_array[], type_t array, size_t size );
void merge_Sort ( type_t array[], size_t size );
void printArray ( const type_t array[], size_t size );
void initializeArray ( type_t array[], size_t size, SortingType type );
bool isSorted ( const type_t array[], size_t size );
void test ( size_t size, SortingType type, bool print );
void usage ( char * const argv[] );

#endif //MERGESORT_HPP