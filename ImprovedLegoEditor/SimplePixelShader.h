/* 
*  Kevin Meergans, Improved Lego Editor, 2014
*  SimplePixelShader.h
*  Wrapper for the "PS_Simple.fx" pixel shader.
*  Simply returns the input colour as the final colour for the pixel.
*/

#ifndef SIMPLE_PIXEL_SHADER_H
#define SIMPLE_PIXEL_SHADER_H

#include <Windows.h>
#include <xnamath.h>
#include "CompiledSimplePixelShader.h"
#include "PixelShader.h"
#include "ShaderDataStructures.h"

class SimplePixelShader : public PixelShader
{
public:
	SimplePixelShader( void );
	virtual HRESULT Initialise( ID3D11Device* pDevice );
	virtual HRESULT Cleanup( void );
	virtual HRESULT UpdatePerSceneData( ID3D11DeviceContext* pContext, const PerSceneData& perSceneData);
	virtual HRESULT UpdatePerFrameData( ID3D11DeviceContext* pContext, const PerFrameData& perFrameData);
	virtual HRESULT UpdatePerObjectData( ID3D11DeviceContext* pContext, const PerObjectData& perObjectData);
	virtual HRESULT UpdateTextureResource( int index, ID3D11DeviceContext* pContext, ID3D11ShaderResourceView* pTexture, ID3D11SamplerState* pSamplerState );
private:
	// no constant buffers required by this one
};


#endif