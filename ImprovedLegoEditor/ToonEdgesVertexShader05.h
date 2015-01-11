/* 
*  Kevin Meergans, Improved Lego Editor, 2014
*  ToonEdgesVertexShader05.h
*  Wrapper for the "VS_ToonEdges05.fx"
*  Moves vertices along the screen-x and -y axis by an offset determined
*  by the vertex normals and the depth. This matches the toon shader used
*  by the game engine Unity.
*/

#ifndef TOON_EDGES_VERTEX_SHADER_05_H
#define TOON_EDGES_VERTEX_SHADER_05_H

#include <Windows.h>
#include <xnamath.h>
#include "CompiledToonEdgesVertexShader05.h"
#include "VertexShader.h"
#include "ShaderDataStructures.h"

class ToonEdgesVertexShader05 : public VertexShader
{
public:
	ToonEdgesVertexShader05( void );
	virtual HRESULT Initialise( ID3D11Device* pDevice );
	virtual HRESULT Cleanup( void );
	virtual HRESULT UpdatePerSceneData( ID3D11DeviceContext* pContext, const PerSceneData& perSceneData);
	virtual HRESULT UpdatePerFrameData( ID3D11DeviceContext* pContext, const PerFrameData& perFrameData);
	virtual HRESULT UpdatePerObjectData( ID3D11DeviceContext* pContext, const PerObjectData& perObjectData);
	virtual HRESULT UpdateTextureResource( int index, ID3D11DeviceContext* pContext, ID3D11ShaderResourceView* pTexture, ID3D11SamplerState* pSamplerState );
private:

	const static D3D11_INPUT_ELEMENT_DESC m_sInputLayoutDescription[9];

	struct ConstBufferPerScene
	{
		float    m_outlineWidth;  // Determines how thick the outline will be
		XMFLOAT3 m_padding;
	};

	struct ConstBufferPerFrame
	{
		XMFLOAT4X4 m_viewProjection;	// The combined view and projection matrix
	};

	ConstBufferPerScene  m_cbPerScene;
	ID3D11Buffer*		 m_pCbPerSceneBuffer;

	ConstBufferPerFrame  m_cbPerFrame;
	ID3D11Buffer*		 m_pCbPerFrameBuffer;
};


#endif