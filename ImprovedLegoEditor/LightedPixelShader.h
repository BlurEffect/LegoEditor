/* 
*  Kevin Meergans, Improved Lego Editor, 2014
*  LightedPixelShader.h
*  Wrapper for the "PS_Lighted.fx" pixel shader.
*  Provides simple diffuse lighting for a given directional light source.
*/

#ifndef LIGHTED_PIXEL_SHADER_H
#define LIGHTED_PIXEL_SHADER_H

#include <Windows.h>
#include <xnamath.h>
#include "CompiledLightedPixelShader.h"
#include "PixelShader.h"
#include "ShaderDataStructures.h"

class LightedPixelShader : public PixelShader
{
public:
	LightedPixelShader( void );
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