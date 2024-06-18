#ifndef QUICKSORT_HPP
#define QUICKSORT_HPP

enum SortingType { 
    ORDENADO,
    DESORDENADO,
    INVERSAMENTE_ORDENADO,
    PARCIALMENTE_ORDENADO
};

void swap ( type_t * x, type_t * y );
size_t partition ( type_t * array, size_t low, size_t high );
void _quickSort ( type_t * array, size_t low, size_t high );
void quickSort ( type_t * array, size_t size );
void printArray ( const type_t * array, size_t size );
void initializeArray ( type_t * array, size_t size, SortingType type );
bool isSorted ( const type_t * array, size_t size );
void test ( size_t size, SortingType type, bool print );

#endif //QUICKSORT_HPP