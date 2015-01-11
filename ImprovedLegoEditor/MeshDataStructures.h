/* 
*  Kevin Meergans, Improved Lego Editor, 2014
*  MeshDataStructures.h
*  Contains the structure of a vertex and mesh.
*/

#ifndef MESH_DATA_STRUCTURES_H
#define MESH_DATA_STRUCTURES_H

//#include <d3d11.h>
#include <windows.h>
#include <xnamath.h>

//--------------------------------------------------------------------------------------
// The structure of a vertex used in the application.
//--------------------------------------------------------------------------------------
struct Vertex
{
	Vertex() : m_position( 0, 0, 0 ), m_normal( 0, 0, 0 ), m_texCoord( 0, 0 )  {}
	Vertex( float posX, float posY, float posZ, float normX, float normY, float normZ, float texU, float texV ) : m_position( posX, posY, posZ ), m_normal( normX, normY, normZ ), m_sharedNormal( 0.0f, 0.0f, 0.0f ), m_texCoord( texU, texV ){}

	XMFLOAT3 m_position;		// position of the vertex
	XMFLOAT3 m_normal;			// normal vector of the vertex
	XMFLOAT3 m_sharedNormal;
	XMFLOAT2 m_texCoord;		// texture coordinate of the vertex
};

//--------------------------------------------------------------------------------------
// The structure of an instance of a mesh.
//--------------------------------------------------------------------------------------
struct Instance
{
	Instance() : m_colour( 1.0f, 1.0f, 1.0f, 1.0f ) 
	{
		XMStoreFloat4x4( &m_world, XMMatrixIdentity() );
	}
	Instance( const XMFLOAT4X4& world, const XMFLOAT4& colour ) : m_world( world ), m_colour( colour ){}

	XMFLOAT4X4 m_world;
	XMFLOAT4   m_colour;
};

//--------------------------------------------------------------------------------------
// Represents the mesh format used by the application. Objects of this type will be used
// to store mesh data after it has been read from a file.
// Corresponds to the structure of a Vertex.
//--------------------------------------------------------------------------------------
struct MeshType
{
	MeshType() : m_positionX( 0.0f ),
				 m_positionY( 0.0f ),
				 m_positionZ( 0.0f ),
				 m_normalX( 0.0f ),
				 m_normalY( 0.0f ),
				 m_normalZ( 0.0f ),
				 m_avgNormalX( 0.0f ),
				 m_avgNormalY( 0.0f ),
				 m_avgNormalZ( 0.0f ),
				 m_texCoordU( 0.0f ),
				 m_texCoordV( 0.0f )
				
	{}

	// the position of the vertex
	float m_positionX;
	float m_positionY;
	float m_positionZ;

	// the normal vector of the vertex
	float m_normalX;
	float m_normalY;
	float m_normalZ;

	// the normal vector this vertex shares with other vertices at this position
	float m_avgNormalX;
	float m_avgNormalY;
	float m_avgNormalZ;

	// the texture coordinates of the vertex
	float m_texCoordU;
	float m_texCoordV;

	
};



#endif