/* 
*  Kevin Meergans, Improved Lego Editor, 2014
*  CreateMapsPixelShaderToon06.h
*  Wrapper for the "PS_CreateMapsToon06.fx" pixel shader.
*  Determines the colour value for the pixel using a texture holding different
*  shades and writes the resulting colour value to a colour map. Writes normal
*  and depth information for the pixel to another render target texture.
*/

#ifndef CREATE_MAPS_PIXEL_SHADER_TOON_06_H
#define CREATE_MAPS_PIXEL_SHADER_TOON_06_H

#include <Windows.h>
#include <xnamath.h>
#include "CompiledCreateMapsPixelShader06.h"
#include "PixelShader.h"
#include "ShaderDataStructures.h"

class CreateMapsPixelShaderToon06 : public PixelShader
{
public:
	CreateMapsPixelShaderToon06( void );
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

	ID3D11ShaderResourceView*	m_pTextures[1];			// The texture holding the different shades/colour tones
	ID3D11SamplerState*		    m_pSamplerStates[1];		
};


#endif