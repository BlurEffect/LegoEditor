/* 
*  Kevin Meergans, Improved Lego Editor, 2014
*  Editor.h
*  The Editor class is the central, coordinating class of the application. 
*  It delegates tasks and function calls to the other components and handles
*  communication between these components.
*/

#ifndef EDITOR_H
#define EDITOR_H

#include <windows.h>
#include <memory>
#include "Renderer.h"

// forward declaration
class EditorImplementation;
class Renderer;

class Editor
{
public:
	Editor();
	HRESULT		Initialise( HINSTANCE hInst, HWND hWnd, int windowWidth, int windowHeight );
	HRESULT		Cleanup( void );
	void		Update( void );

private:
	std::tr1::shared_ptr<EditorImplementation> m_pImplementation;	// pointer to the implementation/data of an editor object
};

#endif