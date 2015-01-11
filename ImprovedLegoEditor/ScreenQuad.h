/* 
*  Kevin Meergans, Improved Lego Editor, 2014
*  ScreenQuad.h
*  Encapsulates vertex and index buffers for a screen filling quad in terms
*  of screen space
*/

#ifndef SCREEN_QUAD_H
#define SCREEN_QUAD_H

#include <windows.h>
#include <memory>
#include <d3d11.h>
#include <d3dx11.h>
#include <xnamath.h>

class ScreenQuad
{
public:
	ScreenQuad();

	HRESULT Initialise( ID3D11Device* pDevice );
	HRESULT Cleanup();
	void	Render( ID3D11DeviceContext* );

private:
	ID3D11Buffer*	m_pVertexBuffer;	
	ID3D11Buffer*	m_pIndexBuffer;		
	int				m_vertexCount;
	int				m_indexCount;

	struct QuadVertex
	{
		QuadVertex() : m_position( 0, 0, 0 ), m_texCoord( 0.0f, 0.0f ) {}
		QuadVertex( float posX, float posY, float posZ, float u, float v ) : m_position( posX, posY, posZ ), m_texCoord( u, v ) {}

		XMFLOAT3 m_position;		// position of the vertex
		XMFLOAT2 m_texCoord;		// texture coordinate of the vertex
	};

};

#endif