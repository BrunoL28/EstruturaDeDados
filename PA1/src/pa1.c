//---------------------------------------------------------------------
// Arquivo      : evalenum.c
// Conteudo     : avaliacao de desempenho de algoritmos de ordenacao 
// Autor        : Wagner Meira Jr. (meira@dcc.ufmg.br)
// Historico    : 2023-11-04 - arquivo criado
//---------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <unistd.h>

#define ALGINSERTION 1
#define ALGSELECTION 2
#define ALGQSORT     3
#define ALGQSORT3    4
#define ALGQSORTINS  5
#define ALGQSORT3INS 6
#define ALGSHELLSORT 7
#define ALGRECSEL    8

typedef struct alg {
    int num;
    char * name;
} alg_t;

alg_t algvet[] = {
    {ALGINSERTION,"i"},
    {ALGSELECTION,"s"},
    {ALGQSORT,"q"},
    {ALGQSORT3,"q3"},
    {ALGQSORTINS,"qi"},
    {ALGQSORT3INS,"q3i"},
    {ALGSHELLSORT,"h"},
    {ALGRECSEL,"rs"},
    {0,0}
};

int name2num ( char * name ) {
    int i=0;
    while ( algvet[ i ].num ) {
        if ( !strcmp( algvet[ i ].name,name) ) return algvet[ i ].num;
        i++;
    }
    return 0;
}

char * num2name ( int num ) {
    int i=0;
    while ( algvet[ i ].num ) {
        if ( algvet[ i ].num==num) return algvet[ i ].name;
        i++;
    }
    return 0;
}

typedef struct opt {
    int size;
    int seed;
    int alg;
} opt_t;

typedef struct sortperf {
    int cmp;
    int move;
    int calls;
} sortperf_t;

void resetcounter ( sortperf_t * perf ) {
    perf->cmp = 0;
    perf->move = 0;
    perf->calls = 0;
}

void inccmp ( sortperf_t * perf, int num ) {
    perf->cmp += num;
}

void incmove ( sortperf_t * perf, int num ) {
    perf->move += num;
}

void inccalls ( sortperf_t * perf, int num ) {
    perf->calls += num;
}

char * printsortperf ( sortperf_t * perf, char * str, char * pref ) {
    sprintf( str, "%s cmp %d move %d calls %d", pref, perf->cmp, perf->move, perf->calls );
    return str;
}

void initVector ( int * vet, int size ) {
    int i;
    for ( i = 0; i < size; i++ ) {
        vet[ i ] = ( int )( drand48()*size );
    }
}

void printVector ( int * vet, int size ) {
    int i;
    for ( i = 0; i < size; i++ ) {
        printf( "%d ", vet[ i ] );
    }
    printf( "\n" );
}

void swap ( int * x, int * y, sortperf_t * perf ) {
    int aux = *x;
    *x = *y;
    *y = aux;
    incmove( perf, 3 );
}

void shellSort ( int * A, int n, sortperf_t * perf ) {
    inccalls( perf, 1 );
    int aux = 0, j = 0;
    for ( int gap = n/2; gap > 0; gap /= 2 ) {
        for ( int i = gap; i < n; i++ ) {
            inccmp( perf, 1 );
            aux = A[ i ];
            incmove( perf, 1 );
            j = i;
            while ( j >= gap && A[ j - gap ] > aux ) {
                inccmp( perf, 1 );
                A[ j ] = A[ j - gap ];
                incmove( perf, 1 );
                j -= gap;
            }
            A[ j ] = aux;
            incmove( perf, 1 );
        }
    }
}

void recursiveSelectionSort ( int * A, int l, int r, sortperf_t * perf ) {
    int min = l;
    inccalls( perf, 1 );
    for ( int j = l + 1; j <= r; j++ ) {
	    inccmp( perf, 1 );
        if ( A[ j ] < A[ min ] ) {
            min = j;
        }
    }
    if ( min != l )
      swap( &A[ min ], &A[ l ], perf );
    if ( l + 1 < r ) {
        recursiveSelectionSort( A, l + 1, r, perf );
    }
}

void selectionSort ( int * A, int l, int r, sortperf_t * perf ) {
    inccalls( perf, 1 );
    for ( int i = l; i < r; i++ ) {
        int min_index = i;
        for ( int j = i + 1; j <= r; j++ ) {
            inccmp( perf, 1 );
            if ( A[ j ] < A[ min_index ] ) {
                min_index = j;
            }
        }
        if ( min_index != i ) {
            swap( &A[ i ], &A[ min_index ], perf );
        }
    }
}

