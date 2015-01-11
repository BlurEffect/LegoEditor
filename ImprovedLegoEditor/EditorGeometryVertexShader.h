/* 
*  Kevin Meergans, Improved Lego Editor, 2014
*  EditorGeometryVertexShader.h
*  Wrapper for the "VS_EditorGeometry.fx" vertex shader
*  Performs standard transformation of the vertex position and
*  passes it together with the vertex colour to the next stage.
*/

#ifndef EDITOR_GEOMETRY_VERTEX_SHADER_H
#define EDITOR_GEOMETRY_VERTEX_SHADER_H

#include <Windows.h>
#include <xnamath.h>
#include "CompiledEditorGeometryVertexShader.h"
#include "VertexShader.h"
#include "ShaderDataStructures.h"

class EditorGeometryVertexShader : public VertexShader
{
public:
	EditorGeometryVertexShader( void );
	virtual HRESULT Initialise( ID3D11Device* pDevice );
	virtual HRESULT Cleanup( void );
	virtual HRESULT UpdatePerSceneData( ID3D11DeviceContext* pContext, const PerSceneData& perSceneData);
	virtual HRESULT UpdatePerFrameData( ID3D11DeviceContext* pContext, const PerFrameData& perFrameData);
	virtual HRESULT UpdatePerObjectData( ID3D11DeviceContext* pContext, const PerObjectData& perObjectData);
	virtual HRESULT UpdateTextureResource( int index, ID3D11DeviceContext* pContext, ID3D11ShaderResourceView* pTexture, ID3D11SamplerState* pSamplerState );
private:

	const static D3D11_INPUT_ELEMENT_DESC m_sInputLayoutDescription[1];

	struct ConstBufferPerObject
	{
		XMFLOAT4X4  m_WVP;			// The combined world, view and projection matrices
		XMFLOAT4	m_colour;		// The vertex colour to use
	};

	ConstBufferPerObject m_cbPerObject;
	ID3D11Buffer*		 m_pCbPerObjectBuffer;
};


#endif