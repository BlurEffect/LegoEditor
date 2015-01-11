/* 
*  Kevin Meergans, Improved Lego Editor, 2014
*  EditorImplementation.cpp
*  Contains the function definitions for the EditorImplementation class.
*/

#include "EditorImplementation.h"

EditorImplementation::EditorImplementation() : m_windowWidth( 0 ),
											   m_windowHeight( 0 ),
											   m_windowHandle( nullptr )
{
}


//--------------------------------------------------------------------------------------
// Initialise the editor and its components
//--------------------------------------------------------------------------------------
HRESULT EditorImplementation::Initialise( HINSTANCE hInst, HWND hWnd, int windowWidth, int windowHeight )
{

	m_windowWidth  = windowWidth;
	m_windowHeight = windowHeight;

	// update the number of custom structures
	m_editorData.m_numberOfCustomStructures = m_legoWorld.GetNumberOfCustomStructures();

	HRESULT hr = SUCCEEDED( m_editorCamera.Initialise( XMFLOAT3(0,0,-1), XMFLOAT3(0,0,0), XMFLOAT3(0,1,0), FIELD_OF_VIEW, m_windowWidth, m_windowHeight, NEAR_CLIPPING_PLANE, FAR_CLIPPING_PLANE ) ) &&
				 SUCCEEDED( m_renderer.Initialise( hWnd, m_windowWidth, m_windowHeight, *m_editorCamera.GetViewMatrix() ) ) &&
				 SUCCEEDED( m_input.Initialise( hInst, hWnd ) ) &&
				 SUCCEEDED( m_legoWorld.Initialise() ) &&
				 SUCCEEDED( m_performanceTimer.Initialise() );

	if( SUCCEEDED( hr ) )
	{
		// update the number of custom structures
		m_editorData.m_numberOfCustomStructures = m_legoWorld.GetNumberOfCustomStructures();
	}

	return hr;
}

//--------------------------------------------------------------------------------------
// Cleanup all components
//--------------------------------------------------------------------------------------
HRESULT	EditorImplementation::Cleanup( void )
{
	// todo: does editor have its own stuff to cleanup???

	return SUCCEEDED( m_renderer.Cleanup() ) &&
		   SUCCEEDED( m_editorCamera.Cleanup() ) &&
		   SUCCEEDED( m_input.Cleanup() ) &&
		   SUCCEEDED( m_legoWorld.Cleanup() ) &&
		   SUCCEEDED( m_performanceTimer.Cleanup() );
	
}

//--------------------------------------------------------------------------------------
// Contains the "game loop", updates all components
//--------------------------------------------------------------------------------------
void EditorImplementation::Update( void )
{
	m_performanceTimer.Update();
	m_input.Update( &m_editorInput, &m_cameraInput );
	m_editorCamera.Update( m_cameraInput );
	UpdateEditorData();
	m_legoWorld.Update( m_renderer.GetRenderContext(), m_editorCamera.GetFrustumPlanes() );
	m_renderer.Update( *m_editorCamera.GetViewMatrix(), *m_editorCamera.GetProjectionMatrix(), *m_editorCamera.GetOrthoProjectionMatrix(), m_editorData, m_legoWorld.GetNumberOfBricks(), m_legoWorld.GetNumberOfStuds(), m_performanceTimer.GetPerformanceData(), m_editorCamera.GetCameraPosition() );
}

