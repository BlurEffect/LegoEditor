/* 
*  Kevin Meergans, Improved Lego Editor, 2014
*  PixelShader.cpp
*  Contains the function definitions for the abstract VertexShader class.
*/

#include "PixelShader.h"


PixelShader::PixelShader( void ) : m_pPixelShader( nullptr )
{
}

PixelShader::~PixelShader( void )
{
}

//--------------------------------------------------------------------------------------
// Free resources
//--------------------------------------------------------------------------------------
HRESULT PixelShader::Cleanup( void )
{
	if( m_pPixelShader )
	{
		m_pPixelShader -> Release();
		m_pPixelShader = nullptr;
	}

	return S_OK;
}

//--------------------------------------------------------------------------------------
// Set this shader as the active one
//--------------------------------------------------------------------------------------
HRESULT PixelShader::Activate( ID3D11DeviceContext* pContext )
{
	// Set the vertex shader
	pContext -> PSSetShader( m_pPixelShader, 0, 0 );

	return S_OK;
}