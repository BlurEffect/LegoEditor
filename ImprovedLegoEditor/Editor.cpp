/* 
*  Kevin Meergans, Improved Lego Editor, 2014
*  Editor.cpp
*  Contains the function definitions for the Editor class. Calls to these
*  functions will be forwarded to the implementation part of the editor class
*  "EditorImplementation".
*/

#include "Editor.h"
#include "EditorImplementation.h"

//--------------------------------------------------------------------------------------
// Constructor, dynamically create an implementation object, to which all public function
// calls to this object will be forwarded. Part of separation of interface and 
// implementations.
//--------------------------------------------------------------------------------------

Editor::Editor() : m_pImplementation( new EditorImplementation() )
{
}

HRESULT Editor::Initialise( HINSTANCE hInst, HWND hWnd, int windowWidth, int windowHeight )
{
	return m_pImplementation -> Initialise( hInst, hWnd, windowWidth, windowHeight );
}

HRESULT	Editor::Cleanup( void )
{
	return m_pImplementation -> Cleanup();
}

void Editor::Update( void )
{
	m_pImplementation -> Update();
}
