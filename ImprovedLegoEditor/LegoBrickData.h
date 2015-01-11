/* 
*  Kevin Meergans, Improved Lego Editor, 2014
*  LegoWorldDataStructures.h
*  Contains data structures describing lego bricks and their properties as well as static
*  functions providing convenient access to properties of the bricks, such as colour and scale.
*/

#ifndef LEGO_BRICK_DATA_H
#define LEGO_BRICK_DATA_H

#include <windows.h>
#include <xnamath.h>
#include <string>
#include <vector>
#include "Settings.h"
#include "CommonDataStructures.h"

// todo: add custom structures?
//--------------------------------------------------------------------------------------
// Holds a value for each basic brick type included in the application.
// Std -> Standard brick
// width x height x length (width and length in number of knobs, height in "lego plate heights"; normal brick is three times as high as a plate)
//--------------------------------------------------------------------------------------
enum LegoBrickType
{
	Std1x1x1, Std1x3x1, Std1x1x2, Std1x3x2, Std2x1x2, Std2x3x2, Std1x1x3, Std1x3x3, Std2x1x3, Std2x3x3, Std1x1x4, Std1x3x4,  
	Std2x1x4, Std2x3x4, Std4x1x4, Std1x1x6, Std1x3x6, Std2x1x6, Std2x3x6, Std4x1x6, Std1x1x8, Std1x3x8, Std2x1x8, Std2x3x8,  
	Std1x1x10, Std1x3x10, Std2x1x10, Std2x3x10, Std4x1x10, NumberOfBrickTypes
};

//--------------------------------------------------------------------------------------
// Holds a value for each colour available for the lego bricks
//--------------------------------------------------------------------------------------
enum LegoBrickColour
{
	Black, DarkGrey, DarkerGrey, Grey, LighterGrey, LightGrey, 
	DarkBrown, Brown, Sienna, SaddleBrown, Brick, LightBrown, BurlyWood,
	DarkGreen, ForestGreen, Green, DarkOliveGreen, Olive, YellowGreen, LightGreen, 
	DarkBlue, Blue, DodgerBlue, Teal, Cyan, LightBlue, 
	Indigo, Purple, Magenta, Pink,
	DarkRed, Red, LightRed,
	OrangeRed, Orange, DarkGoldenRod, GoldenRod, Yellow, Khaki, White, NumberOfColours
};

//--------------------------------------------------------------------------------------
// Representation of a lego brick
//--------------------------------------------------------------------------------------
struct LegoBrick
{
	LegoBrick::LegoBrick( unsigned int id, LegoBrickType type, LegoBrickColour colour, const IntVector3& position, int rotation, const XMFLOAT4X4& transformMatrix) : 
																															m_id( id ), 
																															m_type( type ), 
																															m_colour( colour ),
																															m_position( position ),
																															m_rotation( rotation ),
																															m_transform( transformMatrix )
	{}

	unsigned int	m_id;			// unique identifier for this brick
	LegoBrickType	m_type;			// denotes the type of lego brick
	LegoBrickColour m_colour;		// identifies the colour of this brick
	IntVector3		m_position;		// the position of the brick in grid units
	int				m_rotation;		// the rotation of the brick


	XMFLOAT4X4		m_transform;	// transform matrix to be applied upon rendering (includes position, rotation, scale)

};

//--------------------------------------------------------------------------------------
// Representation of a lego stud
//--------------------------------------------------------------------------------------
struct LegoStud
{
	LegoStud::LegoStud( LegoBrickColour colour, const IntVector3& position, const XMFLOAT4X4& transformMatrix) : 
																															m_colour( colour ),
																															m_position( position ),
																															m_transform( transformMatrix )
	{}

	LegoBrickColour m_colour;		// identifies the colour of this stud
	IntVector3		m_position;		// the position of the stud in grid units

	XMFLOAT4X4		m_transform;	// transform matrix to be applied upon rendering (includes position, rotation, scale)
};

//--------------------------------------------------------------------------------------
// All the data required for bricks stored as a custom lego structure
//--------------------------------------------------------------------------------------
struct BasicBrickData
{
	BasicBrickData::BasicBrickData( LegoBrickType type, LegoBrickColour colour, const IntVector3& position, int rotation) : m_type( type ), 
																															m_colour( colour ),
																															m_position( position ),
																															m_rotation( rotation )
	{}

	LegoBrickType	m_type;			// denotes the type of lego brick
	LegoBrickColour m_colour;		// identifies the colour of this brick
	IntVector3		m_position;		// the position of the brick in grid units
	int				m_rotation;		// the rotation of the brick
};

