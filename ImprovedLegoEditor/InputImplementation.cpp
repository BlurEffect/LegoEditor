/* 
*  Kevin Meergans, Improved Lego Editor, 2014
*  InputImplementation.cpp
*  Contains the function definitions for the InputImplementation class.
*/

#include "InputImplementation.h"


InputImplementation::InputImplementation(void) : m_currentMouseMode(Selection),	
												 m_wasLeftMouseButtonDown(false),
												 m_pDI(nullptr),
												 m_pDIMouseDevice(nullptr),
												 m_pDIKeyboardDevice(nullptr)
{
	ZeroMemory( &m_oldKeyboardState, 256 );
	ZeroMemory( &m_oldMouseState, sizeof( m_oldMouseState ) );
}

//--------------------------------------------------------------------------------------
// Initialise the input component.
//--------------------------------------------------------------------------------------
HRESULT InputImplementation::Initialise( HINSTANCE hInst, HWND hWnd )
{
	return SetupDirectInput( hInst, hWnd );
}

//--------------------------------------------------------------------------------------
// Process user input.
//--------------------------------------------------------------------------------------
void InputImplementation::Update( EditorInput* pEditorInput, CameraInput* pCameraInput )
{
	// Reset CameraInput and EditorInput structure
	pCameraInput->Reset();
	pEditorInput->Reset();

	ProcessKeyboardInput( pEditorInput );
	ProcessMouseInput	( pEditorInput, pCameraInput );
}

//--------------------------------------------------------------------------------------
// Cleanup the input component, free ressources.
//--------------------------------------------------------------------------------------
HRESULT InputImplementation::Cleanup( void )
{
	return CleanupDirectInput();
}

//--------------------------------------------------------------------------------------
// Initialise and set up direct input
//--------------------------------------------------------------------------------------
HRESULT WINAPI InputImplementation::SetupDirectInput( HINSTANCE hInst, HWND hWnd )
{ 
    HRESULT hr; 

    // Create the DirectInput object. 
    hr = DirectInput8Create( hInst, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pDI, NULL );
    if FAILED( hr ) 
		return hr;

	// Initialise the mouse device

    // Retrieve a pointer to an IDirectInputDevice8 interface for the mouse.
    hr = m_pDI -> CreateDevice( GUID_SysMouse, &m_pDIMouseDevice, NULL );
    if FAILED( hr ) 
    {
        return hr; 
    }

    // Set the data format using the predefined mouse data format.
    hr = m_pDIMouseDevice -> SetDataFormat( &c_dfDIMouse2 );
    if FAILED( hr ) 
    {
        return hr; 
    }

    // Set the cooperative level 
    hr = m_pDIMouseDevice -> SetCooperativeLevel( hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND );
    if FAILED( hr ) 
    { 
        return hr; 
    }

	// Get the input's device state and store it in 'MouseState'
	ZeroMemory( &m_oldMouseState, sizeof( m_oldMouseState ) );
	hr = m_pDIMouseDevice -> GetDeviceState( sizeof( DIMOUSESTATE2 ), &m_oldMouseState );
	if ( FAILED( hr ) )
	{
		// If input is lost, try to reacquire it
		hr = m_pDIMouseDevice -> Acquire();
		// todo: this might be an endless loop
		while ( hr == DIERR_INPUTLOST ) 
			hr = m_pDIMouseDevice -> Acquire();

		hr = m_pDIMouseDevice -> GetDeviceState( sizeof( DIMOUSESTATE2 ), &m_oldMouseState );
	}

	// Initialise the keyboard device

    // Retrieve a pointer to an IDirectInputDevice8 interface.
    hr = m_pDI -> CreateDevice( GUID_SysKeyboard, &m_pDIKeyboardDevice, NULL );
    if FAILED( hr ) 
    { 
        return hr;
    } 

    // Set the data format using the predefined mouse data format.
    hr = m_pDIKeyboardDevice -> SetDataFormat( &c_dfDIKeyboard ); 

    if FAILED( hr ) 
    { 
        return hr;
    } 

    // Set the cooperative level 
    hr = m_pDIKeyboardDevice -> SetCooperativeLevel( hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE ); 
    if FAILED( hr ) 
    { 
        return hr; 
    } 

	// initialise state of keyboard
	ZeroMemory(m_oldKeyboardState, 256);
	hr = m_pDIKeyboardDevice -> GetDeviceState( sizeof( m_oldKeyboardState ),( LPVOID )&m_oldKeyboardState ); 
	if FAILED( hr ) 
	{ 
		// Device might have been lost, try to reacquire it
		hr = m_pDIKeyboardDevice -> Acquire();

		// todo: this might be an endless loop
        while (hr == DIERR_INPUTLOST) 
			hr = m_pDIKeyboardDevice -> Acquire();

		hr = m_pDIKeyboardDevice -> GetDeviceState( sizeof( m_oldKeyboardState ),( LPVOID )&m_oldKeyboardState );
	} 

    return S_OK; 
}

