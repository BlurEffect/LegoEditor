/* 
*  Kevin Meergans, Improved Lego Editor, 2014
*  ToonEdgesVertexShader04.h
*  Wrapper for the "VS_ToonEdges04.fx" vertex shader.
*  Moves vertices along the screen-z axis by a certain bias in order to create an
*  outline around an object as these backfaces now appear slightly in front of the
*  neighbouring front faces. The transformed position is then forwarded to the 
*  pixel shader.
*/

#ifndef TOON_EDGES_VERTEX_SHADER_04_H
#define TOON_EDGES_VERTEX_SHADER_04_H

#include <Windows.h>
#include <xnamath.h>
#include "CompiledToonEdgesVertexShader04.h"
#include "VertexShader.h"
#include "ShaderDataStructures.h"

class ToonEdgesVertexShader04 : public VertexShader
{
public:
	ToonEdgesVertexShader04( void );
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
		float    m_moveBias;	// The vertices are moved by this distance in screen-z
		XMFLOAT3 m_padding;
	};

	struct ConstBufferPerFrame
	{
		XMFLOAT4X4 m_viewProjection;	// The combined view and projection matrix
		XMFLOAT3   m_eyePosition;		// The position of the camera in view space
		float	   m_padding;
	};

	ConstBufferPerScene  m_cbPerScene;
	ID3D11Buffer*		 m_pCbPerSceneBuffer;

	ConstBufferPerFrame  m_cbPerFrame;
	ID3D11Buffer*		 m_pCbPerFrameBuffer;

};


#endif