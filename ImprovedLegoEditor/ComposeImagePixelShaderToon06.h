/* 
*  Kevin Meergans, Improved Lego Editor, 2014
*  ComposeImagePixelShaderToon06.h
*  Wrapper for the "PS_ComposeImageToon06.fx" pixel shader.
*  Applies a sobel filter on the depth (and possibly normal) information of a scene contained
*  in textures provided to the shader. The shader also composes the edges with the actual 
*  shaded image provided as another texture.
*/

#ifndef COMPOSE_IMAGE_PIXEL_SHADER_TOON_06_H
#define COMPOSE_IMAGE_PIXEL_SHADER_TOON_06_H

#include <Windows.h>
#include <xnamath.h>
#include "CompiledComposeImagePixelShader06.h"
#include "PixelShader.h"
#include "ShaderDataStructures.h"

class ComposeImagePixelShaderToon06 : public PixelShader
{
public:
	ComposeImagePixelShaderToon06( void );
	virtual HRESULT Initialise( ID3D11Device* pDevice );
	virtual HRESULT Cleanup( void );
	virtual HRESULT UpdatePerSceneData( ID3D11DeviceContext* pContext, const PerSceneData& perSceneData);
	virtual HRESULT UpdatePerFrameData( ID3D11DeviceContext* pContext, const PerFrameData& perFrameData);
	virtual HRESULT UpdatePerObjectData( ID3D11DeviceContext* pContext, const PerObjectData& perObjectData);
	virtual HRESULT UpdateTextureResource( int index, ID3D11DeviceContext* pContext, ID3D11ShaderResourceView* pTexture, ID3D11SamplerState* pSamplerState );
private:
	struct ConstBufferPerScene
	{
		float	 m_viewportWidth;			// Width of the window the application is running in (in pixels)
		float	 m_viewportHeight;			// Height of the window the application is running in (in pixels)
		float	 m_thickness;				// Determines the width of the outline around the silhouettes of objects
		float	 m_thresholdNormalsEdges;	// Determines how many edges are being drawn/how fine grained the result will be
		float	 m_thresholdDepthEdges;		// Determines how many edges are being drawn/how fine grained the result will be
		XMFLOAT3 m_padding;
	};

	ConstBufferPerScene  m_cbPerScene;
	ID3D11Buffer*		 m_pCbPerSceneBuffer;

	// m_pTextures[0] -> colour map
	// m_pTextures[1] -> normal/depth map
	ID3D11ShaderResourceView*	m_pTextures[2];			
	ID3D11SamplerState*		    m_pSamplerStates[2];		
};


#endif