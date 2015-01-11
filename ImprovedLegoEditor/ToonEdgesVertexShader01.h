/* 
*  Kevin Meergans, Improved Lego Editor, 2014
*  ToonEdgesVertexShader01.h
*  Wrapper for the "VS_ToonEdges01.fx" vertex shader.
*  Moves vertices along their normals in order to create an outline around
*  objects. Afterwards, the new position is transformed as usual
*  and forwarded to the pixel shader.
*/

#ifndef TOON_EDGES_VERTEX_SHADER_01_H
#define TOON_EDGES_VERTEX_SHADER_01_H

#include <Windows.h>
#include <xnamath.h>
#include "CompiledToonEdgesVertexShader01.h"
#include "VertexShader.h"
#include "ShaderDataStructures.h"

class ToonEdgesVertexShader01 : public VertexShader
{
public:
	ToonEdgesVertexShader01( void );
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
		float    m_vertexOffset;	// Determines how far the vertices are moved along their normal
		XMFLOAT3 m_padding;
	};

	struct ConstBufferPerFrame
	{
		XMFLOAT4X4 m_viewProjection;	// The combined view and projection matrices
	};

	ConstBufferPerScene  m_cbPerScene;
	ID3D11Buffer*		 m_pCbPerSceneBuffer;

	ConstBufferPerFrame  m_cbPerFrame;
	ID3D11Buffer*		 m_pCbPerFrameBuffer;
};


#endif