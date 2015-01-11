/* 
*  Kevin Meergans, Improved Lego Editor, 2014
*  GridMeshDataStructures.h
*  Contains the structure of a vertex used to draw the editor geometry, that is
*  grid and cursor.
*/

#ifndef EDITOR_GEOMETRY_DATA_STRUCTURES_H
#define EDITOR_GEOMETRY_GRID_DATA_STRUCTURES_H

//#include <d3d11.h>
#include <windows.h>
#include <xnamath.h>

//--------------------------------------------------------------------------------------
// The structure of a vertex used for the grid in the application.
//--------------------------------------------------------------------------------------
struct SimpleVertex
{
	SimpleVertex() : m_position( 0, 0, 0 ) {}
	SimpleVertex( float posX, float posY, float posZ ) : m_position( posX, posY, posZ ) {}

	XMFLOAT3 m_position;		// position of the vertex
};

#endif