/* 
*  Kevin Meergans, Improved Lego Editor, 2014
*  Cursor.h
*  Contains functions to create and draw a cursor highlighting the 
*  position, rotation and extents of bricks to be placed. It's like a 
*  bounding box.
*/

#ifndef CURSOR_H
#define CURSOR_H

#include <windows.h>
#include <d3d11.h>
#include <memory>
#include <xnamath.h>

// forward declaration
class CursorImplementation;

class Cursor
{
public:
	Cursor();
	HRESULT Initialise( ID3D11Device* pDevice, XMFLOAT3 position, XMFLOAT3 extents );
	HRESULT Cleanup();
	void	Render( ID3D11DeviceContext* );
private:
	std::tr1::shared_ptr<CursorImplementation> m_pImplementation;
};

#endif