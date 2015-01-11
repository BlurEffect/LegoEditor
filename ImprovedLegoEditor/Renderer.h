/* 
*  Kevin Meergans, Improved Lego Editor, 2014
*  Renderer.h
*  The Renderer class is responsible for drawing the scene. 
*  It sets up and manages DirectX 11.
*/

#ifndef RENDERER_H
#define RENDERER_H

#include <windows.h>
#include <memory>
#include <xnamath.h>
#include <vector>

// forward declaration
class RendererImplementation;
struct EditorData;
struct LegoBrick;
class RenderContext;
struct PerformanceData;

class Renderer
{
public:
	Renderer();
	HRESULT			Initialise( HWND hWnd, int windowWidth, int windowHeight, const XMFLOAT4X4& baseViewMatrix );
	HRESULT			Cleanup( void );
	void			Update( const XMFLOAT4X4& viewMatrix, const XMFLOAT4X4& projMatrix, const XMFLOAT4X4& orthoProjMatrix, const EditorData& editorData, int numberOfBricks, int numberOfStuds, const PerformanceData& performanceData, const XMFLOAT3& cameraPosition );
	RenderContext*  GetRenderContext( void );
private:
	std::tr1::shared_ptr<RendererImplementation> m_pImplementation;	
};

#endif