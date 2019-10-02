#include <iostream>
#include <string>
#include <vector>
#include <cstdint>
#include <algorithm>
#include <cassert>

namespace BenchInt
{

static bool PARITY_FAILED_PREV = false;

template< typename T >
__attribute__((__used__))
static void benchSimpleAdd( std::vector< T >& iVec )
{
    T idxOverflow = 1;
    T coeff = { 1 };

    // NOTE:
    // Internally, Int.cpp operator++ and += overload 
    // do NOT go through the switch cases, and perform the operation
    // on the private int member instead

    // ^use of + operator instead of += and ++ is intentional^

    for( T& vi : std::move( iVec ) )
    {
        //std::cout << std::to_string(idxOverflow) + " | ";
        idxOverflow = idxOverflow + coeff;
        vi = idxOverflow;
    }
}

template< typename T >
__attribute__((__used__))
static void benchSimpleMod( std::vector< T >& iVec )
{
    T coeff = { 8 };

    for( T& vi : std::move( iVec ) )
    {
        vi = vi % coeff;
    }
}

template< typename T >
__attribute__((__used__))
static void benchMulAhead( std::vector< T >& iVec )
{
    for( int i = 0; i < iVec.size() - 1; ++i )
    {
    	iVec[i] = iVec[i] * iVec[i + 1];
    }
}

template< typename T >
__attribute__((__used__))
static void benchBubbleSort( std::vector< T >& iVec )
{
    size_t vecSize = iVec.size();

    for( size_t i = 0; i < vecSize - 1; i++ )
    {
        for( size_t j = 0; j < vecSize - i - 1; j++ )
        {
            if( iVec[j] > iVec[j+1] )
            {
                T temp = iVec[j];
                iVec[j] = iVec[j+1];
                iVec[j+1] = temp;
            }
        }
    }
}

template< typename T >
__attribute__((__used__))
static void benchQuicksort( std::vector< T >& iVec, size_t head, size_t tail )
{
    std::function< size_t ( std::vector< T >&, size_t, size_t )> pivot = []( std::vector< T >& iVec, size_t pHead, size_t pTail )
    {
        T p = pHead;
        T pivotElement = iVec[pHead];

        for( int i = pHead + 1 ; i <= pTail; i++ )
        {
            if( iVec[i] <= pivotElement )
            {
                p++;
                std::swap( iVec[i], iVec[p] );
            }
        }

        std::swap( iVec[p], iVec[pHead] );

        return p;
    };

    size_t pivotElement;

    if( head < tail )
    {
        pivotElement = pivot( iVec, head, tail );
        benchQuicksort( iVec, head, pivotElement - 1 );
        benchQuicksort( iVec, pivotElement + 1, tail );

    }


}


template< typename T, typename T2 >
static void benchCmpVec( const std::vector< T >& iVec1, const std::vector< T2 >& iVec2, bool assertParity = true )
{
    // you wouldn't cheat an int, would you?
    assert( iVec1.size() == iVec2.size() );

    if( PARITY_FAILED_PREV )
    {
    	std::cout << "Parity failed previously\n";
    	if( assertParity )
    		assert( PARITY_FAILED_PREV );
    }

    bool _parity = true;
    for( size_t i = 0; i < iVec1.size(); ++i )
    {
        //std::cout << std::to_string( iVec1[1] ) + ", ";
        _parity = iVec1[i] == iVec2[i];
        if( !_parity )
        {
        	PARITY_FAILED_PREV = true;
            std::cout << "Failed to match parity (" + std::to_string( iVec1[i] ) + ", " + std::to_string( iVec2[i] ) + ")\n";
            if( assertParity )
                assert( _parity );
            break;
        }
    }
}

}