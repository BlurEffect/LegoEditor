/* 
*  Kevin Meergans, Improved Lego Editor, 2014
*  ComposeImageVertexShaderToon06.h
*  Wrapper for the "VS_ComposeImageToon06.fx" vertex shader.
*  Simply forwards the passed in position and texture data to the pixel shader.
*  Does not apply any transformations.
*/

#ifndef COMPOSE_IMAGE_VERTEX_SHADER_TOON_06_H
#define COMPOSE_IMAGE_VERTEX_SHADER_TOON_06_H

#include <Windows.h>
#include <xnamath.h>
#include "CompiledComposeImageVertexShader06.h"
#include "VertexShader.h"
#include "ShaderDataStructures.h"

class ComposeImageVertexShaderToon06 : public VertexShader
{
public:
	ComposeImageVertexShaderToon06( void );
	virtual HRESULT Initialise( ID3D11Device* pDevice );
	virtual HRESULT Cleanup( void );
	virtual HRESULT UpdatePerSceneData( ID3D11DeviceContext* pContext, const PerSceneData& perSceneData);
	virtual HRESULT UpdatePerFrameData( ID3D11DeviceContext* pContext, const PerFrameData& perFrameData);
	virtual HRESULT UpdatePerObjectData( ID3D11DeviceContext* pContext, const PerObjectData& perObjectData);
	virtual HRESULT UpdateTextureResource( int index, ID3D11DeviceContext* pContext, ID3D11ShaderResourceView* pTexture, ID3D11SamplerState* pSamplerState );
private:
	const static D3D11_INPUT_ELEMENT_DESC m_sInputLayoutDescription[2];
};


#endif