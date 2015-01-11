/* 
*  Kevin Meergans, Improved Lego Editor, 2014
*  ToonColourPixelShader04.h
*  Wrapper for the "PS_ToonColour04.fx" pixel shader.
*  Determines the colour shade for pixels by calculating the amount of
*  light for each pixel and using that value as a texture coordinate into
*  a texture containing different shades.
*/

#ifndef TOON_COLOUR_PIXEL_SHADER_04_H
#define TOON_COLOUR_PIXEL_SHADER_04_H

#include <Windows.h>
#include <xnamath.h>
#include "CompiledToonColourPixelShader04.h"
#include "PixelShader.h"
#include "ShaderDataStructures.h"

class ToonColourPixelShader04 : public PixelShader
{
public:
	ToonColourPixelShader04( void );
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

	ID3D11ShaderResourceView*	m_pTextures[1];			// The texture holding the different shades (greyscales)
	ID3D11SamplerState*		    m_pSamplerStates[1];	
};


#endif