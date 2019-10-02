#pragma once

// From: https://raw.githubusercontent.com/Arandur/prog3B/master/src/Int.h

#include <iostream>
#include <cstdint>

class Int
{
public:
	Int();
	Int( const int& );
	Int( const Int& );
	
	Int operator +  ( const Int& ) const;
	Int operator -  ( const Int& ) const;
	Int operator *  ( const Int& ) const;
	Int operator /  ( const Int& ) const;
	Int operator %  ( const Int& ) const;
	
	Int& operator  = ( const Int& );
	Int& operator += ( const Int& );
	Int& operator -= ( const Int& );
	Int& operator *= ( const Int& );
	Int& operator /= ( const Int& );
	Int& operator %= ( const Int& );
	
	bool operator == ( const Int& ) const;
	bool operator != ( const Int& ) const;
	bool operator <  ( const Int& ) const;
	bool operator <= ( const Int& ) const;
	bool operator >  ( const Int& ) const;
	bool operator >= ( const Int& ) const;
	
	Int& operator ++ ();
	Int operator ++ ( int );
	Int& operator -- ();
	Int operator -- ( int );
	
	operator int();
	operator int() const;
	
	friend std::istream& operator >> ( std::istream&, Int& );
	
private:
	int8_t _i;
};
