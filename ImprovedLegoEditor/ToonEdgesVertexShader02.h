/* 
*  Kevin Meergans, Improved Lego Editor, 2014
*  ToonEdgesVertexShader02.h
*  Wrapper for the "VS_ToonEdges02.fx" vertex shader.
*  Moves each vertex along the normal vector it shares with other vertices
*  in the same position in order to create an outline around objects without gaps
*  between the extruded faces. The new position is transformed as usual
*  and forwarded to the pixel shader.
*/

#ifndef TOON_EDGES_VERTEX_SHADER_02_H
#define TOON_EDGES_VERTEX_SHADER_02_H

#include <Windows.h>
#include <xnamath.h>
#include "CompiledToonEdgesVertexShader02.h"
#include "VertexShader.h"
#include "ShaderDataStructures.h"

class ToonEdgesVertexShader02 : public VertexShader
{
public:
	ToonEdgesVertexShader02( void );
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
		XMFLOAT4   m_viewPosition;
	};

	ConstBufferPerScene  m_cbPerScene;
	ID3D11Buffer*		 m_pCbPerSceneBuffer;

	ConstBufferPerFrame  m_cbPerFrame;
	ID3D11Buffer*		 m_pCbPerFrameBuffer;
};


#endif