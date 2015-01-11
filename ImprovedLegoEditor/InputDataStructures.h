/* 
*  Kevin Meergans, Improved Lego Editor, 2014
*  InputDataStructures.h
*  Contains data structures used to forward user input between 
*  different components of the application.
*/

#ifndef INPUT_DATA_STRUCTURES_H
#define INPUT_DATA_STRUCTURES_H

#include <windows.h>
#include <xnamath.h>

//--------------------------------------------------------------------------------------
// Stores information that can be used to update the camera of the application.
//--------------------------------------------------------------------------------------
struct CameraInput
{
	CameraInput() : m_movement( 0, 0, 0 ), 
					m_rotation( 0, 0, 0 ), 
					m_doUpdate( false )
	{}

	XMFLOAT3	m_movement;		// movement along the camera's x, y and z axis
	XMFLOAT3	m_rotation;		// rotation around the camera's x, y and z axis (pitch, yaw, roll)
	bool		m_doUpdate;		// set if the camera should be updated (was moved/rotated), false otherwise

	//--------------------------------------------------------------------------------------
	// Resets the camera input to the default state (called before setting the new input).
	//--------------------------------------------------------------------------------------
	void Reset()
	{
		m_movement.x = 0.0f;
		m_movement.y = 0.0f;
		m_movement.z = 0.0f;

		m_rotation.x = 0.0f;
		m_rotation.y = 0.0f;
		m_rotation.z = 0.0f;

		m_doUpdate 	 = false;
	}
};


//--------------------------------------------------------------------------------------
// Bundes all user input required to control the editor except for the camera (latter one 
// stored in CameraInput struct).
//--------------------------------------------------------------------------------------
struct EditorInput
{
	EditorInput() : m_changeColour( 0 ), 
					m_changeBrick( 0 ), 
					m_changeEditLevel( 0 ), 
					m_changeBrickRotation( 0 ), 
					m_changeShaderGroup( 0 ),
					m_doAction( false ), 
					m_doToggleDeletionMode( false ), 
					m_doToggleRecordingMode( false ),
					m_doTogglePresentationMode( false ),
					m_doSave( false ), 
					m_doLoad( false ), 
					m_doQuit( false )
	{}
	
	int	 m_changeColour;			// switch to the colour these many steps from the current one
	int  m_changeBrick;				// switch to the brick type or custom structure these many steps from the current one
	int  m_changeEditLevel;			// change the edit level of the editor by these many steps (move the grid up or down)
	int  m_changeBrickRotation;		// the rotation that will be applied to bricks (int because only a few values allowed, only rotations by 90 degrees)
	int  m_changeShaderGroup;		// switch to the shader group this many steps from the currently selected one

	bool m_doAction;				// depending on the current mode, execute a user action (add or delete a brick at cursor position)
	bool m_doToggleDeletionMode;	// is the deletion mode activated
	bool m_doToggleRecordingMode;	// is the recording mode activated
	bool m_doTogglePresentationMode;// is the presentation mode activated

	bool m_doSave;					// if true, save the game
	bool m_doLoad;					// if true, load a lego world
	bool m_doQuit;					// exit the application

	//--------------------------------------------------------------------------------------
	// Resets the editor input for the next frame.
	//--------------------------------------------------------------------------------------
	void Reset( void )
	{
		m_changeColour        = 0;			
		m_changeBrick         = 0;						
		m_changeEditLevel	  = 0;					
		m_changeBrickRotation = 0;			
		m_changeShaderGroup   = 0;

		m_doAction				   = false;				
		m_doToggleDeletionMode     = false;			
		m_doToggleRecordingMode	   = false;	
		m_doTogglePresentationMode = false;

		m_doSave = false;			
		m_doLoad = false;			
		m_doQuit = false;			
	}
};

#endif