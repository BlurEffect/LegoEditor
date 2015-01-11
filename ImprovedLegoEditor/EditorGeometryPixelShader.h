/* 
*  Kevin Meergans, Improved Lego Editor, 2014
*  EditorGeometryPixelShader.h
*  Wrapper for the "PS_EditorGeometry.fx" pixel shader
*  Forwards the input colour as the final colour for th pixel.
*/

#ifndef EDITOR_GEOMETRY_PIXEL_SHADER_H
#define EDITOR_GEOMETRY_PIXEL_SHADER_H

#include <Windows.h>
#include <xnamath.h>
#include "CompiledEditorGeometryPixelShader.h"
#include "PixelShader.h"
#include "ShaderDataStructures.h"

class EditorGeometryPixelShader : public PixelShader
{
public:
	EditorGeometryPixelShader( void );
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