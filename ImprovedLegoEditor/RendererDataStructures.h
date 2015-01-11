/* 
*  Kevin Meergans, Improved Lego Editor, 2014
*  RendererDataStructures.h
*  Contains data structures used by the renderer of the application.
*/

#ifndef RENDERER_DATA_STRUCTURES_H
#define RENDERER_DATA_STRUCTURES_H

#include <windows.h>
#include <xnamath.h>

/*
//--------------------------------------------------------------------------------------
// Constant buffer structure for effects (for grid, cursor)
//--------------------------------------------------------------------------------------
struct ConstBufferPerSimpleObject
{
	XMFLOAT4X4  m_WVP;
	XMFLOAT4	m_colour;
};

//--------------------------------------------------------------------------------------
// Constant buffer structure for effects (for bricks, scene objects)
//--------------------------------------------------------------------------------------
struct ConstBufferPerLightedObject
{
	XMFLOAT4X4  m_WVP;
	XMFLOAT4X4	m_world;
	XMFLOAT4	m_colour;
};


//--------------------------------------------------------------------------------------
// Updated once every frame
//--------------------------------------------------------------------------------------
struct ConstBufferPerFrame
{
	XMFLOAT4X4 m_viewProjection;
	XMFLOAT3   m_viewPosition;
	float	   m_padding;
};



//--------------------------------------------------------------------------------------
// Updated once per scene
//--------------------------------------------------------------------------------------
struct ConstBufferPerSceneColour
{
	XMFLOAT4   m_diffuseLightColor;
	//XMFLOAT4   m_edgeColour;
	XMFLOAT3   m_lightDirection;
	float	   m_padding;
	//float	   m_colourEdgeThreshold;		
	//float	   m_numberOfShades;
	//float      m_excludedShades;
	//XMFLOAT2   m_padding;
};

struct ConstBufferPerSceneEdges
{
	XMFLOAT4   m_edgeColour;

};


*/


//--------------------------------------------------------------------------------------
// Description of the vertex layout to be used when setting up shaders for meshes
//--------------------------------------------------------------------------------------
/*
const static D3D11_INPUT_ELEMENT_DESC VertexLayout[] =
{
	{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,  0, D3D11_INPUT_PER_VERTEX_DATA, 0 },  
	{ "NORMAL"  , 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT   , 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	
};
*/
/*
const static D3D11_INPUT_ELEMENT_DESC VertexLayout[] =
{
	// Vertex data
	{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,    0,  0, D3D11_INPUT_PER_VERTEX_DATA,   0 },  
	{ "NORMAL"  , 0, DXGI_FORMAT_R32G32B32_FLOAT,    0, 12, D3D11_INPUT_PER_VERTEX_DATA,   0 },
	{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT   ,    0, 24, D3D11_INPUT_PER_VERTEX_DATA,   0 },  
	
	// Instance data
	{ "WORLD",	  0, DXGI_FORMAT_R32G32B32A32_FLOAT, 1,  0, D3D11_INPUT_PER_INSTANCE_DATA, 1 },
	{ "WORLD",    1, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 16, D3D11_INPUT_PER_INSTANCE_DATA, 1 },
	{ "WORLD",    2, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 32, D3D11_INPUT_PER_INSTANCE_DATA, 1 },
	{ "WORLD",    3, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 48, D3D11_INPUT_PER_INSTANCE_DATA, 1 },
	{ "COLOUR",   0, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 64, D3D11_INPUT_PER_INSTANCE_DATA, 1 }
};
*//*
//--------------------------------------------------------------------------------------
// Description of the vertex layout to be used when setting up shaders for the grid
//--------------------------------------------------------------------------------------
const static D3D11_INPUT_ELEMENT_DESC SimpleVertexLayout[] =
{
	{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT   , 0,  0, D3D11_INPUT_PER_VERTEX_DATA, 0 } 
};

*/

#endif