//--------------------------------------------------------------------------------------
// Update the editor data structure according to the user input
//--------------------------------------------------------------------------------------
void EditorImplementation::UpdateEditorData( void )
{
	// Process user input

	// Check for termination of the application
	if( m_editorInput.m_doQuit )
	{
		PostQuitMessage(0);
		return;
	}

	// Switch between creation and deletion mode if necessary
	if( m_editorInput.m_doToggleDeletionMode )
		m_editorData.m_isDeletionModeActive = !m_editorData.m_isDeletionModeActive;

	// Enable/Disable recording mode
	if( m_editorInput.m_doTogglePresentationMode )
		m_editorData.m_isPresentationModeActive = !m_editorData.m_isPresentationModeActive;


	if( m_editorInput.m_doToggleRecordingMode )
	{
		m_editorData.m_isRecordingModeActive = !m_editorData.m_isRecordingModeActive;
		
		if( m_editorData.m_isRecordingModeActive )
		{
			StartRecording();
		}else
		{
			StopRecording();
		}
	}
		

	// todo: use better construct here, modulo, less branching?

	// Update current brick type and colour

	if( m_editorData.m_selectedBuildingBlock + m_editorInput.m_changeBrick >= NumberOfBrickTypes + m_editorData.m_numberOfCustomStructures )
	{
		m_editorData.m_selectedBuildingBlock = static_cast<LegoBrickType>( 0 );
	}else if( m_editorData.m_selectedBuildingBlock + m_editorInput.m_changeBrick < 0 )
	{
		m_editorData.m_selectedBuildingBlock = static_cast<LegoBrickType>( NumberOfBrickTypes + m_editorData.m_numberOfCustomStructures - 1 );
	}else
	{
		m_editorData.m_selectedBuildingBlock = static_cast<LegoBrickType>( m_editorData.m_selectedBuildingBlock + m_editorInput.m_changeBrick );
	}


	if( m_editorData.m_selectedBrickColour + m_editorInput.m_changeColour >= NumberOfColours )
	{
		m_editorData.m_selectedBrickColour = static_cast<LegoBrickColour>( 0 );
	}else if( m_editorData.m_selectedBrickColour + m_editorInput.m_changeColour < 0 )
	{
		m_editorData.m_selectedBrickColour = static_cast<LegoBrickColour>( NumberOfColours - 1 );
	}else
	{
		m_editorData.m_selectedBrickColour = static_cast<LegoBrickColour>( m_editorData.m_selectedBrickColour + m_editorInput.m_changeColour );
	}

	// Update shader group

	if( m_editorData.m_selectedShaderGroup + m_editorInput.m_changeShaderGroup >= NumberOfShaderGroups )
	{
		m_editorData.m_selectedShaderGroup = static_cast<ShaderGroups>( 1 ); // don't use editor geometry shaders
	}else if( m_editorData.m_selectedShaderGroup + m_editorInput.m_changeShaderGroup < 1 )
	{
		m_editorData.m_selectedShaderGroup = static_cast<ShaderGroups>( NumberOfShaderGroups - 1 );
	}else
	{
		m_editorData.m_selectedShaderGroup = static_cast<ShaderGroups>( m_editorData.m_selectedShaderGroup + m_editorInput.m_changeShaderGroup );
	}

	// Update grid, but only if the new level is within the defined bounds
	if( ( m_editorData.m_cursorPosition.m_y + m_editorInput.m_changeEditLevel < MAX_GRID_POS.m_y ) && ( m_editorData.m_cursorPosition.m_y + m_editorInput.m_changeEditLevel >= MIN_GRID_POS.m_y ) )
	{
		m_editorData.m_cursorPosition.m_y += m_editorInput.m_changeEditLevel;
	}

	// Get the new rotation
	if( !m_editorData.m_isDeletionModeActive)
	{
		m_editorData.m_brickRotation = ( m_editorData.m_brickRotation + m_editorInput.m_changeBrickRotation ) % 360;
	}
	
	if( m_editorData.m_selectedBuildingBlock < NumberOfBrickTypes )
	{
		m_editorData.m_cursorExtents = BrickSizesInUnits[m_editorData.m_selectedBuildingBlock];
	}else
	{
		m_editorData.m_customStructureName = m_legoWorld.GetCustomStructureName( m_editorData.m_selectedBuildingBlock - NumberOfBrickTypes ).c_str();
		m_legoWorld.GetExtentsOfStructure( m_editorData.m_selectedBuildingBlock - NumberOfBrickTypes, &m_editorData.m_cursorExtents );
	}

	/* Alternate implementation, todo: remove if rotation correctly displayed
	if( m_editorData.m_brickRotation + m_editorInput.m_changeBrickRotation >= 360 )
	{
		m_editorData.m_brickRotation -= 360;
	}else if ( m_editorData.m_brickRotation + m_editorInput.m_changeBrickRotation < 0 )
	{
		m_editorData.m_brickRotation += 360;
	}else
	{
		//m_editorData.m_brickRotation += m_editorInput.m_changeBrickRotation;
	}
	*/

	// Determine and set the new cursor/brick position

	// Get the position of the mouse cursor
	POINT winCursorPosition;
	LPPOINT pCursorPosition = &winCursorPosition;
	GetCursorPos(pCursorPosition);
	
	// Convert screen coordinates to client area coordinates
	ScreenToClient(m_windowHandle, pCursorPosition);

	// Create the description of the grid plane
	XMFLOAT4 gridPlane( 0.0f, 1.0f, 0.0f, 0.0f ); 

	XMFLOAT3 intersection( 0.0f, 0.0f, 0.0f );

	// Get the intersection of the ray from the cursor with the grid plane
	GetIntersection( winCursorPosition, &gridPlane,  m_editorData.m_cursorPosition.m_y * GRID_UNIT.y, m_windowWidth, m_windowHeight, m_editorCamera.GetViewMatrix(), &intersection );

	// Set the cursor/brick position

	if( intersection.x >= 0 )
		m_editorData.m_cursorPosition.m_x = static_cast<int>(intersection.x/GRID_UNIT.x);
	else
		m_editorData.m_cursorPosition.m_x = (static_cast<int>(intersection.x/GRID_UNIT.x) - 1);

	if( intersection.z >= 0 )
		m_editorData.m_cursorPosition.m_z = static_cast<int>(intersection.z/GRID_UNIT.z);
	else
		m_editorData.m_cursorPosition.m_z = (static_cast<int>(intersection.z/GRID_UNIT.z) - 1);

	if( m_editorInput.m_doAction && !m_editorData.m_isDeletionModeActive )
	{
		if( m_editorData.m_selectedBuildingBlock < NumberOfBrickTypes )
		{
			m_legoWorld.AddLegoBrick( m_editorData.m_selectedBuildingBlock, m_editorData.m_cursorPosition, m_editorData.m_brickRotation, m_editorData.m_selectedBrickColour );
		}else
		{
			m_legoWorld.AddLegoStructure( m_editorData.m_selectedBuildingBlock - NumberOfBrickTypes, m_editorData.m_cursorPosition, m_editorData.m_brickRotation );
		}

	}else if( m_editorInput.m_doAction && m_editorData.m_isDeletionModeActive )
	{
		m_legoWorld.RemoveLegoBrick( m_editorData.m_cursorPosition );
	}

	// save/load a lego world
	if( m_editorInput.m_doSave )
	{
		Save();
	}
	if( m_editorInput.m_doLoad )
	{
		Load();
	}
}

