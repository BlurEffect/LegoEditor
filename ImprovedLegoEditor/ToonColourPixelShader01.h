/* 
*  Kevin Meergans, Improved Lego Editor, 2014
*  ToonColourPixelShader01.h
*  Wrapper for the "PS_ToonColour01.fx" pixel shader.
*  Calculates the amount of light on each pixel and uses that value to
*  determine the colour shade to be used, based on ranges set in the 
*  shader code
*/

#ifndef TOON_COLOUR_PIXEL_SHADER_01_H
#define TOON_COLOUR_PIXEL_SHADER_01_H

#include <Windows.h>
#include <xnamath.h>
#include "CompiledToonColourPixelShader01.h"
#include "PixelShader.h"
#include "ShaderDataStructures.h"

class ToonColourPixelShader01 : public PixelShader
{
public:
	ToonColourPixelShader01( void );
	virtual HRESULT Initialise( ID3D11Device* pDevice );
	virtual HRESULT Cleanup( void );
	virtual HRESULT UpdatePerSceneData( ID3D11DeviceContext* pContext, const PerSceneData& perSceneData);
	virtual HRESULT UpdatePerFrameData( ID3D11DeviceContext* pContext, const PerFrameData& perFrameData);
	virtual HRESULT UpdatePerObjectData( ID3D11DeviceContext* pContext, const PerObjectData& perObjectData);
	virtual HRESULT UpdateTextureResource( int index, ID3D11DeviceContext* pContext, ID3D11ShaderResourceView* pTexture, ID3D11SamplerState* pSamplerState );
private:
	struct ConstBufferPerScene
	{
		XMFLOAT4   m_diffuseLightColor;		// The colour of the directional light in the scene
		XMFLOAT3   m_lightDirection;		// The direction of the directional light in the scene
		float	   m_padding;
	};

	ConstBufferPerScene  m_cbPerScene;
	ID3D11Buffer*		 m_pCbPerSceneBuffer;	
};


#endif