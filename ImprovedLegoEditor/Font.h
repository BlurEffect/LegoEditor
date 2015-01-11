/* 
*  Kevin Meergans, Improved Lego Editor, 2014
*  Font.h
*  Encapsulates a font created by loading in a texture and an accompanying data file containing 
*  information on the characters in the texture, such as the width. Creates vertex and index
*  buffers for a given text. 
*  Tailored to read in data created with "Codehead's Bitmap Font Generator", available from here: http://www.codehead.co.uk/cbfg/ 
*/

#ifndef FONT_H
#define FONT_H

#include <windows.h>
#include <memory>
#include <d3d11.h>
#include <string>

// forward declaration
class FontImplementation;

class Font
{
public:
	Font();
	HRESULT Initialise( ID3D11Device* pDevice, const std::string& dataFileName, LPCWSTR textureFilename );
	HRESULT Cleanup( void );
	void    BuildVertexArray( void* outVertices, const char* text, float screenX, float screenY);
	ID3D11ShaderResourceView* GetTexture();
private:
	
	std::tr1::shared_ptr<FontImplementation> m_pImplementation;
};

#endif