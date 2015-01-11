/* 
*  Kevin Meergans, Improved Lego Editor, 2014
*  Grid.h
*  Contains functions to create and draw a horizontal grid of square size.
*/

#ifndef GRID_H
#define GRID_H

#include <windows.h>
#include <d3d11.h>
#include <memory>
#include <xnamath.h>

// forward declaration
class GridImplementation;

class Grid
{
public:
	Grid();
	HRESULT Initialise( ID3D11Device* pDevice, XMFLOAT3 centre, int width, int length, float gridUnitX, float gridUnitZ );
	HRESULT Cleanup();
	void	Render( ID3D11DeviceContext* );
private:
	std::tr1::shared_ptr<GridImplementation> m_pImplementation;
};

#endif