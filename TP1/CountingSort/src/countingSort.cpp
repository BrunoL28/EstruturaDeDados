#ifndef COUNTINGSORT_CPP
#define COUNTINGSORT_CPP

typedef int type_t;
typedef type_t key_t;

#include <cassert>
#include <iostream>
#include <cstddef>
#include <cstdlib>
#include <ctime>
#include <time.h>
#include <cstring>

#include "../include/countingSort.hpp"

void swap ( type_t * x, type_t * y ) {
    type_t temp = * x;
    * x = * y;
    * y = temp;
}

key_t key ( const type_t * x ) {
    return ((key_t)(*x));
}

void countingSort ( type_t * array, size_t size ) {
    type_t * aux = nullptr;
    size_t * count = nullptr;
    size_t countlen = 1;
    key_t max = key( &array[ 0 ] );

    aux = new type_t[ size ];
    assert( aux != nullptr );

    for ( size_t i = 1; i < size; i++ ) {
        if ( max < key( &array[ i ] ) ) {
            max = key( &array[ i ] );
        }
    }

    countlen = static_cast<size_t>( max + 1 );
    count = new size_t[ countlen ]();
    assert( count != nullptr );

    for ( size_t i = 0; i < size; i++ ) {
        key_t k = key( &array[ i ] );
        count[ k ] += 1;
    }

    for ( size_t i = 1; i < countlen; i++ ) {
        count[ i ] += count[ i - 1 ];
    }

    for ( size_t i = size; i > 0; i-- ) {
        key_t k = key( &array[ i - 1 ] );
        count[ k ] -= 1;
        aux[ count[ k ] ] = array[ i - 1 ];
    }

    for ( size_t i = 0; i < size; i++ ) {
        array[ i ] = aux[ i ];
    }

    delete[] count;
    delete[] aux;
}

void printArray ( type_t * array, size_t size ) {
    std::cout << "[ ";
    for ( size_t i = 0; i < size; i++ ) {
        std::cout << array[ i ] << ( ( i + 1 ) == size ? " ]" : " " );
    }
    std::cout << std::endl;
}

void initializeArray( type_t * array, size_t size, SortingType type ) {
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

bool isSorted( const type_t * array, size_t size ) {
    for ( size_t i = 1; i < size; i++ ) {
        if ( array[ i ] < array[ i - 1 ] ) {
            return false;
        }
    }
    return true;
}

void test( size_t size, SortingType type, bool print ) {
    double tstart = 0.0, tend = 0.0;
    type_t * array = nullptr;
    const double MICROSECS = ( ( CLOCKS_PER_SEC / 1000000.0 ) );

    srand( 0 );

    array = new type_t[ size ];
    assert( array != nullptr );
    initializeArray( array, size, type );

    if ( print ) {
        std::cout << "Array antes da ordenacao: ";
        printArray( array, size );
    }

    tstart = clock();
    countingSort( array, size );
    tend = clock();

    std::cout << "Counting Sort: " << ( tend - tstart ) / MICROSECS << " microssegundos" << std::endl;

    if ( print ) {
        std::cout << "Array depois da ordenacao: ";
        printArray( array, size );
    }

    assert( isSorted( array, size ) );

    delete[] array;

}

void usage( char * const argv[] ) {
    std::cout << argv[0] << "Testando programa para o Counting Sort." << std::endl;
    std::cout << "Uso: " << argv[0] << " [--verbose] <tamanho-do-array> [--tipo-de-ordenacao]" << std::endl;
    std::cout << "Tipos de ordenacao disponiveis: ordenado, desordenado, parcialmente-ordenado, inversamente-ordenado" << std::endl;
    exit( EXIT_FAILURE );
}

int main ( int argc, char * const argv[] ) {
    size_t size = 0;
    bool print = false;
    SortingType type = DESORDENADO;

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

    return EXIT_SUCCESS;
}

#endif //COUNTINGSORT_CPP