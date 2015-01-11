/* 
*  Kevin Meergans, Improved Lego Editor, 2014
*  GridImplementation.h
*  Implementation part of the Grid class.The public interface of this class
*  and the one of the Grid class have to be kept consistent. 
*/

#ifndef GRID_IMPLEMENTATION_H
#define GRID_IMPLEMENTATION_H

#include <windows.h>
#include <memory>
#include <d3d11.h>
#include <d3dx11.h>
#include "EditorGeometryDataStructures.h"


class GridImplementation
{
public:
	GridImplementation();

	HRESULT Initialise( ID3D11Device* pDevice, XMFLOAT3 centre, int width, int length, float gridUnitX, float gridUnitZ );
	HRESULT Cleanup();
	void	Render( ID3D11DeviceContext* );

private:
	ID3D11Buffer*	m_pVertexBuffer;	
	ID3D11Buffer*	m_pIndexBuffer;		
	int				m_vertexCount;
	int				m_indexCount;
};

#endif