#ifndef BUBBLESORT_HPP
#define BUBBLESORT_HPP

enum SortingType {
    ORDENADO,
    DESORDENADO,
    INVERSAMENTE_ORDENADO,
    PARCIALMENTE_ORDENADO
};

static void swap ( type_t * x, type_t * y );
static void bubbleSorting( type_t array[], size_t size );
static void printArray( const type_t array[], size_t size );
static void initializeArray( type_t array[], size_t size, SortingType type );
static bool isSorted( const type_t array[], size_t size );
static void test( size_t size, SortingType type, bool print );
static void usage( char * const argv[] );

#endif //BUBBLESORT_HPP