/* 
*  Kevin Meergans, Improved Lego Editor, 2014
*  CursorImplementation.h
*  Implementation part of the Cursor class.The public interface of this class
*  and the one of the Cursor class have to be kept consistent. 
*/

#ifndef CURSOR_IMPLEMENTATION_H
#define CURSOR_IMPLEMENTATION_H

#include <windows.h>
#include <memory>
#include <d3d11.h>
#include <d3dx11.h>
#include "EditorGeometryDataStructures.h"


class CursorImplementation
{
public:
	CursorImplementation();

	HRESULT Initialise( ID3D11Device* pDevice, XMFLOAT3 position, XMFLOAT3 extents );
	HRESULT Cleanup();
	void	Render( ID3D11DeviceContext* );

private:
	ID3D11Buffer*	m_pVertexBuffer;	
	ID3D11Buffer*	m_pIndexBuffer;		
	int				m_vertexCount;
	int				m_indexCount;
};

#endif