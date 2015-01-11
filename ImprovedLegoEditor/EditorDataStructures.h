/* 
*  Kevin Meergans, Improved Lego Editor, 2014
*  EditorDataStructures.h
*  Contains data structures used by the editor and shared with the renderer.
*/

#ifndef EDITOR_DATA_STRUCTURES_H
#define EDITOR_DATA_STRUCTURES_H

#include <windows.h>
#include <xnamath.h>
#include "LegoBrickData.h"
#include "CommonDataStructures.h"
#include <string>
#include "ShaderDataStructures.h"

//--------------------------------------------------------------------------------------
// Contains the current editor state
//--------------------------------------------------------------------------------------
struct EditorData
{
	EditorData::EditorData() : m_cursorPosition( 0, 0, 0 ), 
							   m_brickRotation( 0 ), 
							   m_cursorExtents( 1, 1, 1 ),
							   m_numberOfCustomStructures( 0 ),
							   m_selectedBuildingBlock( 0 ), 
							   m_customStructureName( "" ),
							   m_selectedBrickColour( Black ), 
							   m_isRecordingModeActive( false ), 
							   m_isDeletionModeActive( false ),
							   m_isPresentationModeActive( false ),
							   m_selectedShaderGroup( GroupSimple )
	{}

	// todo: split up in two parts: one to be shared with renderer and one with stuff only needed by editor

	IntVector3		m_cursorPosition;		 // Bricks will be placed at this grid position (also position of the cursor)
	int				m_brickRotation;		 // Rotation that will be applied to bricks about to be placed (equals cursor rotation),
											 // int because only values for which (rotation % 90 == 0) allowed/possible

	IntVector3		m_cursorExtents;

	int				m_numberOfCustomStructures;

	int				m_selectedBuildingBlock; // The currently selected brick type or structure
	const char*		m_customStructureName; 
	LegoBrickColour m_selectedBrickColour;	 // The currently selected brick colour

	bool			m_isRecordingModeActive; // Are bricks currently being recorded?
	bool			m_isDeletionModeActive;  // Is the editor in creation or deletion mode?
	bool			m_isPresentationModeActive; // Is the application in presentation mode?

	ShaderGroups    m_selectedShaderGroup;   // Determines what shader is used to render the bricks
};




#endif