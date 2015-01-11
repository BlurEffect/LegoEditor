/* 
*  Kevin Meergans, Improved Lego Editor, 2014
*  InputImplementation.h
*  Implementation part of the Input class.The public interface of this class
*  and the one of the Input class have to be kept consistent.
*/

#ifndef INPUT_IMPLEMENTATION_H
#define INPUT_IMPLEMENTATION_H

#define DIRECTINPUT_VERSION 0x0800 // define direct input version

#include <windows.h>	
#include <dinput.h>	  // for direct input
#include "InputDataStructures.h"

//--------------------------------------------------------------------------------------
// Depending on the current mode, different actions will be carried out when the user moves the mouse 
// or clicks its buttons. The modes are mutually exclusive.
//--------------------------------------------------------------------------------------
enum MouseMode
{
	Selection,			// moving the mouse moves the cursor around and clicking will lead to add/delete actions
	CameraDrag,			// active when the middle mouse button is held down, the camera is moved around according to the mouse movements
	CameraLookAround	// active when the right mouse button is down, moving the mouse will rotate the camera
};

class InputImplementation
{
public:

	InputImplementation( void );

	HRESULT Initialise( HINSTANCE hInst, HWND hWnd );
	void	Update( EditorInput* pEditorInput, CameraInput* pCameraInput );
	HRESULT Cleanup( void );

private:

	MouseMode     m_currentMouseMode;		// the current mouse mode (see enum definition above for details)
	bool	      m_wasLeftMouseButtonDown; // tells whether the left mouse button was down during the last frame
	DIMOUSESTATE2 m_oldMouseState;			// stores the mouse state of the latest frame to be able to detect state changes
	char		  m_oldKeyboardState[256];  // stores the keyboard state of the latest frame to be able to distinguish between key presses
											// and keys being held down

	// Needed for direct input
	LPDIRECTINPUT8		 m_pDI;				// pointer to the Direct Input object
	LPDIRECTINPUTDEVICE8 m_pDIMouseDevice;		// the Direct Input mouse device
	LPDIRECTINPUTDEVICE8 m_pDIKeyboardDevice;  // the Direct Input keyboard device
	
	// Wrapped direct input functions
	HRESULT WINAPI SetupDirectInput( HINSTANCE hInst, HWND hWnd );
	void    WINAPI ProcessMouseInput( EditorInput* pEditorInput, CameraInput* pCameraInput );
	void    WINAPI ProcessKeyboardInput( EditorInput* pEditorInput );
	HRESULT WINAPI CleanupDirectInput();
};

#endif