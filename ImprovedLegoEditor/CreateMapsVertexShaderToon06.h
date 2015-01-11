/* 
*  Kevin Meergans, Improved Lego Editor, 2014
*  CreateMapsVertexShaderToon06.h
*  Wrapper for the "VS_CreateMapsToon06.fx" vertex shader.
*  Performs the standard transformations on vertex positions and normals
*  and forwards the rest of the vertex input to the pixel shader. Additionally
*  to that, the shader passes normals and position data in view space to the next 
*  stage.
*/

#ifndef CREATE_MAPS_VERTEX_SHADER_TOON_06_H
#define CREATE_MAPS_VERTEX_SHADER_TOON_06_H

#include <Windows.h>
#include <xnamath.h>
#include "CompiledCreateMapsVertexShader06.h"
#include "VertexShader.h"
#include "ShaderDataStructures.h"

class CreateMapsVertexShaderToon06 : public VertexShader
{
public:
	CreateMapsVertexShaderToon06( void );
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
		XMFLOAT4X4 m_viewProjection;	// The combined view and projection matrices
		XMFLOAT4X4 m_viewMatrix;		// The current view matrix
	};

	ConstBufferPerFrame  m_cbPerFrame;
	ID3D11Buffer*		 m_pCbPerFrameBuffer;

};


#endif