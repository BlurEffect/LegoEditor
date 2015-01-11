/* 
*  Kevin Meergans, Improved Lego Editor, 2014
*  LegoWorldDataStructures.h
*  Contains data structures used by the lego world.
*/

#ifndef COMMON_DATA_STRUCTURES_H
#define COMMON_DATA_STRUCTURES_H

#include <windows.h>
#include <xnamath.h>

//--------------------------------------------------------------------------------------
// A vector made up of three integer numbers
//--------------------------------------------------------------------------------------
struct IntVector3
{
	IntVector3( void ) : m_x( 0 ), m_y ( 0 ), m_z( 0 ) {} 
	IntVector3( int x, int y, int z ) : m_x( x ), m_y ( y ), m_z( z ) {}
	int m_x;
	int m_y;
	int m_z;

	bool operator==( const IntVector3& vector )
	{
		return ( this -> m_x == vector.m_x ) &&
			   ( this -> m_y == vector.m_y ) &&
			   ( this -> m_z == vector.m_z );
	}
};


#endif