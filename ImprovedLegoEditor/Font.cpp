/* 
*  Kevin Meergans, Improved Lego Editor, 2014
*  Font.cpp
*  Contains the function definitions for the Font class. Calls to these
*  functions will be forwarded to the implementation part of the Font class
*  "FontImplementation".
*/

#include "Font.h"
#include "FontImplementation.h"

Font::Font() : m_pImplementation( new FontImplementation() )
{
}

HRESULT Font::Initialise( ID3D11Device* pDevice, const std::string& dataFileName, LPCWSTR textureFilename )
{
	return m_pImplementation -> Initialise( pDevice, dataFileName, textureFilename );
}

HRESULT Font::Cleanup( void )
{
	return m_pImplementation -> Cleanup();
}

void Font::BuildVertexArray( void* outVertices, const char* text, float screenX, float screenY)
{
	m_pImplementation -> BuildVertexArray( outVertices, text, screenX, screenY);
}

ID3D11ShaderResourceView* Font::GetTexture()
{
	return m_pImplementation -> GetTexture();
}