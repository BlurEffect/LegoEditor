/* 
*  Kevin Meergans, Improved Lego Editor, 2014
*  TextRenderer.cpp
*  Contains the function definitions for the TextRenderer class. Calls to these
*  functions will be forwarded to the implementation part of the TextRenderer class
*  "TextRendererImplementation".
*/

#include "TextRenderer.h"
#include "TextRendererImplementation.h"

TextRenderer::TextRenderer() : m_pImplementation( new TextRendererImplementation() )
{
}

HRESULT TextRenderer::Initialise( ID3D11Device* pDevice, ID3D11DeviceContext* pDeviceContext, HWND hwnd, int screenWidth, int screenHeight, int maxSentenceLength, const XMFLOAT4X4& baseViewMatrix )
{
	return m_pImplementation -> Initialise( pDevice, pDeviceContext, hwnd, screenWidth, screenHeight, maxSentenceLength, baseViewMatrix );
}

HRESULT TextRenderer::Cleanup()
{
	return m_pImplementation -> Cleanup();
}

void TextRenderer::Render( ID3D11DeviceContext* pContext, const XMFLOAT4X4& worldMatrix , const XMFLOAT4X4& orthoMatrix, const EditorData& editorData, int numberOfBricks, int bricksRendered, int numberOfStuds, int studsRendered, const PerformanceData& performanceData )
{
	m_pImplementation -> Render( pContext, worldMatrix , orthoMatrix, editorData, numberOfBricks, bricksRendered, numberOfStuds, studsRendered, performanceData );
}
