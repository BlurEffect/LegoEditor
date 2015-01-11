/* 
*  Kevin Meergans, Improved Lego Editor - Model Converter, 2014
*  ConverterDataStructures.h
*  Contains data structures used by the converter.
*/

#ifndef CONVERTER_DATA_STRUCTURES_H
#define CONVERTER_DATA_STRUCTURES_H

#include <Windows.h>
#include <xnamath.h>

//--------------------------------------------------------------------------------------
// The structure of a vertex used in the application.
//--------------------------------------------------------------------------------------
struct Vertex
{
	Vertex() : m_position( 0, 0, 0 ), m_normal( 0, 0, 0 ), m_texCoord( 0, 0 )  {}
	Vertex( float posX, float posY, float posZ, float normX, float normY, float normZ, float texU, float texV ) : m_position( posX, posY, posZ ), m_normal( normX, normY, normZ ), m_texCoord( texU, texV ){}

	XMFLOAT3 m_position;		// position of the vertex
	XMFLOAT3 m_normal;			// normal vector of the vertex
	XMFLOAT2 m_texCoord;		// texture coordinate of the vertex

	bool operator==( const Vertex& vertex ) const
	{
		return m_position.x == vertex.m_position.x &&
			   m_position.y == vertex.m_position.y &&
			   m_position.z == vertex.m_position.z &&
			   m_normal.x   == vertex.m_normal.x   &&
			   m_normal.y   == vertex.m_normal.y   &&
			   m_normal.z   == vertex.m_normal.z   &&
			   m_texCoord.x == vertex.m_texCoord.x &&
			   m_texCoord.y == vertex.m_texCoord.y;
	}
};

//--------------------------------------------------------------------------------------
// Data structure representing a face/triangle of a 3d model
//--------------------------------------------------------------------------------------
struct Face
{
	Face() : m_vertexIndex1(0), m_vertexIndex2(0), m_vertexIndex3(0),
			 m_texCoordIndex1(0), m_texCoordIndex2(0), m_texCoordIndex3(0),
			 m_normalIndex1(0), m_normalIndex2(0), m_normalIndex3(0)
	{}

	int m_vertexIndex1;
	int m_vertexIndex2;
	int m_vertexIndex3;

	int m_texCoordIndex1;
	int m_texCoordIndex2;
	int m_texCoordIndex3;

	int m_normalIndex1;
	int m_normalIndex2;
	int m_normalIndex3;
};


#endif