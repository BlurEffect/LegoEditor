/* 
*  Kevin Meergans, Improved Lego Editor, 2014
*  VertexShader.h
*  This is an abstract base class for concrete vertex shader classes that will
*  inherit from this class.
*/

#ifndef VERTEX_SHADER
#define VERTEX_SHADER

#include <Windows.h>
#include <D3D11.h>
#include "Shader.h"

class VertexShader : public Shader
{
public:
	VertexShader( void );
	virtual ~VertexShader( void );
	virtual HRESULT Cleanup( void );
	HRESULT Activate( ID3D11DeviceContext* pContext );

// allow access by derived classes; todo: better to provide protected interface with getters/setters?
protected:
	ID3D11InputLayout*  m_pInputLayout;
	ID3D11VertexShader* m_pVertexShader;

};


#endif



