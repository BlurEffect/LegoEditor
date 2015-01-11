/* 
*  Kevin Meergans, Improved Lego Editor, 2014
*  Input.h
*  The Input class is responsible for detecting user input. 
*/

#ifndef INPUT_H
#define INPUT_H

#include <windows.h>
#include <memory>

// forward declaration
class  InputImplementation;
struct EditorInput;
struct CameraInput;

class Input
{
public:

	Input( void );

	HRESULT Initialise( HINSTANCE hInst, HWND hWnd );
	void	Update( EditorInput* pEditorInput, CameraInput* pCameraInput );
	HRESULT Cleanup( void );
private:
	std::tr1::shared_ptr<InputImplementation> m_pImplementation;
};

#endif