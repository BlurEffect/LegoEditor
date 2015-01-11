/* 
*  Kevin Meergans, Improved Lego Editor, 2014
*  TextRenderer.h
*  Responsible for rendering all texts being displayed on the screen.
*/

#ifndef TEXT_RENDERER_H
#define TEXT_RENDERER_H

#include <windows.h>
#include <memory>
#include <d3d11.h>
#include <xnamath.h>

// forward declaration
class TextRendererImplementation;
struct SentenceData;
struct EditorData;
struct PerformanceData;

class TextRenderer
{
public:
	TextRenderer();
	HRESULT Initialise( ID3D11Device* pDevice, ID3D11DeviceContext* pDeviceContext, HWND hwnd, int screenWidth, int screenHeight, int maxSentenceLength, const XMFLOAT4X4& baseViewMatrix );
	HRESULT Cleanup();
	void	Render( ID3D11DeviceContext* pContext, const XMFLOAT4X4& worldMatrix , const XMFLOAT4X4& orthoMatrix, const EditorData& editorData, int numberOfBricks, int bricksRendered, int numberOfStuds, int studsRendered, const PerformanceData& performanceData );
private:
	std::tr1::shared_ptr<TextRendererImplementation> m_pImplementation;
};

#endif