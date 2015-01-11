/* 
*  Kevin Meergans, Improved Lego Editor, 2014
*  ToonColourVertexShader05.h
*  Wrapper for the "VS_ToonColour05.fx" vertex shader.
*  Performs standard transformation of the vertex position and normal
*  and passes them together with the vertex colour to the next stage.
*/

#ifndef TOON_COLOUR_VERTEX_SHADER_05_H
#define TOON_COLOUR_VERTEX_SHADER_05_H

#include <Windows.h>
#include <xnamath.h>
#include "CompiledToonColourVertexShader05.h"
#include "VertexShader.h"
#include "ShaderDataStructures.h"

class ToonColourVertexShader05 : public VertexShader
{
public:
	ToonColourVertexShader05( void );
	virtual HRESULT Initialise( ID3D11Device* pDevice );
	virtual HRESULT Cleanup( void );
	virtual HRESULT UpdatePerSceneData( ID3D11DeviceContext* pContext, const PerSceneData& perSceneData);
	virtual HRESULT UpdatePerFrameData( ID3D11DeviceContext* pContext, const PerFrameData& perFrameData);
	virtual HRESULT UpdatePerObjectData( ID3D11DeviceContext* pContext, const PerObjectData& perObjectData);
	virtual HRESULT UpdateTextureResource( int index, ID3D11DeviceContext* pContext, ID3D11ShaderResourceView* pTexture, ID3D11SamplerState* pSamplerState );
private:

	const static D3D11_INPUT_ELEMENT_DESC m_sInputLayoutDescription[9];

	struct ConstBufferPerFrame
	{
		XMFLOAT4X4 m_viewProjection;	// The combined view and projection matrix
	};

	ConstBufferPerFrame  m_cbPerFrame;
	ID3D11Buffer*		 m_pCbPerFrameBuffer;

};


#endif