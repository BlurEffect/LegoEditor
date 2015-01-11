/* 
*  Kevin Meergans, Improved Lego Editor, 2014
*  Editor.cpp
*  Contains the function definitions for the Renderer class. Calls to these
*  functions will be forwarded to the implementation part of the renderer class
*  "RendererImplementation".
*/

#include "Renderer.h"
#include "RendererImplementation.h"

//--------------------------------------------------------------------------------------
// Constructor, dynamically create an implementation object, to which all public function
// calls to this object will be forwarded. Part of separation of interface and 
// implementations.
//--------------------------------------------------------------------------------------

Renderer::Renderer() : m_pImplementation( new RendererImplementation() )
{
}

HRESULT Renderer::Initialise( HWND hWnd, int windowWidth, int windowHeight, const XMFLOAT4X4& baseViewMatrix )
{
	return m_pImplementation -> Initialise( hWnd, windowWidth, windowHeight, baseViewMatrix );
}

HRESULT Renderer::Cleanup( void )
{
	return m_pImplementation -> Cleanup();
}

void Renderer::Update( const XMFLOAT4X4& viewMatrix, const XMFLOAT4X4& projMatrix, const XMFLOAT4X4& orthoProjMatrix, const EditorData& editorData, int numberOfBricks, int numberOfStuds, const PerformanceData& performanceData, const XMFLOAT3& cameraPosition )
{
	m_pImplementation -> Update( viewMatrix, projMatrix, orthoProjMatrix, editorData, numberOfBricks, numberOfStuds, performanceData, cameraPosition );
}

RenderContext* Renderer::GetRenderContext( void )
{
	return m_pImplementation -> GetRenderContext();
}
