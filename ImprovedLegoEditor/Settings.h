/* 
*  Kevin Meergans, Improved Lego Editor, 2014
*  Settings.h
*  A collection of constant values used by different components of the application.
*  Although not adhering to encapsulation, I decided to put all these constants in
*  one place to allow for a more convenient tweaking of application settings.
*/

#ifndef SETTINGS_H
#define SETTINGS_H

#include <windows.h>
#include <xnamath.h>
#include <d3d10.h>
#include <d3dx10.h>
#include <string>
#include "CommonDataStructures.h"


const float NEAR_CLIPPING_PLANE		= 1.0f;		// near clipping plane of the editor camera
const float FAR_CLIPPING_PLANE		= 4000.0f;	// far clipping plane of the editor camera
const float FIELD_OF_VIEW			= XM_PI/4;  // field of view of the editor camera

const D3DXCOLOR BACKGROUND_COLOUR( 0.0f, 0.0f, 0.0f, 1.0f );	// the background of the scene is coloured in this colour
const XMFLOAT3 CAMERA_MOVEMENT_SPEED( 0.1f, 0.1f, 0.1f );		// determines how fast the camera moves along each axis for a given user input
																// (horizontal pan speed, vertical pan speed, zoom speed)
const XMFLOAT3 CAMERA_ROTATION_SPEED( 0.1f, 0.1f, 0.1f );		// determines how much the camera rotates along each axis for a given user input
																// (pitch speed, yaw speed, roll speed)
const XMFLOAT3 GRID_UNIT( 8.0f, 3.2f, 8.0f );

const int GRID_SIZE_X = 256;	// not possible as IntVector3 because the values are used to initialise the m_idMatrix array in the 
								// LegoWorldImplementation class and a constant expression is necessary for that (using IntVector3 did not work)
const int GRID_SIZE_Y = 128; 
const int GRID_SIZE_Z = 256;

const IntVector3 GRID_HALF_SIZE( GRID_SIZE_X / 2, GRID_SIZE_Y / 2, GRID_SIZE_Z / 2 );
const IntVector3 MIN_GRID_POS( -GRID_SIZE_X / 2, -GRID_SIZE_Y / 2, -GRID_SIZE_Z / 2 );

// This is limited to make sure studs are still encompassed in the octree, todo: find other solution
const IntVector3 MAX_GRID_POS( GRID_SIZE_X / 2, GRID_SIZE_Y / 2 - 1, GRID_SIZE_Z / 2 );

const XMFLOAT3 DIRECTIONAL_LIGHT_DIRECTION( 1.0f, -0.3f, 1.0f );
const XMFLOAT4 DIRECTIONAL_LIGHT_COLOUR( 1.0f, 1.0f, 1.0f, 1.0f );

const std::string CUSTOM_STRUCTURES_FILENAME( "CustomLegoStructures.txt" );

const XMFLOAT4 GRID_COLOUR( 0.0f, 0.0f, 1.0f, 1.0f );	        // determines the colour of the editor grid (r,g,b,a)
const XMFLOAT4 CURSOR_COLOUR( 1.0f, 1.0f, 0.0f, 1.0f );	        // determines the colour of the editor cursor (r,g,b,a)
const XMFLOAT4 CURSOR_DELETE_COLOUR( 1.0f, 0.0f, 0.0f, 1.0f );	// determines the colour of the editor cursor when in deletion mode (r,g,b,a)
const XMFLOAT4 EDGE_COLOUR( 0.0f, 0.0f, 0.0f, 1.0f );			// determines colour of edges when using a toon shader

// todo: make this an array with a distinct value for every type (more bricks for smaller ones etc)
const int NUMBER_OF_BRICKS_PER_TYPE( 20000 ); 
const int NUMBER_OF_STUDS( 100000 ); 


const int MAX_TREE_LEVEL(2);       // The octree representing the lego world will have this depth at max (root is level 0)

const int MAX_SENTENCE_LENGTH(25); // a sentence structure used to display text on the screen can have as many characters as this figure says

#endif