//--------------------------------------------------------------------------------------
// Representation of a lego structure consisting of single bricks
//--------------------------------------------------------------------------------------
struct LegoStructure
{
	LegoStructure(){}
	LegoStructure(const std::string& name, const IntVector3& extents, const std::vector<BasicBrickData>& bricks) : m_name( name ),
																												   m_extents( extents ),
																											       m_bricks( bricks )
	{}

	std::string m_name;							// the name identifying the structure
	IntVector3 m_extents;						// the maximal extents of the structure on each axis (used to display the cursor accordingly)
	std::vector<BasicBrickData> m_bricks;		// the bricks this structure consists of
};



//--------------------------------------------------------------------------------------
// The colour values for the available bricks colours ( r, g, b, a ), use LegoBrickColour enum value as index
//--------------------------------------------------------------------------------------
static const XMFLOAT4 BrickColours[NumberOfColours] = 
{
	XMFLOAT4( 0.05f, 0.05f, 0.05f, 1.0f ),	// Black 
	XMFLOAT4( 0.2f, 0.2f, 0.2f, 1.0f ),		// DarkGrey 
	XMFLOAT4( 0.35f, 0.35f, 0.35f, 1.0f ),	// DarkerGrey 
	XMFLOAT4( 0.5f, 0.5f, 0.5f, 1.0f ),		// Grey
	XMFLOAT4( 0.65f, 0.65f, 0.65f, 1.0f ),  // LighterGrey
	XMFLOAT4( 0.8f, 0.8f, 0.8f, 1.0f ),		// LightGrey
	
	XMFLOAT4( 0.2f, 0.1f, 0.0f, 1.0f ),		// DarkBrown
	XMFLOAT4( 0.4f, 0.2f, 0.1f, 1.0f ),		// Brown
	XMFLOAT4( 0.54f, 0.27f, 0.15f, 1.0f ),	// Sienna
	XMFLOAT4( 0.54f, 0.27f, 0.07f, 1.0f ),	// SaddleBrown
	XMFLOAT4( 0.61f, 0.4f, 0.12f, 1.0f ),	// Brick
	XMFLOAT4( 0.95f, 0.64f, 0.37f, 1.0f ),	// LightBrown
	XMFLOAT4( 0.87f, 0.72f, 0.53f, 1.0f ),	// BurlyWood

	XMFLOAT4( 0.0f, 0.3f, 0.0f, 1.0f ),		// DarkGreen
	XMFLOAT4( 0.13f, 0.55f, 0.13f, 1.0f ),	// ForestGreen
	XMFLOAT4( 0.0f, 1.0f, 0.0f, 1.0f ),		// Green
	XMFLOAT4( 0.33f, 0.42f, 0.18f, 1.0f ),	// DarkOliveGreen
	XMFLOAT4( 0.5f, 0.5f, 0.0f, 1.0f ),		// Olive
	XMFLOAT4( 0.67f, 1.0f, 0.18f, 1.0f ),	// YellowGreen
	XMFLOAT4( 0.56f, 1.0f, 0.56f, 1.0f ),	// LightGreen
	
	XMFLOAT4( 0.0f, 0.0f, 0.5f, 1.0f ),		// DarkBlue
	XMFLOAT4( 0.0f, 0.0f, 1.0f, 1.0f ),		// Blue
	XMFLOAT4( 0.12f, 0.56f, 1.0f, 1.0f ),	// DodgerBlue
	XMFLOAT4( 0.0f, 0.5f, 0.5f, 1.0f ),		// Teal
	XMFLOAT4( 0.0f, 1.0f, 1.0f, 1.0f ),		// Cyan
	XMFLOAT4( 0.67f, 0.85f, 0.9f, 1.0f ),	// LightBlue 

	XMFLOAT4( 0.29f, 0.0f, 0.5f, 1.0f ),	// Indigo
	XMFLOAT4( 0.5f, 0.0f, 0.5f, 1.0f ),		// Purple
	XMFLOAT4( 1.0f, 0.0f, 1.0f, 1.0f ),		// Magenta
	XMFLOAT4( 1.0f, 0.75f, 0.79f, 1.0f ),	// Pink

	XMFLOAT4( 0.5f, 0.0f, 0.0f, 1.0f ),		// DarkRed
	XMFLOAT4( 1.0f, 0.0f, 0.0f, 1.0f ),		// Red
	XMFLOAT4( 1.0f, 0.5f, 0.5f, 1.0f ),		// LightRed
	
	XMFLOAT4( 1.0f, 0.27f, 0.0f, 1.0f ),	// OrangeRed
	XMFLOAT4( 1.0f, 0.5f, 0.0f, 1.0f ),		// Orange
	XMFLOAT4( 0.72f, 0.52f, 0.04f, 1.0f ),	// DarkGoldenRod
	XMFLOAT4( 0.85f, 0.65f, 0.12f, 1.0f ),	// GoldenRod
	XMFLOAT4( 1.0f, 1.0f, 0.0f, 1.0f ),		// Yellow
	XMFLOAT4( 0.94f, 0.9f, 0.55f, 1.0f ),	// Khaki

	XMFLOAT4( 1.0f, 1.0f, 1.0f, 1.0f )		// White
};


