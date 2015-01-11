/* 
*  Kevin Meergans, Improved Lego Editor, 2014
*  Cursor.cpp
*  Contains the function definitions for the Cursor class. Calls to these
*  functions will be forwarded to the implementation part of the cursor class
*  "CursorImplementation".
*/

#include "Cursor.h"
#include "CursorImplementation.h"

Cursor::Cursor() : m_pImplementation( new CursorImplementation() )
{
}

HRESULT Cursor::Initialise( ID3D11Device* pDevice, XMFLOAT3 position, XMFLOAT3 extents )
{
	return m_pImplementation -> Initialise( pDevice, position, extents );
}

HRESULT Cursor::Cleanup()
{
	return m_pImplementation -> Cleanup();
}

void Cursor::Render( ID3D11DeviceContext* pDeviceContext)
{
	m_pImplementation -> Render( pDeviceContext );
}