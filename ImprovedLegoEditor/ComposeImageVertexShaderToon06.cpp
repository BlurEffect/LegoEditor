/* 
*  Kevin Meergans, Improved Lego Editor, 2014
*  ComposeImageVertexShaderToon06.cpp
*  Contains the function definitions for the ComposeImageVertexShaderToon06 class.
*/

#include "ComposeImageVertexShaderToon06.h"

// The vertex input layout expected by this vertex shader
const D3D11_INPUT_ELEMENT_DESC ComposeImageVertexShaderToon06::m_sInputLayoutDescription[] = 
{
	// Vertex data
	{ "POSITION" , 0, DXGI_FORMAT_R32G32B32_FLOAT,    0,  0, D3D11_INPUT_PER_VERTEX_DATA,   0 },  
	{ "TEXCOORD" , 0, DXGI_FORMAT_R32G32_FLOAT   ,    0, 12, D3D11_INPUT_PER_VERTEX_DATA,   0 },  
};

ComposeImageVertexShaderToon06::ComposeImageVertexShaderToon06( void ) : VertexShader()
{

}

//--------------------------------------------------------------------------------------
// Initialise the shader's member variables.
//--------------------------------------------------------------------------------------
HRESULT ComposeImageVertexShaderToon06::Initialise( ID3D11Device* pDevice )
{
	HRESULT hr;

	// Create the shader

	hr = pDevice -> CreateVertexShader( g_composeImageVertexShader06, sizeof( g_composeImageVertexShader06 ), nullptr, &m_pVertexShader );
	if( FAILED ( hr ) )
	{
		return hr;
	}

	// Create the vertex input layout

	UINT numElements = ARRAYSIZE( m_sInputLayoutDescription );
	hr = pDevice -> CreateInputLayout( m_sInputLayoutDescription, numElements, g_composeImageVertexShader06, sizeof( g_composeImageVertexShader06 ), &m_pInputLayout );
	if( FAILED ( hr ) )
	{
		return hr;
	}


	return S_OK;
}

//--------------------------------------------------------------------------------------
// Free all allocated resources.
//--------------------------------------------------------------------------------------
HRESULT ComposeImageVertexShaderToon06::Cleanup( void )
{

	return VertexShader::Cleanup();
}

//--------------------------------------------------------------------------------------
// Update the per-scene constant buffer of the shader.
//--------------------------------------------------------------------------------------
HRESULT ComposeImageVertexShaderToon06::UpdatePerSceneData( ID3D11DeviceContext* pContext, const PerSceneData& perSceneData)
{
	// Buffer not used in this shader
	return E_FAIL;
}

//--------------------------------------------------------------------------------------
// Update the per-frame constant buffer of the shader.
//--------------------------------------------------------------------------------------
HRESULT ComposeImageVertexShaderToon06::UpdatePerFrameData( ID3D11DeviceContext* pContext, const PerFrameData& perFrameData)
{
	// Not used in this shader
	return E_FAIL;
}

//--------------------------------------------------------------------------------------
// Update the per-object constant buffer of the shader.
//--------------------------------------------------------------------------------------
HRESULT ComposeImageVertexShaderToon06::UpdatePerObjectData( ID3D11DeviceContext* pContext, const PerObjectData& perObjectData)
{
	// Not used in this shader
	return E_FAIL;
}

//--------------------------------------------------------------------------------------
// Update the texture and corresponding sample state being used by the shader.
//--------------------------------------------------------------------------------------
HRESULT ComposeImageVertexShaderToon06::UpdateTextureResource( int index, ID3D11DeviceContext* pContext, ID3D11ShaderResourceView* pTexture, ID3D11SamplerState* pSamplerState )
{
	// Not used in this shader
	return E_FAIL;
}