//--------------------------------------------------------------------------------------
// The names of the available brick colours, use LegoBrickColour enum value as index
//--------------------------------------------------------------------------------------
static const std::string BrickColourNames[NumberOfColours] = 
{
	"Black", "DarkGrey", "DarkerGrey", "Grey", "LighterGrey", "LightGrey", 
	"DarkBrown", "Brown", "Sienna", "SaddleBrown", "Brick", "LightBrown", "BurlyWood",
	"DarkGreen", "ForestGreen", "Green", "DarkOliveGreen", "Olive", "YellowGreen", "LightGreen", 
	"DarkBlue", "Blue", "DodgerBlue", "Teal", "Cyan", "LightBlue", 
	"Indigo", "Purple", "Magenta", "Pink",
	"DarkRed", "Red", "LightRed",
	"OrangeRed", "Orange", "DarkGoldenRod", "GoldenRod", "Yellow", "Khaki", "White"
};


//--------------------------------------------------------------------------------------
// The names of the brick types, use LegoBrickType enum values as index into this array
//--------------------------------------------------------------------------------------
static const std::string BrickTypeNames[NumberOfBrickTypes] =
{
	"Std1x1x1", "Std1x3x1", "Std1x3x2", "Std1x1x2", "Std2x1x2", "Std2x3x2", "Std1x1x3", "Std1x3x3", 
	"Std2x1x3", "Std2x3x3", "Std1x1x4", "Std1x3x4", "Std2x1x4", "Std2x3x4", "Std4x1x4", "Std1x1x6", 
	"Std1x3x6", "Std2x1x6", "Std2x3x6", "Std4x1x6", "Std1x1x8", "Std1x3x8", "Std2x1x8", "Std2x3x8",  
	"Std1x1x10", "Std1x3x10", "Std2x1x10", "Std2x3x10", "Std4x1x10"
};