void insertionSort( int * A, long long int l, long long int r, sortperf_t * perf ) {
    inccalls( perf, 1 );
    int i = 0, j = 0, tmp = 0;
    for ( i = l + 1; i <= r; i++ ) {
        inccmp( perf, 1 );
        tmp = A[ i ];
        incmove( perf, 1 );
        j = i - 1;
        while ( j > -1 && A[ j ] > tmp ) {
            inccmp( perf, 1 );
            A[ j + 1 ] = A[ j ];
            incmove( perf, 1 );
            j--;
        }
        A[ j + 1 ] = tmp;
        incmove( perf, 1 );
    }
}

int median ( int a, int b, int c ) {
    if ( ( a <= b ) && ( b <= c ) ) {
        return b;
    }  // a b c
    if ( ( a <= c ) && ( c <= b ) ) {
        return c;
    }  // a c b
    if ( ( b <= a ) && ( a <= c ) ) {
        return a;
    }  // b a c
    if ( ( b <= c ) && ( c <= a ) ) {
         return c;
    }  // b c a
    if ( ( c <= a ) && ( a <= b ) ) {
        return a;
    }  // c a b
    return b;  // c b a
}

void partition( int * A, int l, int r, int * i, int * j, sortperf_t * perf ) {
    inccalls( perf, 1 );
    *i = l;
    *j = r;
    int tmp;
    int x = A[ ( *i + *j ) / 2 ]; 

    do {
        inccmp( perf, 1 );
        while ( *i < r && x > A[ *i ] ) {
            inccmp( perf, 1 );
            ( *i )++;
        }
        while ( l < *j && x < A[ *j ] ) {
            inccmp( perf, 1 );
            ( *j )--;
        }
        inccmp( perf, 1 );
        if ( *i <= *j ) {
            swap( &A[ *i ], &A[ *j ], perf );
            ( *i )++;
            ( *j )--;
        }
    } while ( *i <= *j );
}

void quickSort ( int * A, int l, int r, sortperf_t * perf ) {
    inccalls( perf, 1 );
    if ( l < r ) {
        int i, j;
        partition( A, l, r, &i, &j, perf );
        if ( l < j ) {
            quickSort( A, l, j, perf );
        }
        if ( i < r ) {
            quickSort( A, i, r, perf );
        }
    }
}

void partition3 ( int * A, int l, int r, int * i, int * j, sortperf_t * perf ) {
    inccalls( perf, 1 );
    *i = l;
    *j = r;
    int x = median( A[ l ], A[ ( *i + *j ) / 2 ], A[ r ]);

    do {
        inccmp( perf, 1 );
        while ( *i < r && x > A[ *i ] ) {
            inccmp( perf, 1 );
            ( *i )++;
        }
        while ( l < *j && x < A[ *j ] ) {
            inccmp( perf, 1 );
            ( *j )--;
        }
        inccmp( perf, 1 );
        if ( *i <= *j ) {
            swap( &A[ *i ], &A[ *j ], perf );
            ( *i )++;
            ( *j )--;
        }
    } while ( *i <= *j );
}

void quickSort3 ( int * A, int l, int r, sortperf_t * perf ) {
    inccalls( perf, 1 );
    if ( l < r ) {
        int i, j;
        partition3( A, l, r, &i, &j, perf );
        if ( l < j ) {
            quickSort3( A, l, j, perf );
        }
        if ( i < r ) {
            quickSort3( A, i, r, perf );
        }
    }
}

void quickSortIns ( int * A, int l, int r, sortperf_t * perf ) {
    inccalls( perf, 1 );
    if ( l < r ) {
        int i = l, j = r;
        partition( A, l, r, &i, &j, perf );
        if ( j - l <= 50 ) {
            if ( l < j ) {
                insertionSort( A, l, j, perf );
            }
        } else {
            quickSortIns( A, l, j, perf );
        }
        if ( r - i <= 50 ) {
            if ( i < r ) {
                insertionSort( A, i, r, perf );
            }
        } else {
            quickSortIns( A, i, r, perf );
        }
    }
}

