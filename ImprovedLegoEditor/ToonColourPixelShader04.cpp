/* 
*  Kevin Meergans, Improved Lego Editor, 2014
*  ToonColourPixelShader04.cpp
*  Contains the function definitions for the ToonColourPixelShader04 class.
*/

#include "ToonColourPixelShader04.h"


ToonColourPixelShader04::ToonColourPixelShader04( void ) : PixelShader(), 
														   m_pCbPerSceneBuffer( nullptr )
{
	m_cbPerScene.m_diffuseLightColor = XMFLOAT4( 1.0f, 1.0f, 1.0f, 1.0f );
	m_cbPerScene.m_lightDirection    = XMFLOAT3( 0.0f, 0.0f, 1.0f );
	m_cbPerScene.m_padding			 = 0.0f;

	m_pTextures[0] = nullptr;
	m_pSamplerStates[0] = nullptr;
}

//--------------------------------------------------------------------------------------
// Initialise the shader's member variables.
//--------------------------------------------------------------------------------------
HRESULT ToonColourPixelShader04::Initialise( ID3D11Device* pDevice )
{
	HRESULT hr;

	// Create the shader

	hr = pDevice -> CreatePixelShader( g_toonColourPixelShader04, sizeof( g_toonColourPixelShader04 ), nullptr, &m_pPixelShader );
	if( FAILED ( hr ) )
	{
		return hr;
	}

	// Create constant buffers

	D3D11_BUFFER_DESC cbPerSceneDesc;	
	ZeroMemory( &cbPerSceneDesc, sizeof( D3D11_BUFFER_DESC ) );

	cbPerSceneDesc.Usage = D3D11_USAGE_DYNAMIC;
	cbPerSceneDesc.ByteWidth = sizeof( m_cbPerScene );
	cbPerSceneDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbPerSceneDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cbPerSceneDesc.MiscFlags = 0;

	hr = pDevice -> CreateBuffer( &cbPerSceneDesc, NULL, &m_pCbPerSceneBuffer );
	if( FAILED ( hr ) )
	{
		return hr;
	}

	return S_OK;
}

//--------------------------------------------------------------------------------------
// Free all allocated resources.
//--------------------------------------------------------------------------------------
HRESULT ToonColourPixelShader04::Cleanup( void )
{
	if( m_pCbPerSceneBuffer )
	{
		m_pCbPerSceneBuffer -> Release();
		m_pCbPerSceneBuffer = nullptr;
	}

	return PixelShader::Cleanup();

	// Texture and SampleState are created elsewhere and only passed to the shader, they
	// will be destroyed elsewhere. Destroying them here might lead to problems for other
	// objects still using the texture.
}

//--------------------------------------------------------------------------------------
// Update the per-scene constant buffer of the shader.
//--------------------------------------------------------------------------------------
HRESULT ToonColourPixelShader04::UpdatePerSceneData( ID3D11DeviceContext* pContext, const PerSceneData& perSceneData)
{

	HRESULT hr;

	m_cbPerScene.m_diffuseLightColor = perSceneData.m_diffuseLightColor;
	m_cbPerScene.m_lightDirection    = perSceneData.m_lightDirection;

	D3D11_MAPPED_SUBRESOURCE mappedResource;
	hr = pContext -> Map( m_pCbPerSceneBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource );
	if( FAILED( hr ) )
	{
		return hr;
	}

	memcpy( mappedResource.pData, &m_cbPerScene, sizeof( ConstBufferPerScene ) );
	pContext -> Unmap( m_pCbPerSceneBuffer, 0 );

	pContext -> PSSetConstantBuffers( 0, 1, &m_pCbPerSceneBuffer );

	return S_OK;
}

//--------------------------------------------------------------------------------------
// Update the per-frame constant buffer of the shader.
//--------------------------------------------------------------------------------------
HRESULT ToonColourPixelShader04::UpdatePerFrameData( ID3D11DeviceContext* pContext, const PerFrameData& perFrameData)
{
	// Buffer not used in this shader
	return E_FAIL;
}

//--------------------------------------------------------------------------------------
// Update the per-object constant buffer of the shader.
//--------------------------------------------------------------------------------------
HRESULT ToonColourPixelShader04::UpdatePerObjectData( ID3D11DeviceContext* pContext, const PerObjectData& perObjectData)
{
	// not used in this shader
	return E_FAIL;
}

//--------------------------------------------------------------------------------------
// Update the texture and corresponding sample state being used by the shader.
//--------------------------------------------------------------------------------------
HRESULT ToonColourPixelShader04::UpdateTextureResource( int index, ID3D11DeviceContext* pContext, ID3D11ShaderResourceView* pTexture, ID3D11SamplerState* pSamplerState )
{
	if( index != 0 )
	{
		return E_FAIL;
	}

	m_pTextures[index]	    = pTexture;
	m_pSamplerStates[index] = pSamplerState;

	// Set the texture and sampler state
	pContext -> PSSetShaderResources(0, 1, &m_pTextures[index]);
	pContext -> PSSetSamplers(0, 1, &m_pSamplerStates[index]);

	return S_OK;
}




	