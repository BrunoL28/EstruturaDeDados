#ifndef BUCKETSORT_CPP
#define BUCKETSORT_CPP

#include <cassert>
#include <iostream>
#include <cstddef>
#include <cstdlib>
#include <ctime>
#include <time.h>
#include <cstring>
#include <algorithm>
#include <vector>

typedef int type_t;

#include "../include/bucketSort.hpp"

void swap ( type_t * x, type_t * y ) {
    type_t temp = * x;
    * x = * y;
    * y = temp;
}

void bucketSort ( type_t * array, size_t size, size_t bucketSize ) {
    if ( size <= 0 ) return;
    type_t minValue = array[0];
    type_t maxValue = array[0];

    for ( size_t i = 1; i < size; i++ ) {
        if ( array[i] < minValue ) {
            minValue = array[i];
        }
        if ( array[i] > maxValue ) {
            maxValue = array[i];
        }
    }
    size_t bucketCount = ( maxValue - minValue ) / bucketSize + 1;
    std::vector<std::vector<type_t>> buckets( bucketCount );

    for ( size_t i = 0; i < size; i++ ) {
        size_t bucketIndex = ( array[i] - minValue ) / bucketSize;
        buckets[bucketIndex].push_back( array[i] );
    }

    size_t currentIndex = 0;
    for ( size_t i = 0; i < bucketCount; i++ ) {
        std::sort( buckets[i].begin(), buckets[i].end() );
        for ( size_t j = 0; j < buckets[i].size(); j++ ) {
            array[currentIndex++] = buckets[i][j];
        }
    }
}

void printArray ( type_t * array, size_t size ) {
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

bool isSorted ( type_t * array, size_t size ) {
    for ( size_t i = 1; i < size; i++ ) {
        if ( array[ i ] < array[ i - 1 ] ) {
            return false;
        }
    }
    return true;
}

void test ( size_t size, SortingType type, size_t bucketSize, bool print ) {
    double tstart = 0.0, tend = 0.0;
    type_t* array = nullptr;
    const double MICROSECS = ( ( CLOCKS_PER_SEC / 1000000.0 ) );

    srand( 0 );

    array = new type_t[size];
    assert( array != nullptr );
    initializeArray( array, size, type );

    if ( print ) {
        std::cout << "Array antes da ordenacao: ";
        printArray( array, size );
    }

    tstart = clock();
    bucketSort( array, size, bucketSize );
    tend = clock();

    std::cout << "Bucket Sort: " << ( tend - tstart ) / MICROSECS << " us" << std::endl;

    if ( print ) {
        std::cout << "Array depois da ordenacao: ";
        printArray( array, size );
    }

    assert( isSorted( array, size ) );

    delete[] array;
}

void usage ( char * const argv[] ) {
    std::cout << argv[0] << " Testando programa para o Bucket Sort." << std::endl;
    std::cout << "Uso: " << argv[0] << " [--verbose] <tamanho-do-array> <tamanho-do-bucket> [--tipo-de-ordenacao]" << std::endl;
    std::cout << "Tipos de ordenacao disponiveis: ordenado, desordenado, parcialmente-ordenado, inversamente-ordenado" << std::endl;
    exit( EXIT_FAILURE );
}

int main ( int argc, char* const argv[] ) {
    size_t size = 0;
    size_t bucketSize = 1;
    bool print = false;
    SortingType type = DESORDENADO;

    if ( argc < 3 || argc > 5 ) {
        std::cerr << "Erro: numero de argumentos invalido." << std::endl;
        usage( argv );
    }

    if ( argc == 3 ) {
        size = atoi( argv[1] );
        bucketSize = atoi( argv[2] );
    } else if ( argc == 4 ) {
        if ( !strcmp( argv[1], "--verbose" ) ) {
            print = true;
            size = atoi( argv[2] );
            bucketSize = atoi( argv[3] );
        } else {
            size = atoi( argv[1] );
            bucketSize = atoi( argv[2] );
            if ( !strcmp( argv[3], "--ordenado" ) ) {
                type = ORDENADO;
            } else if ( !strcmp( argv[3], "--desordenado" ) ) {
                type = DESORDENADO;
            } else if ( !strcmp( argv[3], "--parcialmente-ordenado" ) ) {
                type = PARCIALMENTE_ORDENADO;
            } else if ( !strcmp( argv[3], "--inversamente-ordenado" ) ) {
                type = INVERSAMENTE_ORDENADO;
            } else {
                std::cerr << "Erro: tipo de ordenacao invalido." << std::endl;
                usage( argv );
            }
        }
    } else if ( argc == 5 ) {
        print = true;
        size = atoi( argv[2] );
        bucketSize = atoi( argv[3] );
        if ( !strcmp( argv[4], "--ordenado" ) ) {
            type = ORDENADO;
        } else if ( !strcmp(argv[4], "--desordenado" ) ) {
            type = DESORDENADO;
        } else if ( !strcmp(argv[4], "--parcialmente-ordenado" ) ) {
            type = PARCIALMENTE_ORDENADO;
        } else if ( !strcmp(argv[4], "--inversamente-ordenado" ) ) {
            type = INVERSAMENTE_ORDENADO;
        } else {
            std::cerr << "Erro: tipo de ordenacao invalido." << std::endl;
            usage( argv );
        }
    } else {
        std::cerr << "Erro: argumentos invalidos." << std::endl;
        usage( argv );
    }

    test(size, type, bucketSize, print);

    return EXIT_SUCCESS;
}

#endif // BUCKETSORT_CPP