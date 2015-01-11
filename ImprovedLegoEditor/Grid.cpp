/* 
*  Kevin Meergans, Improved Lego Editor, 2014
*  Grid.cpp
*  Contains the function definitions for the Mesh class. Calls to these
*  functions will be forwarded to the implementation part of the grid class
*  "GridImplementation".
*/

#include "Grid.h"
#include "GridImplementation.h"

Grid::Grid() : m_pImplementation( new GridImplementation() )
{
}

HRESULT Grid::Initialise( ID3D11Device* pDevice, XMFLOAT3 centre, int width, int length, float gridUnitX, float gridUnitZ )
{
	return m_pImplementation -> Initialise( pDevice, centre, width, length, gridUnitX, gridUnitZ );
}

HRESULT Grid::Cleanup()
{
	return m_pImplementation -> Cleanup();
}

void Grid::Render( ID3D11DeviceContext* pDeviceContext)
{
	m_pImplementation -> Render( pDeviceContext );
}