/* 
*  Kevin Meergans, Improved Lego Editor, 2014
*  PixelShader.h
*  This is an abstract base class for concrete pixel shader classes that will
*  inherit from this class.
*/

#ifndef PIXEL_SHADER
#define PIXEL_SHADER

#include <Windows.h>
#include <D3D11.h>
#include "Shader.h"

class PixelShader : public Shader
{
public:
	PixelShader( void );
	virtual ~PixelShader( void );
	virtual HRESULT Cleanup( void );
	HRESULT Activate( ID3D11DeviceContext* pContext );

// allow access by derived classes; todo: better to provide protected interface with getters/setters?
protected:
	ID3D11PixelShader*			m_pPixelShader;
};


#endif