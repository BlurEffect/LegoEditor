/* 
*  Kevin Meergans, Improved Lego Editor, 2014
*  EditorImplementation.h
*  Implementation part of the Editor class. The public interface of this class
*  and the one of the Editor class have to be kept consistent.
*/

#ifndef EDITOR_IMPLEMENTATION_H
#define EDITOR_IMPLEMENTATION_H

#include <windows.h>
#include "Renderer.h"
#include "EditorCamera.h"
#include "Settings.h"
#include "Input.h"
#include "InputDataStructures.h"
#include "EditorDataStructures.h"
#include "Helpers.h"
#include "LegoWorld.h"
#include "PerformanceTimer.h"
#include <iostream>

class EditorImplementation
{
public:
	EditorImplementation() ;

	HRESULT		Initialise( HINSTANCE hInst, HWND hWnd, int windowWidth, int windowHeight );
	HRESULT		Cleanup( void );
	void		Update( void );

private:

	void	UpdateEditorData( void );
	void	Save( void );
	void	Load( void );
	void	StartRecording( void );
	void	StopRecording( void );

	int				m_windowWidth;		// todo: move these to editor state later on?
	int				m_windowHeight;

	HWND			m_windowHandle;		// Handle to the window, in which the application is running

	Renderer		m_renderer;			// Render component of the application, responsible for drawing the scene
	EditorCamera	m_editorCamera;		// Camera used within the editor
	Input			m_input;			// Component responsible to detect user input
	LegoWorld		m_legoWorld;		// The representation of the lego world

	EditorData		m_editorData;		// used for communication with the renderer class

	EditorInput		m_editorInput;		// used for communication with the input class
	CameraInput		m_cameraInput;		// used for communication with the input and camera class

	PerformanceTimer m_performanceTimer;// used to measure performance of the application

};

#endif