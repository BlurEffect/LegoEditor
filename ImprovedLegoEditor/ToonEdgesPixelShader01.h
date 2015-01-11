/* 
*  Kevin Meergans, Improved Lego Editor, 2014
*  ToonEdgesPixelShader01.h
*  Wrapper for the "PS_ToonEdges01.fx" pixel shader.
*  Simply returns a defined edge colour for every pixel.
*/

#ifndef TOON_EDGES_PIXEL_SHADER_01_H
#define TOON_EDGES_PIXEL_SHADER_01_H

#include <Windows.h>
#include <xnamath.h>
#include "CompiledToonEdgesPixelShader01.h"
#include "PixelShader.h"
#include "ShaderDataStructures.h"

class ToonEdgesPixelShader01 : public PixelShader
{
public:
	ToonEdgesPixelShader01( void );
	virtual HRESULT Initialise( ID3D11Device* pDevice );
	virtual HRESULT Cleanup( void );
	virtual HRESULT UpdatePerSceneData( ID3D11DeviceContext* pContext, const PerSceneData& perSceneData);
	virtual HRESULT UpdatePerFrameData( ID3D11DeviceContext* pContext, const PerFrameData& perFrameData);
	virtual HRESULT UpdatePerObjectData( ID3D11DeviceContext* pContext, const PerObjectData& perObjectData);
	virtual HRESULT UpdateTextureResource( int index, ID3D11DeviceContext* pContext, ID3D11ShaderResourceView* pTexture, ID3D11SamplerState* pSamplerState );
private:
	struct ConstBufferPerScene
	{
		XMFLOAT4   m_edgeColour;	// The colour to paint the outline in
	};

	ConstBufferPerScene  m_cbPerScene;
	ID3D11Buffer*		 m_pCbPerSceneBuffer;
};


#endif