//--------------------------------------------------------------------------------------
// The actual size of the different brick types, use LegoBrickType enum values as index into this array
//--------------------------------------------------------------------------------------
static const XMFLOAT3 BrickSizes[NumberOfBrickTypes] = 
{ 
	XMFLOAT3( 1.0f * GRID_UNIT.x, 1.0f * GRID_UNIT.y, 1.0f * GRID_UNIT.z ),
	XMFLOAT3( 1.0f * GRID_UNIT.x, 3.0f * GRID_UNIT.y, 1.0f * GRID_UNIT.z ), 
	XMFLOAT3( 1.0f * GRID_UNIT.x, 1.0f * GRID_UNIT.y, 2.0f * GRID_UNIT.z ),
	XMFLOAT3( 1.0f * GRID_UNIT.x, 3.0f * GRID_UNIT.y, 2.0f * GRID_UNIT.z ),
	XMFLOAT3( 2.0f * GRID_UNIT.x, 1.0f * GRID_UNIT.y, 2.0f * GRID_UNIT.z ),
	XMFLOAT3( 2.0f * GRID_UNIT.x, 3.0f * GRID_UNIT.y, 2.0f * GRID_UNIT.z ),
	XMFLOAT3( 1.0f * GRID_UNIT.x, 1.0f * GRID_UNIT.y, 3.0f * GRID_UNIT.z ),
	XMFLOAT3( 1.0f * GRID_UNIT.x, 3.0f * GRID_UNIT.y, 3.0f * GRID_UNIT.z ),
	XMFLOAT3( 2.0f * GRID_UNIT.x, 1.0f * GRID_UNIT.y, 3.0f * GRID_UNIT.z ),
	XMFLOAT3( 2.0f * GRID_UNIT.x, 3.0f * GRID_UNIT.y, 3.0f * GRID_UNIT.z ),
	XMFLOAT3( 1.0f * GRID_UNIT.x, 1.0f * GRID_UNIT.y, 4.0f * GRID_UNIT.z ),
	XMFLOAT3( 1.0f * GRID_UNIT.x, 3.0f * GRID_UNIT.y, 4.0f * GRID_UNIT.z ),
	XMFLOAT3( 2.0f * GRID_UNIT.x, 1.0f * GRID_UNIT.y, 4.0f * GRID_UNIT.z ),
	XMFLOAT3( 2.0f * GRID_UNIT.x, 3.0f * GRID_UNIT.y, 4.0f * GRID_UNIT.z ),
	XMFLOAT3( 4.0f * GRID_UNIT.x, 1.0f * GRID_UNIT.y, 4.0f * GRID_UNIT.z ),
	XMFLOAT3( 1.0f * GRID_UNIT.x, 1.0f * GRID_UNIT.y, 6.0f * GRID_UNIT.z ),
	XMFLOAT3( 1.0f * GRID_UNIT.x, 3.0f * GRID_UNIT.y, 6.0f * GRID_UNIT.z ),
	XMFLOAT3( 2.0f * GRID_UNIT.x, 1.0f * GRID_UNIT.y, 6.0f * GRID_UNIT.z ),
	XMFLOAT3( 2.0f * GRID_UNIT.x, 3.0f * GRID_UNIT.y, 6.0f * GRID_UNIT.z ),
	XMFLOAT3( 4.0f * GRID_UNIT.x, 1.0f * GRID_UNIT.y, 6.0f * GRID_UNIT.z ),
	XMFLOAT3( 1.0f * GRID_UNIT.x, 1.0f * GRID_UNIT.y, 8.0f * GRID_UNIT.z ),
	XMFLOAT3( 1.0f * GRID_UNIT.x, 3.0f * GRID_UNIT.y, 8.0f * GRID_UNIT.z ),
	XMFLOAT3( 2.0f * GRID_UNIT.x, 1.0f * GRID_UNIT.y, 8.0f * GRID_UNIT.z ),
	XMFLOAT3( 2.0f * GRID_UNIT.x, 3.0f * GRID_UNIT.y, 8.0f * GRID_UNIT.z ),
	XMFLOAT3( 1.0f * GRID_UNIT.x, 1.0f * GRID_UNIT.y, 10.0f * GRID_UNIT.z ),
	XMFLOAT3( 1.0f * GRID_UNIT.x, 3.0f * GRID_UNIT.y, 10.0f * GRID_UNIT.z ),
	XMFLOAT3( 2.0f * GRID_UNIT.x, 1.0f * GRID_UNIT.y, 10.0f * GRID_UNIT.z ),
	XMFLOAT3( 2.0f * GRID_UNIT.x, 3.0f * GRID_UNIT.y, 10.0f * GRID_UNIT.z ),
	XMFLOAT3( 4.0f * GRID_UNIT.x, 1.0f * GRID_UNIT.y, 10.0f * GRID_UNIT.z )
};

//--------------------------------------------------------------------------------------
// The size of the bricks measured in brick units, use LegoBrickType enum values as index
//--------------------------------------------------------------------------------------
static const IntVector3 BrickSizesInUnits[NumberOfBrickTypes] = 
{ 
	IntVector3( 1, 1, 1 ),
	IntVector3( 1, 3, 1 ), 
	IntVector3( 1, 1, 2 ),
	IntVector3( 1, 3, 2 ),
	IntVector3( 2, 1, 2 ),
	IntVector3( 2, 3, 2 ),
	IntVector3( 1, 1, 3 ),
	IntVector3( 1, 3, 3 ),
	IntVector3( 2, 1, 3 ),
	IntVector3( 2, 3, 3 ),
	IntVector3( 1, 1, 4 ),
	IntVector3( 1, 3, 4 ),
	IntVector3( 2, 1, 4 ),
	IntVector3( 2, 3, 4 ),
	IntVector3( 4, 1, 4 ),
	IntVector3( 1, 1, 6 ),
	IntVector3( 1, 3, 6 ),
	IntVector3( 2, 1, 6 ),
	IntVector3( 2, 3, 6 ),
	IntVector3( 4, 1, 6 ),
	IntVector3( 1, 1, 8 ),
	IntVector3( 1, 3, 8 ),
	IntVector3( 2, 1, 8 ),
	IntVector3( 2, 3, 8 ),
	IntVector3( 1, 1, 10 ),
	IntVector3( 1, 3, 10 ),
	IntVector3( 2, 1, 10 ),
	IntVector3( 2, 3, 10 ),
	IntVector3( 4, 1, 10 )
};



#endif