/* 
*  Kevin Meergans, Improved Lego Editor, 2014
*  VertexShader.cpp
*  Contains the function definitions for the abstract VertexShader class.
*/

#include "VertexShader.h"


VertexShader::VertexShader( void ) : m_pInputLayout( nullptr ), 
									 m_pVertexShader( nullptr )
{
}

VertexShader::~VertexShader( void )
{
}

//--------------------------------------------------------------------------------------
// Free resources
//--------------------------------------------------------------------------------------
HRESULT VertexShader::Cleanup( void )
{
	if( m_pInputLayout )
	{
		m_pInputLayout -> Release();
		m_pInputLayout = nullptr;
	}

	if( m_pVertexShader )
	{
		m_pVertexShader -> Release();
		m_pVertexShader = nullptr;
	}

	return S_OK;
}

//--------------------------------------------------------------------------------------
// Set this shader as the active one
//--------------------------------------------------------------------------------------
HRESULT VertexShader::Activate( ID3D11DeviceContext* pContext )
{
	// Set the vertex shader
	pContext -> VSSetShader( m_pVertexShader, 0, 0 );

	// Set the input layout
	pContext -> IASetInputLayout( m_pInputLayout );

	return S_OK;
}