/* 
*  Kevin Meergans, Improved Lego Editor, 2014
*  Application.cpp
*  Contains the entry point for the application and is responsible for creating, updating
*  and cleaning up a window and an editor object.
*/

#include <windows.h>
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dx10.h>

#include "Editor.h"

// global variables

HINSTANCE	g_hInst		= NULL;
HWND        g_hWnd		= NULL;		// the handle to the window the application is running in
int			g_width		= 400;		// the width of the window in pixels
int			g_height	= 400;		// the height of the window in pixels
Editor		g_editor;				// the lego editor

// forward declarations

HRESULT Cleanup( void );
HRESULT InitialiseWindow( HINSTANCE hInstance, int nCmdShow );
LRESULT CALLBACK WndProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam );

//--------------------------------------------------------------------------------------
// Entry point to the program. Initializes everything and goes into a message processing 
// loop. Idle time is used to update the editor.
//--------------------------------------------------------------------------------------
int WINAPI WinMain( HINSTANCE   hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)          
{
 
	UNREFERENCED_PARAMETER( hPrevInstance );
    UNREFERENCED_PARAMETER( lpCmdLine );

    if( FAILED( InitialiseWindow( hInstance, nCmdShow ) ) )
        return 0;

	if( FAILED( g_editor.Initialise( hInstance, g_hWnd, g_width, g_height ) ) )
		return 0;

    // Main message loop
    MSG msg = {0};
    while( WM_QUIT != msg.message )
    {
        if( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ) )
        {
            TranslateMessage( &msg );
            DispatchMessage( &msg );
        }
        else
        {
			// update the editor, "game loop"
            g_editor.Update();
        }
    }

    if( FAILED( Cleanup() ) )
		return 0;

    return ( int )msg.wParam;
}

//--------------------------------------------------------------------------------------
// Cleanup the application (termination)
//--------------------------------------------------------------------------------------
HRESULT Cleanup( void )
{
	if( FAILED( g_editor.Cleanup() ) )
		return E_FAIL;

	// unregister the window class to free up memory
	UnregisterClass( L"LegoEditorWindowClass", g_hInst );

	// editor -> cleanup
	return S_OK;
}

//--------------------------------------------------------------------------------------
// Register class and create window
//--------------------------------------------------------------------------------------
HRESULT InitialiseWindow( HINSTANCE hInstance, int nCmdShow )
{
    // Register class
    WNDCLASSEX wcex;
    wcex.cbSize			= sizeof( WNDCLASSEX );
    wcex.style			= CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc	= WndProc;
    wcex.cbClsExtra		= 0;
    wcex.cbWndExtra		= 0;
    wcex.hInstance		= hInstance;
    wcex.hIcon			= LoadIcon( NULL, IDI_APPLICATION );
    wcex.hCursor		= LoadCursor( NULL, IDC_ARROW );
    wcex.hbrBackground	= ( HBRUSH )( COLOR_WINDOW + 1 );
    wcex.lpszMenuName	= NULL;
    wcex.lpszClassName	= L"LegoEditorWindowClass";
    wcex.hIconSm		= LoadIcon( NULL, IDI_APPLICATION );

	// Window class could not be registered
    if( !RegisterClassEx( &wcex ) )
        return E_FAIL;

    // Create window
    g_hInst = hInstance;

	// Determine the resolution of the screen
	g_width  = GetSystemMetrics(SM_CXSCREEN);
	g_height = GetSystemMetrics(SM_CYSCREEN);

	// Setup screen settings for full screen
	DEVMODE dmScreenSettings;
	memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
	dmScreenSettings.dmSize       = sizeof(dmScreenSettings);
	dmScreenSettings.dmPelsWidth  = (unsigned long)g_width;
	dmScreenSettings.dmPelsHeight = (unsigned long)g_height;
	dmScreenSettings.dmBitsPerPel = 32;			
	dmScreenSettings.dmFields     = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

	// Change the display settings to full screen.
	ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN);

    g_hWnd = CreateWindow( L"LegoEditorWindowClass", L"Lego Editor",
                           WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_POPUP,
						   0, 0, g_width, g_height, NULL, NULL, hInstance,
                           NULL );

	// window could not be created
    if( !g_hWnd )
        return E_FAIL;

	ShowWindow(g_hWnd, SW_SHOW);
    return S_OK;
}

//--------------------------------------------------------------------------------------
// Called every time the application receives a message
//--------------------------------------------------------------------------------------
LRESULT CALLBACK WndProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{

    switch( message )
    {
        case WM_DESTROY:
            PostQuitMessage( 0 );
            break;

        default:
            return DefWindowProc( hWnd, message, wParam, lParam );
    }

    return 0;
}