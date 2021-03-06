/* 
*  Kevin Meergans, Improved Lego Editor, 2014
*  SimpleVertexShader.h
*  Wrapper for the "VS_Simple.fx" vertex shader.
*  Performs standard transformation to the vertex position and forwards
*  the result together with the vertex colour to the next stage.
*/

#ifndef SIMPLE_VERTEX_SHADER_H
#define SIMPLE_VERTEX_SHADER_H

#include <Windows.h>
#include <xnamath.h>
#include "CompiledSimpleVertexShader.h"
#include "VertexShader.h"
#include "ShaderDataStructures.h"

class SimpleVertexShader : public VertexShader
{
public:
	SimpleVertexShader( void );
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
		XMFLOAT4X4 m_viewProjection;   // The combined view and projection matrices
	};

	ConstBufferPerFrame  m_cbPerFrame;
	ID3D11Buffer*		 m_pCbPerFrameBuffer;

};


#endif