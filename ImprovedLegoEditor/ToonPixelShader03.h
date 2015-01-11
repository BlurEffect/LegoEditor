/* 
*  Kevin Meergans, Improved Lego Editor, 2014
*  ToonPixelShader03.h
*  Wrapper for the "PS_Toon03.fx" pixel shader.
*  Examines the edge proximity value passed on by the vertex shader and compares it
*  against a given threshold. According to the result of that comparison the pixel is
*  either coloured in the outline colour or lighted/coloured as usual using a texture
*  of shades.
*/

#ifndef TOON_PIXEL_SHADER_03_H
#define TOON_PIXEL_SHADER_03_H

#include <Windows.h>
#include <xnamath.h>
#include "CompiledToonPixelShader03.h"
#include "PixelShader.h"
#include "ShaderDataStructures.h"

class ToonPixelShader03 : public PixelShader
{
public:
	ToonPixelShader03( void );
	virtual HRESULT Initialise( ID3D11Device* pDevice );
	virtual HRESULT Cleanup( void );
	virtual HRESULT UpdatePerSceneData( ID3D11DeviceContext* pContext, const PerSceneData& perSceneData);
	virtual HRESULT UpdatePerFrameData( ID3D11DeviceContext* pContext, const PerFrameData& perFrameData);
	virtual HRESULT UpdatePerObjectData( ID3D11DeviceContext* pContext, const PerObjectData& perObjectData);
	virtual HRESULT UpdateTextureResource( int index, ID3D11DeviceContext* pContext, ID3D11ShaderResourceView* pTexture, ID3D11SamplerState* pSamplerState );
private:
	struct ConstBufferPerScene
	{
		XMFLOAT4 m_diffuseLightColour;  // The colour of the directional light in the scene
		XMFLOAT4 m_edgeColour;			// Colour the edge in this colour
		XMFLOAT3 m_lightDirection;      // The direction of the directional light in the scene
		float    m_edgeThreshold;	    // Colour pixel as edge when the edge proximity value is below this value
	};

	ConstBufferPerScene  m_cbPerScene;
	ID3D11Buffer*		 m_pCbPerSceneBuffer;

	ID3D11ShaderResourceView*	m_pTextures[1];			
	ID3D11SamplerState*		    m_pSamplerStates[1];	
};


#endif