//--------------------------------------------------------------------------------------
// Save the current lego world.
//--------------------------------------------------------------------------------------
void EditorImplementation::Save( void )
{
	// todo: other form of I/O? Closing console will terminate application - meh

	// allocate a console to allow user input
	FILE *stream;
	AllocConsole();
	freopen_s(&stream, "CONIN$", "r+t", stdin);
	freopen_s(&stream, "CONOUT$", "w+t", stdout);
	freopen_s(&stream, "CONOUT$", "w+t", stderr);

	std::cout << "Please enter the name of the file, to which the lego world should be saved."
			  <<"\nIf you enter the name of an existing file, its contents will be overridden, \notherwise a new file will be created."
			  <<"\nEnter 'cancel' to cancel the saving process."
			  <<"\nDon't forget to append the ending '.txt' to the filename. \nPress enter after providing a name to proceed.\n";

	// todo: add validation of the filename and error handling

	// get a filename from the user to which the current lego world will be saved
	std::string filename;
	std::cin >> filename;
	if(filename != "cancel")
	{
		std::cout << "\nSaving...";
		m_legoWorld.Save(filename);
		std::cout << "\nSaving completed.";
	}

	// saving operation finished, get rid of console
	FreeConsole();
}

//--------------------------------------------------------------------------------------
// Load a lego world from a file.
//--------------------------------------------------------------------------------------
void EditorImplementation::Load( void )
{
	// todo: other form of I/O? Closing console will terminate application - meh

	// allocate a console to allow user input 
	FILE *stream;
	AllocConsole();
	freopen_s(&stream, "CONIN$", "r+t", stdin);
	freopen_s(&stream, "CONOUT$", "w+t", stdout);
	freopen_s(&stream, "CONOUT$", "w+t", stderr);

	std::cout << "Please enter the name of a file containing a lego world."
			  <<"\nDon't forget to append the ending '.txt' to the filename."
			  <<"\nEnter 'cancel' to cancel the loading process."
			  <<"\nPress enter after providing a name to proceed.\n";

	// todo: add validation of the filename and error handling

	// get a filename from the user
	std::string filename;
	std::cin >> filename;
	if(filename != "cancel")
	{
		std::cout << "\nLoading...";
		m_legoWorld.Load(filename);		
		std::cout << "\nLoading completed.";
	}

	// loading operation finished, get rid of console
	FreeConsole();
}

//--------------------------------------------------------------------------------------
// Start recording placed bricks to create a custom lego structure
//--------------------------------------------------------------------------------------
void EditorImplementation::StartRecording( void )
{
	m_legoWorld.StartRecording();
}

//--------------------------------------------------------------------------------------
// Stop recording bricks and store the recorded bricks as a new custom lego structure
// if desired by the user.
//--------------------------------------------------------------------------------------
void EditorImplementation::StopRecording( void )
{
	// get name for structure from user

	FILE *stream;
	AllocConsole();
	freopen_s(&stream, "CONIN$", "r+t", stdin);
	freopen_s(&stream, "CONOUT$", "w+t", stdout);
	freopen_s(&stream, "CONOUT$", "w+t", stderr);

	std::cout << "Please enter a name for the custom lego structure."
			  <<"\nEnter 'cancel' if you do not want to save the custom structure."
			  <<"\nPress enter after providing a name to proceed.\n";

	// todo: add validation of user input, make sure string is not already used as identifier

	std::string input;
	getline(std::cin, input);

	std::cout << "\nSaving...";

	// stop recording
	m_legoWorld.StopRecording( input != "cancel", input );

	// update the number of custom structures
	m_editorData.m_numberOfCustomStructures = m_legoWorld.GetNumberOfCustomStructures();
	

	std::cout << "\nCustom structure saved.";

	FreeConsole();
}