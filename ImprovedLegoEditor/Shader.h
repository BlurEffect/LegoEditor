/* 
*  Kevin Meergans, Improved Lego Editor, 2014
*  Shader.h
*  This is an abstract base class for concrete shader classes that will
*  inherit from this class. Used as public interface.
*/

#include <Windows.h>
#include <D3D11.h>

#ifndef SHADER_H
#define SHADER_H

// forward declaration
struct PerSceneData;
struct PerFrameData;
struct PerObjectData;

class Shader
{
public:

	// Virtual destructor to enable proper destruction through the base class interface
	virtual ~Shader( void ){}

	virtual HRESULT Initialise( ID3D11Device* pDevice ) = 0;
	virtual HRESULT Cleanup( void ) = 0;
	virtual HRESULT UpdatePerSceneData( ID3D11DeviceContext* pContext, const PerSceneData& perSceneData)  = 0;
	virtual HRESULT UpdatePerFrameData( ID3D11DeviceContext* pContext, const PerFrameData& perFrameData)  = 0;
	virtual HRESULT UpdatePerObjectData( ID3D11DeviceContext* pContext, const PerObjectData& perObjectData) = 0;
	virtual HRESULT UpdateTextureResource( int index, ID3D11DeviceContext* pContext, ID3D11ShaderResourceView* pTexture, ID3D11SamplerState* pSamplerState ) = 0;
	virtual HRESULT Activate( ID3D11DeviceContext* pContext ) = 0;
};

#endif
