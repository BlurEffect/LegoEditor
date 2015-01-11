/* 
*  Kevin Meergans, Improved Lego Editor, 2014
*  Input.cpp
*  Contains the function definitions for the Input class. Calls to these
*  functions will be forwarded to the implementation part of the mesh class
*  "InputImplementation".
*/

#include "Input.h"
#include "InputImplementation.h"


Input::Input( void ) : m_pImplementation( new InputImplementation() )
{
}

HRESULT Input::Initialise( HINSTANCE hInst, HWND hWnd )
{
	return m_pImplementation -> Initialise( hInst, hWnd);
}

void Input::Update( EditorInput* pEditorInput, CameraInput* pCameraInput )
{
	m_pImplementation -> Update( pEditorInput, pCameraInput );
}

HRESULT Input::Cleanup( void )
{
	return m_pImplementation -> Cleanup();
}