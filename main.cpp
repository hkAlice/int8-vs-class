#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <cstdint>
#include <algorithm>
#include <chrono>
#include <tuple>
#include <cassert>

#include "libs/termcolor/termcolor.hpp"

#include "Int.h"
#include "benchInt.h"

#include "type.h"

std::string getPercentageDiff( std::chrono::system_clock::time_point t1, std::chrono::system_clock::time_point t2,
                               std::chrono::system_clock::time_point t3, std::chrono::system_clock::time_point t4 )
{
    std::chrono::duration< double > eTime1 = std::chrono::duration_cast< std::chrono::milliseconds >( t2 - t1 );
    std::chrono::duration< double > eTime2 = std::chrono::duration_cast< std::chrono::milliseconds >( t4 - t3 );

    auto f1 = eTime1.count();
    auto f2 = eTime2.count();

    double diff = ( ( f2 - f1 ) * 100 ) / f1;
    std::stringstream sstr;

    sstr << " (" << std::setprecision( 2 ) << std::fixed << diff << "%)";

    sstr << termcolor::reset;

    return sstr.str();
}

std::string getPrettyTime( std::chrono::system_clock::time_point t1, std::chrono::system_clock::time_point t2 )
{
    std::chrono::duration< double > elapsedTime = std::chrono::duration_cast< std::chrono::milliseconds >( t2 - t1 );
    std::stringstream sstr;

    sstr << std::setprecision( 2 ) << std::fixed << elapsedTime.count() << "s>";

    return " <elapsed: " + sstr.str();
}

template< typename T1, typename T2 >
static void benchCall( std::function< void() > func1, std::function< void() > func2,
                       const std::string& funcName, bool parity = true )
{
    std::cout << termcolor::yellow << __PRETTY_FUNCTION__ << "\n" << termcolor::reset;
    std::cout << termcolor::cyan << funcName << termcolor::reset 
              << "\nT1 = " + demangle( typeid( T1 ).name() ) + ", T2 = " + demangle( typeid( T2 ).name() ) 
              << termcolor::reset;


    auto t1 = std::chrono::system_clock::now();

    func1();
    
    auto t2 = std::chrono::system_clock::now();

    std::cout << "\n[T1] OK"
              << termcolor::magenta << getPrettyTime( t1, t2 ) << termcolor::reset;

    auto t3 = std::chrono::system_clock::now();

    func2();
    
    auto t4 = std::chrono::system_clock::now();

    std::cout << "\n[T2] OK"
              << termcolor::magenta << getPrettyTime( t3, t4 ) << termcolor::reset;

    std::cout << "\ndiff =" << getPercentageDiff( t1, t2, t3, t4 ) + "\n";
}

int main()
{
    // NOTE: if on windows, make sure to either 
    // 1. adjust stack size so this doesn't blow (stack size is smaller on windows)
    // 2. reduce intCount

    std::vector< int8_t > _int8N;
    std::vector< Int > _int8C;

    const size_t intCount = 4096 * 4096 * 4;

    auto t1 = std::chrono::system_clock::now();

    for( int i = 0; i < intCount; ++i )
    {
        _int8N.push_back( 0 );
    }

    auto t2 = std::chrono::system_clock::now();
    
    std::cout << "Finished initializing ints(int8_t)" << getPrettyTime( t1, t2 ) + "\n";

    auto t3 = std::chrono::system_clock::now();

    for( int i = 0; i < intCount; ++i )
    {
        _int8C.push_back( { 0 } );
    }

    auto t4 = std::chrono::system_clock::now();

    std::cout << "Finished initializing ints(insane)" << getPrettyTime( t3, t4 ) << getPercentageDiff( t1, t2, t3, t4 ) + "\n";

    benchCall< int8_t, Int >( [&](){ BenchInt::benchSimpleAdd< int8_t >( _int8N ); }, 
                              [&](){ BenchInt::benchSimpleAdd< Int >( _int8C ); }, 
                              "benchSimpleAdd" );

    // you wouldn't cheat an int, would you?
    benchCmpVec< int8_t, Int >( _int8N, _int8C );

    benchCall< int8_t, Int >( [&](){ BenchInt::benchMulAhead< int8_t >( _int8N ); }, 
                              [&](){ BenchInt::benchMulAhead< Int >( _int8C ); }, 
                              "benchMulAhead" );

    benchCmpVec< int8_t, Int >( _int8N, _int8C );

    auto _slice_int8N = std::vector< int8_t >( _int8N.begin(), _int8N.begin() + ( 4096 * 8 ) );
    auto _slice_int8C = std::vector< Int >( _int8C.begin(), _int8C.begin() + ( 4096 * 8 ) );

    benchCall< int8_t, Int >( [&](){ BenchInt::benchBubbleSort< int8_t >( _slice_int8N ); }, 
                              [&](){ BenchInt::benchBubbleSort< Int >( _slice_int8C ); }, 
                              "benchBubbleSort (SLICED)" );

    //benchCall< int8_t, Int >( [&](){ benchQuicksort< int8_t >( _slice_int8N, 0, _slice_int8N.size() - 1 ); }, [&](){ benchQuicksort< Int >( _slice_int8C, 0, _slice_int8C.size() - 1 ); }, "benchQuicksort (SLICED)" );

    return 0;
}