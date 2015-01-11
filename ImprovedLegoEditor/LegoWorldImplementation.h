/* 
*  Kevin Meergans, Improved Lego Editor, 2014
*  LegoWorldImplementation.h
*  Implementation part of the LegoWorld class.The public interface of this class
*  and the one of the LegoWorld class have to be kept consistent.
*/

#ifndef LEGO_WORLD_IMPLEMENTATION_H
#define LEGO_WORLD_IMPLEMENTATION_H

#include <windows.h>
#include <memory>
#include <vector>
#include "LegoBrickData.h"
#include "EditorDataStructures.h"
#include "Helpers.h"
#include <algorithm>
#include <fstream>
#include <string>
#include <sstream>
#include "RenderContext.h"
#include "LegoWorldNode.h"

class LegoWorldImplementation
{
public:

	LegoWorldImplementation( void );

	HRESULT Initialise();
	bool	AddLegoBrick( int type, const IntVector3& gridPosition, int rotation, LegoBrickColour colour );
	bool	AddLegoStructure( unsigned int type, const IntVector3& gridPosition, int rotation );
	bool	RemoveLegoBrick( const IntVector3& gridPosition );
	HRESULT Cleanup();

	void	Update( RenderContext* pRenderContext, const XMFLOAT4 frustumPlanes[6] );

	bool	Save( std::string filename );
	bool	Load( std::string filename );

	void	StartRecording();
	bool	StopRecording( bool doSave, std::string name);

	void	GetExtentsOfStructure( int index, IntVector3* pDestination );
	int		GetNumberOfCustomStructures( void ) const;

	const std::string& GetCustomStructureName( int type ) const;
	int		GetNumberOfBricks( void ) const;
	int		GetNumberOfStuds( void ) const;

private:

	bool	CheckSpace( const IntVector3& gridPosition, const IntVector3& brickExtents );
	void	GetBrickExtentsOnGrid( const IntVector3& brickExtents, const IntVector3& brickPosition, int rotation, IntVector3& outBrickExtentsOnGrid, IntVector3& outBrickPositionOnGrid );

	bool	SaveCustomStructures( std::string filename );
	bool	LoadCustomStructures( std::string filename );

	bool	AddStud( int gridX, int gridY, int gridZ, int brickHeight, LegoBrickColour colour );
	bool	RemoveStud( int gridX, int gridY, int gridZ, int brickHeight );

	static unsigned int m_Id;										// used to assign IDs to placed lego bricks

	unsigned int m_idMatrix[GRID_SIZE_X][GRID_SIZE_Y][GRID_SIZE_Z];	// Keeps track of which bricks are placed where on the grid, 
																	// necessary for brick removal and avoidance of intersecting bricks

	bool		 m_doRecord;										// Determines whether placed bricks will be recorded to from a custom structure or not

	LegoWorldNode m_legoWorldTree;		// root of the octree representing the world and holding all the bricks

	int			m_numberOfBricks;									// keep track of number of bricks in the scene
	int		    m_numberOfStuds;

	//std::vector<LegoBrick> m_legoBricks;							// Stores all bricks currently placed in the world
	std::vector<LegoBrick> m_recordedLegoBricks;					// Temporarily stores the bricks placed while recording mode is active
	std::vector<LegoStructure> m_legoStructures;					// User-defined structures consisting of single bricks
};

#endif