//--------------------------------------------------------------------------------------
// Detect and process mouse button presses and movements.
//--------------------------------------------------------------------------------------
void WINAPI InputImplementation::ProcessMouseInput( EditorInput* pEditorInput, CameraInput* pCameraInput )
{
	HRESULT       hr;
    DIMOUSESTATE2 currentMouseState;      // DirectInput mouse state structure

    if (m_pDIMouseDevice)
	{
		// Get the input's device state and store it in 'MouseState'
	    ZeroMemory( &currentMouseState, sizeof( currentMouseState ) );
		hr = m_pDIMouseDevice -> GetDeviceState( sizeof( DIMOUSESTATE2 ), &currentMouseState );
		if ( FAILED( hr ) )
		{
			// If input is lost, try to reacquire it
			hr = m_pDIMouseDevice -> Acquire();
			// todo: this might be an endless loop
			while ( hr == DIERR_INPUTLOST ) 
				hr = m_pDIMouseDevice -> Acquire();

			hr = m_pDIMouseDevice -> GetDeviceState( sizeof( DIMOUSESTATE2 ), &currentMouseState );
		}

		// determine current mouse mode

		if( currentMouseState.rgbButtons[1] & 0x80 )		 // right mouse button is down
			m_currentMouseMode = CameraLookAround;
		else if( currentMouseState.rgbButtons[2] & 0x80 )	 // middle mouse button is down
			m_currentMouseMode = CameraDrag;
		else
			m_currentMouseMode = Selection;		

		// depending on mouse mode, update camera and editor input

		switch( m_currentMouseMode )
		{
		case Selection:
			if( ( currentMouseState.rgbButtons[0] & 0x80 ) )
			{
				if( !(m_oldMouseState.rgbButtons[0] & 0x80) ) // todo: check if this works (was !wasLeftMouseButtonDown)
				{
					pEditorInput->m_doAction = true;
					//todo: remove? wasLeftMouseButtonDown_ = true;
				}
			}
			else
			{
				// todo: remove? wasLeftMouseButtonDown_ = false;
			}
			break;
		case CameraLookAround:
			if( ( currentMouseState.lX != 0 ) || ( currentMouseState.lY != 0 ) )
			{
				pCameraInput->m_rotation.x = static_cast<float>( currentMouseState.lY );
				pCameraInput->m_rotation.y = static_cast<float>( currentMouseState.lX );
				pCameraInput->m_doUpdate   = true;
			}
			break;
		case CameraDrag:
			if( ( currentMouseState.lX != 0 ) || ( currentMouseState.lY != 0) )
			{
				pCameraInput->m_movement.x = - static_cast<float>( currentMouseState.lX );
				pCameraInput->m_movement.y = static_cast<float>( currentMouseState.lY );
				pCameraInput->m_doUpdate   = true;
			}
			break;
		}

		// Zoom
		if (currentMouseState.lZ != 0)
		{
			pCameraInput->m_movement.z = static_cast<float>( currentMouseState.lZ );
			pCameraInput->m_doUpdate   = true;
		}

		// remember the old mouse state in order to determine whether buttons have been pressed before or were pressed in the current frame
		memcpy(&m_oldMouseState, &currentMouseState, sizeof( DIMOUSESTATE2 ) );
	}
}