void quickSort3Ins ( int * A, int l, int r, sortperf_t * perf ) {
    inccalls( perf, 1 );
    if ( l < r ) {
        int i = l, j = r;
        partition3( A, l, r, &i, &j, perf );
        if ( j - l <= 50 ) {
            if ( l < j ) {
                insertionSort( A, l, j, perf );
            }
        } else {
            quickSort3Ins( A, l, j, perf );
        }
        if ( r - i <= 50 ) {
            if ( i < r ) {
                insertionSort( A, i, r, perf );
            }
        } else {
            quickSort3Ins( A, i, r, perf );
        }
    }
}

void uso() {
  fprintf(stderr,"sortperf\n");
  fprintf(stderr,"\t-z <int>\t(vector size)\n");
  fprintf(stderr,"\t-s <int>\t(initialization seed)\n");
  fprintf(stderr,"\t-a <s|i|q|q3|qi|q3i|h|rs>\t(algorithm)\n");
  fprintf(stderr,"\t    s\tselection\n");
  fprintf(stderr,"\t    i\tinsertion\n");
  fprintf(stderr,"\t    q\tquicksort\n");
  fprintf(stderr,"\t    q3\tquicksort+median3\n");
  fprintf(stderr,"\t    qi\tquicksort+insertion\n");
  fprintf(stderr,"\t    q3i\tquicksort+median3+insertion\n");
  fprintf(stderr,"\t    h\theapsort\n");
  fprintf(stderr,"\t    rs\trecursive selection\n");
}

void parse_args(int argc, char ** argv, opt_t * opt) {
    extern char * optarg;
    extern int optind;

    int c;

    opt->seed = 1;
    opt->size = 10;
    opt->alg = 1;

    while ( ( c = getopt( argc, argv, "z:s:a:h" ) ) != EOF ) {
        switch( c ) {
            case 'z':
                opt->size = atoi( optarg );
                break;
            case 's':
                opt->seed = atoi( optarg );
                break;
            case 'a':
            opt->alg = name2num( optarg );
                break;
            case 'h':
            default:
                uso();
                exit(1);
        }
    }
    if ( !opt->alg ) {
        uso();
        exit(1);
    }
}

void clkDiff( struct timespec t1, struct timespec t2, struct timespec * res) {
    if ( t2.tv_nsec < t1.tv_nsec ) {
        res-> tv_nsec = 1000000000+t2.tv_nsec-t1.tv_nsec;
        res-> tv_sec = t2.tv_sec-t1.tv_sec-1;
    } else {
        res-> tv_nsec = t2.tv_nsec-t1.tv_nsec;
        res-> tv_sec = t2.tv_sec-t1.tv_sec;
    }
}
    
int main ( int argc, char ** argv ) {
    sortperf_t s;
    int * vet;
    char buf[ 200 ];
    char pref[ 100 ];
    opt_t opt;
    struct timespec inittp, endtp, restp;
    int retp;

    parse_args( argc, argv, &opt );

    vet = (int *) malloc((opt.size+1)*sizeof(int));

    resetcounter(&s);
    srand48(opt.seed);
    initVector(vet, opt.size);
    vet[opt.size] = vet[0]; // for heapsort

    retp = clock_gettime( CLOCK_MONOTONIC, &inittp );

    switch ( opt.alg ) {
        case ALGINSERTION:
            insertionSort( vet, 0, opt.size-1, &s );
            break;
        case ALGSELECTION:
            selectionSort( vet, 0, opt.size-1, &s );
            break;
        case ALGQSORT:
            quickSort( vet, 0, opt.size-1, &s );
            break;
        case ALGQSORT3:
            quickSort3( vet, 0, opt.size-1, &s );
            break;
        case ALGQSORTINS:
            quickSortIns( vet, 0, opt.size-1, &s );
            break;
        case ALGQSORT3INS:
            quickSort3Ins( vet, 0, opt.size-1, &s );
            break;
        case ALGSHELLSORT:
            shellSort( vet, opt.size, &s );
            break;
        case ALGRECSEL:
            recursiveSelectionSort( vet, 0, opt.size-1, &s );
            break;
    }

    retp = clock_gettime( CLOCK_MONOTONIC, &endtp );
    clkDiff( inittp, endtp, &restp );


    //if (opt.size<100) printVector(vet, opt.size);

    sprintf(pref, "alg %s seed %d size %d time %ld.%.9ld", num2name(opt.alg), opt.seed,opt.size,restp.tv_sec,restp.tv_nsec);

    printsortperf( &s, buf, pref );
    printf( "%s\n", buf );

    exit( 0 );
}
