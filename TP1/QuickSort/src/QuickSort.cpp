#ifndef QUICKSORT_CPP
#define QUICKSORT_CPP

#include <cassert>
#include <iostream>
#include <cstddef>
#include <cstdlib>
#include <ctime>
#include <time.h>
#include <cstring>

typedef int type_t;

#include "../include/quickSort.hpp"

void swap ( type_t * x, type_t * y ) {
    type_t temp = *x;
    *x = *y;
    *y = temp;
}

size_t partition ( type_t * array, size_t low, size_t high ) {
    size_t i = low + 1;
    size_t j = high;
    type_t mid = low + ( high - low ) / 2;

    swap( &array[ low ], &array[ mid ] );

    while ( true ) {
        while ( array[ i ] <= array[ low ] && i < high ) {
            i += 1;
        }
        while ( array[ j ] > array[ low ] ) {
            j -= 1;
        }
        if ( i >= j ) {
            break;
        }
        swap( &array[ i ], &array[ j ] );
    }
    swap( &array[ low ], &array[ j ] );
    return j;
}

void _quickSort ( type_t * array, size_t low, size_t high ) {
    if ( high > low ) {
        size_t p = partition( array, low, high );
        if ( p > 0 ) {
            _quickSort( array, low, p - 1 );
        }
        _quickSort( array, p + 1, high );
    }
}

void quickSort ( type_t * array, size_t size ) {
    _quickSort( array, 0, size - 1 );
}

void printArray ( const type_t * array, size_t size ) {
    std::cout << "[ ";
    for ( size_t i = 0; i < size; i++ ) {
        std::cout << array[ i ] << ( ( i + 1 ) == size ? " ]" : " " );
    }
    std::cout << std::endl;
}

void initializeArray ( type_t * array, size_t size, SortingType type ) {
    switch ( type ) {
        case ORDENADO:
            for ( size_t i = 0; i < size; i++ ) {
                array[ i ] = i;
            }
            break;
        case DESORDENADO:
            for ( size_t i = 0; i < size; i++ ) {
                array[ i ] = rand() % size;
            }
            break;
        case INVERSAMENTE_ORDENADO:
            for ( size_t i = 0; i < size; i++ ) {
                array[ i ] = size - i;
            }
            break;
        case PARCIALMENTE_ORDENADO:
            for ( size_t i = 0; i < size; i++ ) {
                array[ i ] = i;
            }
            for ( size_t i = 0; i < size / 2; i++ ) {
                size_t j = rand() % size;
                swap( &array[ i ], &array[ j ] );
            }
            break;
    }
}

bool isSorted ( const type_t * array, size_t size ) {
    for ( size_t i = 1; i < size; i++ ) {
        if ( array[ i ] < array[ i - 1 ] ) {
            return false;
        }
    }
    return true;
}

void test ( size_t size, SortingType type, bool print ) {
    double tstart = 0.0, tend = 0.0;
    type_t * array = nullptr;
    const double MICROSECS = ( ( CLOCKS_PER_SEC / 1000000.0 ) );

    srand( 0 );

    array = new type_t[ size ];
    assert( array != nullptr );
    initializeArray( array, size, type );

    if ( print ) {
        std::cout << "Array desordenado: ";
        printArray( array, size );
    }

    tstart = clock();
    quickSort( array, size );
    tend = clock();

    std::cout << "Quick Sort: " << ( tend - tstart ) / MICROSECS << " us" << std::endl;

    if ( print ) {
        std::cout << "Array ordenado: ";
        printArray( array, size );
    }

    assert( isSorted( array, size ) );
    delete[] array;
}

void usage ( char * const argv[] ) {
    std::cout << argv[0] << "Testando programa para o Quick Sort." << std::endl;
    std::cout << "Uso: " << argv[0] << " [--verbose] <tamanho-do-array> [--tipo-de-ordenacao]" << std::endl;
    std::cout << "Tipos de ordenacao disponiveis: ordenado, desordenado, parcialmente-ordenado, inversamente-ordenado" << std::endl;
    exit( EXIT_FAILURE );
}

int main ( int argc, char * argv[] ) {
    size_t size = 0;
    SortingType type = DESORDENADO;
    bool print = false;

    if ( argc < 2 || argc > 4 ) {
        std::cerr << "Erro: numero de argumentos invalido." << std::endl;
        usage( argv );
    }

    if ( argc == 2 ) {
        size = atoi( argv[ 1 ] );
    } else if ( argc == 3 ) {
        if ( !strcmp( argv[ 1 ], "--verbose" ) ) {
            print = true;
            size = atoi( argv[ 2 ] );
        } else {
            size = atoi( argv[ 1 ] );
            if ( !strcmp( argv[ 2 ], "--ordenado" ) ) {
                type = ORDENADO;
            } else if ( !strcmp( argv[ 2 ], "--desordenado" ) ) {
                type = DESORDENADO;
            } else if ( !strcmp( argv[ 2 ], "--parcialmente-ordenado" ) ) {
                type = PARCIALMENTE_ORDENADO;
            } else if ( !strcmp( argv[ 2 ], "--inversamente-ordenado" ) ) {
                type = INVERSAMENTE_ORDENADO;
            } else {
                std::cerr << "Erro: tipo de ordenacao invalido." << std::endl;
                usage( argv );
            }
        }
    } else if ( argc == 4 ) {
        print = true;
        size = atoi( argv[ 2 ] );
        if ( !strcmp( argv[ 3 ], "--ordenado" ) ) {
            type = ORDENADO;
        } else if ( !strcmp( argv[ 3 ], "--desordenado" ) ) {
            type = DESORDENADO;
        } else if ( !strcmp( argv[ 3 ], "--parcialmente-ordenado" ) ) {
            type = PARCIALMENTE_ORDENADO;
        } else if ( !strcmp( argv[ 3 ], "--inversamente-ordenado" ) ) {
            type = INVERSAMENTE_ORDENADO;
        } else {
            std::cerr << "Erro: tipo de ordenacao invalido." << std::endl;
            usage( argv );
        }
    } else {
        std::cerr << "Erro: argumentos invalidos." << std::endl;
        usage( argv );
    }

    test( size, type, print );

    return( EXIT_SUCCESS );
}

#endif //QUICKSORT_CPP