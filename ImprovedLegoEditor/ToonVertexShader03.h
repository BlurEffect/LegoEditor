/* 
*  Kevin Meergans, Improved Lego Editor, 2014
*  ToonVertexShader03.h
*  Wrapper for the "VS_Toon03.fx" vertex shader.
*  Uses the dot product between the normal of a vertex and the eye vector to determine
*  whether a vertex lies close to a silhouette edge and passes that value on to the
*  pixel shader, together with the transformed position, normal and the vertex colour.
*/

#ifndef TOON_VERTEX_SHADER_03_H
#define TOON_VERTEX_SHADER_03_H

#include <Windows.h>
#include <xnamath.h>
#include "CompiledToonVertexShader03.h"
#include "VertexShader.h"
#include "ShaderDataStructures.h"

class ToonVertexShader03 : public VertexShader
{
public:
	ToonVertexShader03( void );
	virtual HRESULT Initialise( ID3D11Device* pDevice );
	virtual HRESULT Cleanup( void );
	virtual HRESULT UpdatePerSceneData( ID3D11DeviceContext* pContext, const PerSceneData& perSceneData);
	virtual HRESULT UpdatePerFrameData( ID3D11DeviceContext* pContext, const PerFrameData& perFrameData);
	virtual HRESULT UpdatePerObjectData( ID3D11DeviceContext* pContext, const PerObjectData& perObjectData);
	virtual HRESULT UpdateTextureResource( int index, ID3D11DeviceContext* pContext, ID3D11ShaderResourceView* pTexture, ID3D11SamplerState* pSamplerState );
private:

	const static D3D11_INPUT_ELEMENT_DESC m_sInputLayoutDescription[9];

	struct ConstBufferPerFrame
	{
		XMFLOAT4X4 m_viewProjection;  // The combined view and projection matrix
		XMFLOAT3   m_viewPosition;	  // The world position of the camera
		float	   m_padding;
	};

	ConstBufferPerFrame  m_cbPerFrame;
	ID3D11Buffer*		 m_pCbPerFrameBuffer;

};


#endif