//--------------------------------------------------------------------------------------
// Detect and process key presses on the keyboard.
//--------------------------------------------------------------------------------------
void WINAPI InputImplementation::ProcessKeyboardInput( EditorInput* pEditorInput ) 
{ 
	// Define a macro to represent the key detection predicate.
	#define KEYDOWN(name, key) (name[key] & 0x80) 

 	// Create a buffer (memory space) to contain the key press data from the keyboard.
	char     buffer[256];
	HRESULT  hr;

	if ( m_pDIKeyboardDevice )
	{
		// Clear the keyboard data buffer - just in case.
		ZeroMemory( buffer, 256 );

		// What is the current state of the keyboard?
		hr = m_pDIKeyboardDevice -> GetDeviceState( sizeof( buffer ),( LPVOID )&buffer ); 
		if FAILED( hr ) 
		{ 
			// If this failed, the device has probably been lost.
			// Check for (hr == DIERR_INPUTLOST) and attempt to reacquire it here.
			hr = m_pDIKeyboardDevice -> Acquire();
			while ( hr == DIERR_INPUTLOST ) 
				hr = m_pDIKeyboardDevice -> Acquire();

			hr = m_pDIKeyboardDevice -> GetDeviceState( sizeof( buffer ),( LPVOID )&buffer );
		} 

		// update the keyboard editor input

		// quit the application when 'q' is pressed and wasn't pressed the frame before
		pEditorInput -> m_doQuit = ( KEYDOWN( buffer, DIK_ESCAPE ) > 0 );

		// todo: reduce branching below?

		// move the grid up or down (change edit level)
		if ( ( KEYDOWN( buffer, DIK_UP ) ) && ( !KEYDOWN( m_oldKeyboardState, DIK_UP ) ) )
			pEditorInput -> m_changeEditLevel = 1;
		else if( ( KEYDOWN( buffer, DIK_DOWN ) ) && ( !KEYDOWN( m_oldKeyboardState, DIK_DOWN ) ) )
			pEditorInput -> m_changeEditLevel = -1;
		else
			pEditorInput -> m_changeEditLevel = 0;

		// rotate bricks
		if ( ( KEYDOWN( buffer, DIK_LEFT ) ) && ( !KEYDOWN( m_oldKeyboardState, DIK_LEFT ) ) )
			pEditorInput->m_changeBrickRotation = -90;

		if ( ( KEYDOWN( buffer, DIK_RIGHT ) ) && ( !KEYDOWN( m_oldKeyboardState, DIK_RIGHT ) ) )
			pEditorInput->m_changeBrickRotation = 90;

		// switch colours
		if ( ( KEYDOWN( buffer, DIK_M ) ) && ( !KEYDOWN( m_oldKeyboardState, DIK_M ) ) )
			pEditorInput->m_changeColour = 1;
		else if( ( KEYDOWN( buffer, DIK_N ) ) && ( !KEYDOWN( m_oldKeyboardState, DIK_N ) ) )
			pEditorInput->m_changeColour = -1;
		else
			pEditorInput->m_changeColour = 0;
	
		// switch shader groups
		if ( ( KEYDOWN( buffer, DIK_V ) ) && ( !KEYDOWN( m_oldKeyboardState, DIK_V ) ) )
			pEditorInput->m_changeShaderGroup = 1;
		else if( ( KEYDOWN( buffer, DIK_C ) ) && ( !KEYDOWN( m_oldKeyboardState, DIK_C ) ) )
			pEditorInput->m_changeShaderGroup = -1;
		else
			pEditorInput->m_changeShaderGroup = 0;

		// switch brick types
		if ( ( KEYDOWN( buffer, DIK_X ) ) && ( !KEYDOWN( m_oldKeyboardState, DIK_X ) ) )
			pEditorInput->m_changeBrick = 1;
		else if ( ( KEYDOWN( buffer, DIK_Z ) ) && ( !KEYDOWN( m_oldKeyboardState, DIK_Z ) ) )
			pEditorInput->m_changeBrick = -1;
		else
			pEditorInput->m_changeBrick = 0;

		// toggle deletion mode ('delete' being pressed and not down in the frame before)
		if ( ( KEYDOWN( buffer, DIK_DELETE ) ) && ( !KEYDOWN( m_oldKeyboardState, DIK_DELETE ) ) )
			pEditorInput -> m_doToggleDeletionMode = true;

		// save the lego world ('ctrl' and 's' being pressed and not down in the frame before)
		pEditorInput -> m_doSave = ( KEYDOWN( buffer, DIK_LCONTROL ) && KEYDOWN( buffer, DIK_S ) ) && ( !( KEYDOWN( m_oldKeyboardState, DIK_LCONTROL ) && KEYDOWN( m_oldKeyboardState, DIK_S ) ) );

		// load a lego world ('ctrl' and 'l' being pressed and not down in the frame before)
		pEditorInput -> m_doLoad = ( KEYDOWN( buffer, DIK_LCONTROL ) && KEYDOWN( buffer, DIK_L ) ) && ( !( KEYDOWN( m_oldKeyboardState, DIK_LCONTROL ) && KEYDOWN( m_oldKeyboardState, DIK_L ) ) );

		// toggle recording mode ('ctrl' and 'r' being pressed and not down in the frame before)
		if( ( KEYDOWN( buffer, DIK_LCONTROL ) && KEYDOWN( buffer, DIK_R ) ) && ( !( KEYDOWN( m_oldKeyboardState, DIK_LCONTROL ) && KEYDOWN( m_oldKeyboardState, DIK_R ) ) ) )
			pEditorInput -> m_doToggleRecordingMode = true;

		// toggle presentation mode ('space' being pressed and not down in the frame before)
		if( ( KEYDOWN( buffer, DIK_SPACE ) ) && ( !( KEYDOWN( m_oldKeyboardState, DIK_SPACE ) ) ) )
			pEditorInput -> m_doTogglePresentationMode = true;

		// remember the old keyboard state in order to determine whether keys were pressed in the current frame or have already been pressed before
		memcpy( m_oldKeyboardState, buffer, 256 );
	}
}

//--------------------------------------------------------------------------------------
// Cleanup direct input and free all associated ressources
//--------------------------------------------------------------------------------------
HRESULT WINAPI InputImplementation::CleanupDirectInput() 
{ 
    if (m_pDI) 
    { 
        // Release the mouse
		if (m_pDIMouseDevice) 
        { 
			// Unacquire device before releasing it
            m_pDIMouseDevice -> Unacquire(); 
            m_pDIMouseDevice -> Release();
            m_pDIMouseDevice =  nullptr; 
        } 
        
		// Release the keyboard
		if (m_pDIKeyboardDevice) 
        { 
			// Unacquire device before releasing it 
            m_pDIKeyboardDevice -> Unacquire(); 
            m_pDIKeyboardDevice -> Release();
            m_pDIKeyboardDevice =  nullptr; 
        }
		
		// Release the Direct Input Object
		m_pDI -> Release();
        m_pDI  = nullptr;
    } 

	return S_OK;
} 