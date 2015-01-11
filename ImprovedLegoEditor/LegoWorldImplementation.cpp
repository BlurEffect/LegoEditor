/* 
*  Kevin Meergans, Improved Lego Editor, 2014
*  LegoWorldImplementation.cpp
*  Contains the function definitions for the LegoWorldImplementation class.
*/

# include "LegoWorldImplementation.h"

// intialise ID variable, bricks are assigned values starting from 1
unsigned int LegoWorldImplementation::m_Id( 0 );

LegoWorldImplementation::LegoWorldImplementation() : m_doRecord( false ), 
													 m_legoWorldTree( IntVector3( 0,0,0 ), IntVector3( GRID_SIZE_X, GRID_SIZE_Y, GRID_SIZE_Z ), 0 ),
													 m_numberOfBricks( 0 ),
													 m_numberOfStuds( 0 )
{
}

//--------------------------------------------------------------------------------------
// Initialise the lego world
//--------------------------------------------------------------------------------------
HRESULT LegoWorldImplementation::Initialise()
{
	// initialise the idMatrix to all zeros
	ZeroMemory( &m_idMatrix, GRID_SIZE_X * GRID_SIZE_Y * GRID_SIZE_Z * sizeof( unsigned int ) );

	// Load the custom structures from a file
	if( LoadCustomStructures( CUSTOM_STRUCTURES_FILENAME ) )
	{
		return S_OK;
	}else
	{
		return E_FAIL;
	}
}

//--------------------------------------------------------------------------------------
// Check if there is enough space in the world for the brcik to be added (check if the space
// is already occupied by other bricks)
//--------------------------------------------------------------------------------------
bool LegoWorldImplementation::CheckSpace( const IntVector3& gridPosition, const IntVector3& brickExtents )
{
	// check brick against the world/grid bounds
	if( ( gridPosition.m_x + brickExtents.m_x <= MAX_GRID_POS.m_x && gridPosition.m_x >= MIN_GRID_POS.m_x ) && 
		( gridPosition.m_y + brickExtents.m_y <= MAX_GRID_POS.m_y && gridPosition.m_y >= MIN_GRID_POS.m_y ) &&
		( gridPosition.m_z + brickExtents.m_z <= MAX_GRID_POS.m_z && gridPosition.m_z >= MIN_GRID_POS.m_z ) )
	{
		
		for( int i = gridPosition.m_x + GRID_HALF_SIZE.m_x; i < gridPosition.m_x + GRID_HALF_SIZE.m_x + brickExtents.m_x; ++i )
		{
			for( int j = gridPosition.m_y + GRID_HALF_SIZE.m_y; j < gridPosition.m_y + GRID_HALF_SIZE.m_y + brickExtents.m_y; ++j )
			{
				for( int k = gridPosition.m_z + GRID_HALF_SIZE.m_z; k < gridPosition.m_z + GRID_HALF_SIZE.m_z + brickExtents.m_z; ++k )
				{
					if(m_idMatrix[i][j][k] != 0)
					{
						// place already occupied by another brick
						return false;	
					}
				}
			}
		}

		// there is enough free space for the brick to be placed
		return true;
	}

	// parts of the brick were placed outside of the grid
	return false;
}

//--------------------------------------------------------------------------------------
// Add a brick to the lego world
//--------------------------------------------------------------------------------------
bool LegoWorldImplementation::AddLegoBrick( int type, const IntVector3& gridPosition, int rotation, LegoBrickColour colour )
{
	IntVector3 extentsOnGrid; 
	IntVector3 positionOnGrid;

	// Given the current rotation of the brick, get the actual brick extents in grid space
	GetBrickExtentsOnGrid( BrickSizesInUnits[type], gridPosition, rotation, extentsOnGrid, positionOnGrid );

	// make sure the brick is placed within the grid bounds and that the brick is not intersecting others
	if( CheckSpace( positionOnGrid, extentsOnGrid ) )
	{

		// also get new grid pos

		// create transformation matrix for the brick
		XMFLOAT4X4 matTransform;
		XMStoreFloat4x4( &matTransform, XMMatrixRotationAxis( XMVectorSet( 0.0f, 1.0f, 0.0f, 0.0f ), XMConvertToRadians( static_cast<float>( rotation ) ) ) * 
				XMMatrixTranslation( gridPosition.m_x * GRID_UNIT.x + GRID_UNIT.x * 0.5f, gridPosition.m_y * GRID_UNIT.y, gridPosition.m_z * GRID_UNIT.z + GRID_UNIT.z * 0.5f ) );

		//XMVECTOR deter;
		//XMStoreFloat4x4( &matTransform, XMMatrixInverse( &deter, XMLoadFloat4x4(&matTransform)));

		// create new brick and add it to the brick vector
		LegoBrick brick( ++m_Id, LegoBrickType(type), colour, gridPosition, rotation, matTransform);

		//m_legoBricks.push_back(brick);
		m_legoWorldTree.AddBrick( brick, positionOnGrid, extentsOnGrid );
		++m_numberOfBricks;

		if( m_doRecord )
		{
			m_recordedLegoBricks.push_back(brick);
		}

		// todo: possible to get rid of redundancy? Looping identical to CheckSpace

		// update the id matrix -> indicate that the position is now occupied by the new brick
		
		for( int i = positionOnGrid.m_x + GRID_HALF_SIZE.m_x ; i < positionOnGrid.m_x + GRID_HALF_SIZE.m_x + extentsOnGrid.m_x; ++i )
		{
			for( int j = positionOnGrid.m_y + GRID_HALF_SIZE.m_y; j < positionOnGrid.m_y + GRID_HALF_SIZE.m_y + extentsOnGrid.m_y; ++j )
			{
				for( int k = positionOnGrid.m_z + GRID_HALF_SIZE.m_z ; k < positionOnGrid.m_z + GRID_HALF_SIZE.m_z + extentsOnGrid.m_z; ++k )
				{
					m_idMatrix[i][j][k] = brick.m_id;
				}
			}
		}

		// Add studs
		for( int i = positionOnGrid.m_x + GRID_HALF_SIZE.m_x ; i < positionOnGrid.m_x + GRID_HALF_SIZE.m_x + extentsOnGrid.m_x; ++i )
		{
			for( int j = positionOnGrid.m_z + GRID_HALF_SIZE.m_z ; j < positionOnGrid.m_z + GRID_HALF_SIZE.m_z + extentsOnGrid.m_z; ++j )
			{
				AddStud( i - GRID_HALF_SIZE.m_x, positionOnGrid.m_y, j - GRID_HALF_SIZE.m_z, extentsOnGrid.m_y, colour );
			}
		}

		return true;
	}else
	{
		// not enough space available
		return false;
	}
}

//--------------------------------------------------------------------------------------
// Adds a stud at the grid position determined by the parameters. Returns true if the 
// stud was successfully added, false otherwise.
//--------------------------------------------------------------------------------------
bool LegoWorldImplementation::AddStud( int gridX, int gridY, int gridZ, int brickHeight, LegoBrickColour colour )
{
	bool result = false;

	// Add a new stud if there is no brick occupying the grid position one step above the given position
	if( m_idMatrix[gridX + GRID_HALF_SIZE.m_x][gridY + brickHeight + GRID_HALF_SIZE.m_y][gridZ + GRID_HALF_SIZE.m_z] == 0)
	{
		XMFLOAT4X4 matTransform;
		XMStoreFloat4x4( &matTransform, XMMatrixTranslation( gridX * GRID_UNIT.x + GRID_UNIT.x * 0.5f, (gridY + brickHeight) * GRID_UNIT.y, gridZ * GRID_UNIT.z + GRID_UNIT.z * 0.5f ) );

		LegoStud newStud( colour, IntVector3( gridX, gridY + brickHeight, gridZ ), matTransform );

		result = m_legoWorldTree.AddStud( newStud, IntVector3( gridX, gridY + brickHeight, gridZ ) );
		++m_numberOfStuds;
	}

	// Remove an existing stud at the given x,z coordinates if the brick (for which the new stud was addded) is sitting just
	// on top of it
	if( gridY > MIN_GRID_POS.m_y )
	{
		if( m_idMatrix[gridX + GRID_HALF_SIZE.m_x][gridY + GRID_HALF_SIZE.m_y - 1][gridZ + GRID_HALF_SIZE.m_z] != 0 )
		{
			m_legoWorldTree.RemoveStud( IntVector3( gridX, gridY, gridZ ) );
			--m_numberOfStuds;
		}else
		{
			//++m_numberOfStuds;
		}
	}

	return result;

}

//--------------------------------------------------------------------------------------
// Removes a stud at the grid position determined by the parameters. Returns true if the 
// stud was successfully deleted, false otherwise.
//--------------------------------------------------------------------------------------
bool LegoWorldImplementation::RemoveStud( int gridX, int gridY, int gridZ, int brickHeight )
{
	bool result = false;
	
	// Remove the stud if there is no other brick sitting on top of this one 
	if( m_idMatrix[gridX + GRID_HALF_SIZE.m_x][gridY + brickHeight + GRID_HALF_SIZE.m_y][gridZ + GRID_HALF_SIZE.m_z] == 0)
	{
		result = m_legoWorldTree.RemoveStud( IntVector3( gridX, gridY + brickHeight, gridZ ) );
		--m_numberOfStuds;
	}

	// Add a new stud if the brick was placed on top of another one
	if( gridY > MIN_GRID_POS.m_y )
	{
		if( m_idMatrix[gridX + GRID_HALF_SIZE.m_x][gridY + GRID_HALF_SIZE.m_y - 1][gridZ + GRID_HALF_SIZE.m_z] != 0 )
		{
			XMFLOAT4X4 matTransform;
			XMStoreFloat4x4( &matTransform, XMMatrixTranslation( gridX * GRID_UNIT.x + GRID_UNIT.x * 0.5f, (gridY) * GRID_UNIT.y, gridZ * GRID_UNIT.z + GRID_UNIT.z * 0.5f ) );

			// get the colour of the brick that was below -> colour the stud in that colour
			LegoStud newStud( m_legoWorldTree.GetLegoBrick( m_idMatrix[gridX + GRID_HALF_SIZE.m_x][gridY + GRID_HALF_SIZE.m_y - 1][gridZ + GRID_HALF_SIZE.m_z] ) -> m_colour, IntVector3( gridX, gridY, gridZ ), matTransform );

			m_legoWorldTree.AddStud( newStud, IntVector3( gridX, gridY, gridZ ) );
			++m_numberOfStuds;
		}else
		{
			//++m_numberOfStuds;
		}
	}

	return result;

}

// todo: remove redundancoes of AddBrick and AddLegoStructure -> Have AddStructure call Addbrick?

//--------------------------------------------------------------------------------------
// Add the bricks encompassed in a structure to the scene.
//--------------------------------------------------------------------------------------
bool LegoWorldImplementation::AddLegoStructure( unsigned int type, const IntVector3& gridPosition, int rotation )
{
	if( type >= m_legoStructures.size() )
	{
		return false;
	}

	IntVector3  absolutePosition( 0, 0, 0 );
	int			absoluteRotation = 0;

	bool		isSpaceAvailable = true;

	// Check if there is enough space available to place all bricks
	std::vector<BasicBrickData>::iterator brickIterator = m_legoStructures[type].m_bricks.begin();
	while( isSpaceAvailable && brickIterator!= m_legoStructures[type].m_bricks.end() )
	{
		absolutePosition.m_x = gridPosition.m_x;
		absolutePosition.m_y = gridPosition.m_y + brickIterator->m_position.m_y;
		absolutePosition.m_z = gridPosition.m_z;

		if(rotation == 0 || rotation == 360)
		{
			absolutePosition.m_x += brickIterator->m_position.m_x;
			absolutePosition.m_z += brickIterator->m_position.m_z;
		}else if(rotation == 90 || rotation == -270)
		{
			absolutePosition.m_x += brickIterator->m_position.m_z;
			absolutePosition.m_z += -brickIterator->m_position.m_x;
		}else if(rotation == 180)
		{
			absolutePosition.m_x += -brickIterator->m_position.m_x;
			absolutePosition.m_z += -brickIterator->m_position.m_z;
		}else if(rotation == -90 || rotation == 270)
		{
			absolutePosition.m_x += -brickIterator->m_position.m_z;
			absolutePosition.m_z += brickIterator->m_position.m_x;
		}
		
		absoluteRotation = ( rotation + brickIterator->m_rotation ) % 360;

		IntVector3 extentsOnGrid; 
		IntVector3 positionOnGrid;

		// Given the current rotation of the brick, get the actual brick extents in grid space
		GetBrickExtentsOnGrid( BrickSizesInUnits[brickIterator->m_type], absolutePosition, absoluteRotation, extentsOnGrid, positionOnGrid );
		
		isSpaceAvailable = CheckSpace( positionOnGrid, extentsOnGrid );

		++brickIterator;
	}
		
	// todo: Possible to get rid of redundancy of code in check space and add bricks loop? Also redundancy between this function and AddBrick()

	// Add the brick to the world
	if( isSpaceAvailable )
	{
		// Calculate transfrom matrix for the structure once -> same for all bricks
	
		// Translation matrix for the structure
		XMMATRIX matStructureTranslation = XMMatrixTranslation( gridPosition.m_x * GRID_UNIT.x + GRID_UNIT.x * 0.5f, gridPosition.m_y * GRID_UNIT.y, gridPosition.m_z * GRID_UNIT.z + GRID_UNIT.z * 0.5f );

		// the actual rotation of the structure
		XMMATRIX matPureStructureRotation = XMMatrixRotationAxis( XMVectorSet( 0.0f, 1.0f, 0.0f, 0.0f ), XMConvertToRadians( static_cast<float>( rotation ) ) );
		// calculate translation matrices to and from the rotation centre
		XMMATRIX matStructureTranslationRotCentre = XMMatrixTranslation( gridPosition.m_x * GRID_UNIT.x + GRID_UNIT.x * 0.5f, gridPosition.m_y * GRID_UNIT.y, gridPosition.m_z * GRID_UNIT.z + GRID_UNIT.z * 0.5f);	// Rotation centre (from origin).
		XMVECTOR determinant;
		XMMATRIX matStructureTranslationRotCentreInv = XMMatrixInverse(&determinant, matStructureTranslationRotCentre);
		// Combine the matrices to the completed rotation matrix for the structure
		XMMATRIX matStructureRotation = matStructureTranslationRotCentreInv * matPureStructureRotation * matStructureTranslationRotCentre;
		
		XMMATRIX matStructureTransform = matStructureTranslation * matStructureRotation;


		for(std::vector<BasicBrickData>::iterator brickIterator = m_legoStructures[type].m_bricks.begin(); brickIterator != m_legoStructures[type].m_bricks.end(); ++brickIterator)
		{
			absolutePosition.m_x = gridPosition.m_x;
			absolutePosition.m_y = gridPosition.m_y + brickIterator->m_position.m_y;
			absolutePosition.m_z = gridPosition.m_z;

			if(rotation == 0 || rotation == 360)
			{
				absolutePosition.m_x += brickIterator->m_position.m_x;
				absolutePosition.m_z += brickIterator->m_position.m_z;
			}else if(rotation == 90 || rotation == -270)
			{
				absolutePosition.m_x += brickIterator->m_position.m_z;
				absolutePosition.m_z += -brickIterator->m_position.m_x;
			}else if(rotation == 180)
			{
				absolutePosition.m_x += -brickIterator->m_position.m_x;
				absolutePosition.m_z += -brickIterator->m_position.m_z;
			}else if(rotation == -90 || rotation == 270)
			{
				absolutePosition.m_x += -brickIterator->m_position.m_z;
				absolutePosition.m_z += brickIterator->m_position.m_x;
			}
		
			absoluteRotation = ( rotation + brickIterator->m_rotation ) % 360;

			// Brick translation
			XMMATRIX matBrickTranslation = XMMatrixTranslation( brickIterator->m_position.m_x * GRID_UNIT.x, brickIterator->m_position.m_y * GRID_UNIT.y, brickIterator->m_position.m_z * GRID_UNIT.z );
			// Brick rotation
			XMMATRIX matBrickRotation = XMMatrixRotationAxis( XMVectorSet( 0.0f, 1.0f, 0.0f, 0.0f ), XMConvertToRadians( static_cast<float>( brickIterator->m_rotation ) ) );

			// Create transformation matrix for the brick
			XMFLOAT4X4 matTransform;
			XMStoreFloat4x4( &matTransform, matBrickRotation * matBrickTranslation * matStructureTransform );

			// create new brick and add it to the brick vector
			LegoBrick brick( ++m_Id, LegoBrickType(brickIterator->m_type), brickIterator->m_colour, absolutePosition, absoluteRotation, matTransform);

			IntVector3 extentsOnGrid; 
			IntVector3 positionOnGrid;

			// Given the current rotation of the brick, get the actual brick extents in grid space
			GetBrickExtentsOnGrid( BrickSizesInUnits[brickIterator->m_type], absolutePosition, absoluteRotation, extentsOnGrid, positionOnGrid );
		
			//m_legoBricks.push_back(brick);
			m_legoWorldTree.AddBrick( brick, positionOnGrid, extentsOnGrid );
			++m_numberOfBricks;

			if( m_doRecord )
			{
				m_recordedLegoBricks.push_back(brick);
			}

			// Update id matrix
		
			//IntVector3 extentsOnGrid; 
			//IntVector3 positionOnGrid;

			// Given the current rotation of the brick, get the actual brick extents in grid space
			//GetBrickExtentsOnGrid( BrickSizesInUnits[brickIterator->m_type], absolutePosition, absoluteRotation, extentsOnGrid, positionOnGrid );
		
			for( int i = positionOnGrid.m_x + GRID_HALF_SIZE.m_x ; i < positionOnGrid.m_x + GRID_HALF_SIZE.m_x + extentsOnGrid.m_x; ++i )
			{
				for( int j = positionOnGrid.m_y + GRID_HALF_SIZE.m_y; j < positionOnGrid.m_y + GRID_HALF_SIZE.m_y + extentsOnGrid.m_y; ++j )
				{
					for( int k = positionOnGrid.m_z + GRID_HALF_SIZE.m_z ; k < positionOnGrid.m_z + GRID_HALF_SIZE.m_z + extentsOnGrid.m_z; ++k )
					{
						m_idMatrix[i][j][k] = brick.m_id;
					}
				}
			}

			// Add studs
			for( int i = positionOnGrid.m_x + GRID_HALF_SIZE.m_x ; i < positionOnGrid.m_x + GRID_HALF_SIZE.m_x + extentsOnGrid.m_x; ++i )
			{
				for( int j = positionOnGrid.m_z + GRID_HALF_SIZE.m_z ; j < positionOnGrid.m_z + GRID_HALF_SIZE.m_z + extentsOnGrid.m_z; ++j )
				{
					AddStud( i - GRID_HALF_SIZE.m_x, positionOnGrid.m_y, j - GRID_HALF_SIZE.m_z, extentsOnGrid.m_y, brickIterator->m_colour );
				}
			}

			
		}
		// structure was added successfully
			return true;
	}
	// structure could not be placed (intersections with existing bricks)
	return false;
}

//--------------------------------------------------------------------------------------
// Converts the extents and position of a lego brick into grid space depending on the current rotation.
//--------------------------------------------------------------------------------------
void LegoWorldImplementation::GetBrickExtentsOnGrid( const IntVector3& brickExtents, const IntVector3& brickPosition, int rotation, IntVector3& outBrickExtentsOnGrid, IntVector3& outBrickPositionOnGrid )
{
	// todo: find a better solution to this without having to manually set the extents

	outBrickPositionOnGrid.m_x = brickPosition.m_x;
	outBrickPositionOnGrid.m_y = brickPosition.m_y;
	outBrickPositionOnGrid.m_z = brickPosition.m_z;

	outBrickExtentsOnGrid.m_x = brickExtents.m_x;
	outBrickExtentsOnGrid.m_y = brickExtents.m_y;
	outBrickExtentsOnGrid.m_z = brickExtents.m_z;

	if( rotation == -90 || rotation == 270 )
	{
		outBrickPositionOnGrid.m_x -= brickExtents.m_z - 1;

		outBrickExtentsOnGrid.m_x = brickExtents.m_z;
		outBrickExtentsOnGrid.m_z = brickExtents.m_x;
	}else if( rotation == 90 || rotation == -270 )
	{
		outBrickPositionOnGrid.m_z -= brickExtents.m_x - 1;

		outBrickExtentsOnGrid.m_x = brickExtents.m_z;
		outBrickExtentsOnGrid.m_z = brickExtents.m_x;
	}else if(rotation == 180 || rotation == -180)
	{
		outBrickPositionOnGrid.m_x -= brickExtents.m_x - 1;
		outBrickPositionOnGrid.m_z -= brickExtents.m_z - 1;
	}
}

//--------------------------------------------------------------------------------------
// Remove a brick from the lego world
//--------------------------------------------------------------------------------------
bool LegoWorldImplementation::RemoveLegoBrick( const IntVector3& gridPosition )
{
	// check if the cursor is on the grid
	if( ( gridPosition.m_x + 1 <= MAX_GRID_POS.m_x && gridPosition.m_x >= MIN_GRID_POS.m_x ) && 
		( gridPosition.m_y + 1 <= MAX_GRID_POS.m_y && gridPosition.m_y >= MIN_GRID_POS.m_y ) &&
		( gridPosition.m_z + 1 <= MAX_GRID_POS.m_z && gridPosition.m_z >= MIN_GRID_POS.m_z ) )
	{
		int deleteId = m_idMatrix[gridPosition.m_x + GRID_HALF_SIZE.m_x][gridPosition.m_y + GRID_HALF_SIZE.m_y][gridPosition.m_z + GRID_HALF_SIZE.m_z];

		if( deleteId != 0 )
		{
			// get brick to the id
			//std::vector<LegoBrick>::iterator deleteIterator = std::find_if( m_legoBricks.begin(), m_legoBricks.end(), FindBrickById( deleteId ) );

			LegoBrickType deleteBrickType;
			IntVector3    deleteBrickPosition;
			int			  deleteBrickRotation;
			
			// acquire information on the deleted brick in order to be able to update the idMatrix
			m_legoWorldTree.RemoveBrick( deleteId, deleteBrickType, deleteBrickPosition, deleteBrickRotation );
			--m_numberOfBricks;

			IntVector3 extentsOnGrid; 
			IntVector3 positionOnGrid;

			// Given the current rotation of the brick, get the actual brick extents in grid space
			GetBrickExtentsOnGrid( BrickSizesInUnits[deleteBrickType], deleteBrickPosition, deleteBrickRotation, extentsOnGrid, positionOnGrid );

			for( int i = positionOnGrid.m_x + GRID_HALF_SIZE.m_x ; i < positionOnGrid.m_x + GRID_HALF_SIZE.m_x + extentsOnGrid.m_x; ++i )
			{
				for( int j = positionOnGrid.m_y + GRID_HALF_SIZE.m_y; j < positionOnGrid.m_y + GRID_HALF_SIZE.m_y + extentsOnGrid.m_y; ++j )
				{
					for( int k = positionOnGrid.m_z + GRID_HALF_SIZE.m_z ; k < positionOnGrid.m_z + GRID_HALF_SIZE.m_z + extentsOnGrid.m_z; ++k )
					{
						m_idMatrix[i][j][k] = 0;
					}
				}
			}

			// Remove studs
			for( int i = positionOnGrid.m_x + GRID_HALF_SIZE.m_x ; i < positionOnGrid.m_x + GRID_HALF_SIZE.m_x + extentsOnGrid.m_x; ++i )
			{
				for( int j = positionOnGrid.m_z + GRID_HALF_SIZE.m_z ; j < positionOnGrid.m_z + GRID_HALF_SIZE.m_z + extentsOnGrid.m_z; ++j )
				{
					RemoveStud( i - GRID_HALF_SIZE.m_x, positionOnGrid.m_y, j - GRID_HALF_SIZE.m_z, extentsOnGrid.m_y );
				}
			}

			// delete the brick
			// m_legoBricks.erase( deleteIterator );

			if( m_doRecord )
			{
			    std::vector<LegoBrick>::iterator deleteRecordedIt = std::find_if( m_recordedLegoBricks.begin(), m_recordedLegoBricks.end(), FindBrickById( deleteId ) );
				if( deleteRecordedIt != m_recordedLegoBricks.end() )
				{
					m_recordedLegoBricks.erase( deleteRecordedIt );
				}
			}

			return true;
		}else
		{
			return false;
		}
	}else
	{
		return false;
	}
}

//--------------------------------------------------------------------------------------
// Release any ressources allocated by the lego world.
//--------------------------------------------------------------------------------------
HRESULT LegoWorldImplementation::Cleanup( void )
{
	return S_OK;
}

//--------------------------------------------------------------------------------------
// Update the passed in contexts:
//	- RenderContext: determines number and content of instances of each brick type to be rendered
//--------------------------------------------------------------------------------------
void LegoWorldImplementation::Update( RenderContext* pRenderContext, const XMFLOAT4 frustumPlanes[6] )
{
	m_legoWorldTree.UpdateVisibility( pRenderContext, frustumPlanes);
}

//--------------------------------------------------------------------------------------
// Save the current lego world to the text file specified by the parameter
//--------------------------------------------------------------------------------------
bool LegoWorldImplementation::Save( std::string filename )
{
	// todo: add validation/error handling for I/O

    std::ofstream out( filename );

	if( out.good() )
	{
		m_legoWorldTree.SaveBricks( out );

		// For every brick, write a line to the file with the information needed to restore the world later on
		//for(std::vector<LegoBrick>::iterator brickIt = m_legoBricks.begin(); brickIt != m_legoBricks.end(); ++brickIt)
		//{
		//	out << brickIt->m_type << "," << brickIt->m_colour << "," << brickIt->m_rotation << "," << brickIt->m_position.m_x << "," << brickIt->m_position.m_y << "," << brickIt->m_position.m_z << "\n";
		//}

		out.close();
		return true;
	}

	// opening of the file failed
	return false;
}

//--------------------------------------------------------------------------------------
// Load a lego world from the text file specified as parameter.
// The current lego world will be deleted and replaced by the one stored in the file.
//--------------------------------------------------------------------------------------
bool LegoWorldImplementation::Load( std::string filename )
{
	// todo: add validation/error handling for I/O

	std::ifstream in( filename );
	if(in.good())
	{
		// reset data structures before loading the new world
		memset( &m_idMatrix, 0, sizeof( unsigned int ) * GRID_SIZE_X * GRID_SIZE_Y * GRID_SIZE_Z );
		m_Id = 0;
		//m_legoBricks.clear();

		m_legoWorldTree.Clear();
		m_numberOfBricks = 0;
		m_numberOfStuds = 0;
		if( m_recordedLegoBricks.size() > 0 )
		{
			m_recordedLegoBricks.clear();
		}

		// local variables for temporarily storing of the read in data
		int type;
		int colour;
		int rotation;
		int positionX;
		int positionY;
		int positionZ;
		char ch;

		while(in.good())
		{
			std::string s;
			getline( in, s );
			std::istringstream iss(s);
			iss >> type >> ch >> colour >> ch >> rotation >> ch >> positionX >> ch >> positionY >> ch >> positionZ;
			AddLegoBrick( LegoBrickType( type ), IntVector3( positionX, positionY, positionZ ), rotation, LegoBrickColour( colour ) ); 
		}

		in.close();
		return true;
	}else
	{
		// opening of the file failed
		return false;
	}
}

void LegoWorldImplementation::GetExtentsOfStructure( int index, IntVector3* pDestination )
{
	pDestination->m_x = m_legoStructures[index].m_extents.m_x;
	pDestination->m_y = m_legoStructures[index].m_extents.m_y;
	pDestination->m_z = m_legoStructures[index].m_extents.m_z;
}

int LegoWorldImplementation::GetNumberOfCustomStructures( void ) const
{
	return m_legoStructures.size();
}

/*
const std::vector<LegoBrick> * const LegoWorldImplementation::GetBricks( void ) const
{
	return &m_legoBricks;
}*/

//--------------------------------------------------------------------------------------
// Activate recording mode. Placed bricks will be remembered and can be stored as a 
// reusable custom structure upon switching off the recording mode.
//--------------------------------------------------------------------------------------
void LegoWorldImplementation::StartRecording()
{
	m_doRecord = true;
}

//--------------------------------------------------------------------------------------
// Stop recording bricks. If bricks have been recorded they can be saved as a reusable
// custom structure of the specified name, depending on the first parameter to the function.
// If 'doSave' evaluates to false, the recorded bricks will be discarded.
//--------------------------------------------------------------------------------------
bool LegoWorldImplementation::StopRecording( bool doSave, std::string name)
{
	m_doRecord = false;

	// Recording mode was switched off and bricks have been recorded
	if( doSave && !m_recordedLegoBricks.empty() )
	{
		// Create a custom lego structure
		LegoStructure structure;
		structure.m_name = name;

		// determine the extents of the structure on the grid

		IntVector3 minGridPos(MAX_GRID_POS);
		IntVector3 maxGridPos(MIN_GRID_POS);
		IntVector3 minBrickPos(MAX_GRID_POS);

		

		for( std::vector<LegoBrick>::iterator recBricksIt = m_recordedLegoBricks.begin(); recBricksIt != m_recordedLegoBricks.end(); ++recBricksIt )
		{
			// todo: what if brick rotated and extents reach into negative direction
			// -> account for rotation!!! and get actual smallest position
			if(recBricksIt->m_position.m_x < minBrickPos.m_x )
			{
				minBrickPos.m_x = recBricksIt->m_position.m_x;
			}
			
			if(recBricksIt->m_position.m_y < minBrickPos.m_y )
			{
				minBrickPos.m_y = recBricksIt->m_position.m_y;
			}

			if(recBricksIt->m_position.m_z < minBrickPos.m_z )
			{
				minBrickPos.m_z = recBricksIt->m_position.m_z;
			}

			IntVector3 extentsOnGrid; 
			IntVector3 positionOnGrid;

			// Given the current rotation of the brick, get the actual brick extents in grid space
			GetBrickExtentsOnGrid( BrickSizesInUnits[recBricksIt->m_type], recBricksIt->m_position, recBricksIt->m_rotation, extentsOnGrid, positionOnGrid );
		
			//find the origin of the structure (the grid position with the smallest x,y,z value) 

			if(positionOnGrid.m_x < minGridPos.m_x )
			{
				minGridPos.m_x = positionOnGrid.m_x;
			}
			
			if(positionOnGrid.m_y < minGridPos.m_y )
			{
				minGridPos.m_y = positionOnGrid.m_y;
			}

			if(positionOnGrid.m_z < minGridPos.m_z )
			{
				minGridPos.m_z = positionOnGrid.m_z;
			}
			
			// find max of structure (grid pos with biggest x,y,z values)

			if(positionOnGrid.m_x + extentsOnGrid.m_x > maxGridPos.m_x )
			{
				maxGridPos.m_x = positionOnGrid.m_x + extentsOnGrid.m_x;
			}

			if(positionOnGrid.m_y + extentsOnGrid.m_y > maxGridPos.m_y )
			{
				maxGridPos.m_y = positionOnGrid.m_y + extentsOnGrid.m_y;
			}

			if(positionOnGrid.m_z + extentsOnGrid.m_z > maxGridPos.m_z )
			{
				maxGridPos.m_z = positionOnGrid.m_z + extentsOnGrid.m_z;
			}
		}

		// calculate the extents of the structure
		structure.m_extents.m_x = maxGridPos.m_x - minGridPos.m_x;
		structure.m_extents.m_y = maxGridPos.m_y - minGridPos.m_y;
		structure.m_extents.m_z = maxGridPos.m_z - minGridPos.m_z;

		// Translate the bricks into structure space

		for( std::vector<LegoBrick>::iterator recBricksIt = m_recordedLegoBricks.begin(); recBricksIt != m_recordedLegoBricks.end(); ++recBricksIt )
		{
			// todo: check if this makes sense, is correct!
			IntVector3 relativePos;
			//relativePos.m_x = (recBricksIt->m_position.m_x - minGridPos.m_x);
			//relativePos.m_y = (recBricksIt->m_position.m_y - minGridPos.m_y);
			//relativePos.m_z = (recBricksIt->m_position.m_z - minGridPos.m_z);
			
			relativePos.m_x = (recBricksIt->m_position.m_x - minGridPos.m_x);
			relativePos.m_y = (recBricksIt->m_position.m_y - minGridPos.m_y);
			relativePos.m_z = (recBricksIt->m_position.m_z - minGridPos.m_z);

			BasicBrickData brickData( recBricksIt->m_type, recBricksIt->m_colour, relativePos, recBricksIt->m_rotation );

			structure.m_bricks.push_back( brickData );
		}

		// save the new structure
		m_legoStructures.push_back( structure );

		// update custom structures file
		SaveCustomStructures( CUSTOM_STRUCTURES_FILENAME );

		m_recordedLegoBricks.clear();
		return true;
	}else
	{
		m_recordedLegoBricks.clear();
		return false;
	}
}

//--------------------------------------------------------------------------------------
// Save all custom lego structures to a file in order to make them available when the 
// application is used the next time.
//--------------------------------------------------------------------------------------
bool LegoWorldImplementation::SaveCustomStructures( std::string filename )
{
	// todo: add validation/error handling for I/O

    std::ofstream out (filename);

	if( out.good() )
	{
		for(std::vector<LegoStructure>::iterator structureIterator = m_legoStructures.begin(); structureIterator != m_legoStructures.end(); ++structureIterator)
		{
			out << structureIterator->m_name << " " << structureIterator->m_extents.m_x << "," << structureIterator->m_extents.m_y << "," << structureIterator->m_extents.m_z << "\n";
			for(std::vector<BasicBrickData>::iterator brickIterator = structureIterator->m_bricks.begin(); brickIterator != structureIterator->m_bricks.end(); ++brickIterator)
			{
				out << brickIterator->m_type << "," << brickIterator->m_colour << "," << brickIterator->m_rotation << "," << brickIterator->m_position.m_x << "," << brickIterator->m_position.m_y << "," << brickIterator->m_position.m_z << "\n";
			}
			out << "End of structure\n";
		}

		out.close();
		return true;
	}else
	{
		// opening the file failed
		return false;
	}
}

//--------------------------------------------------------------------------------------
// Load the custom lego structures from a file
//--------------------------------------------------------------------------------------
bool LegoWorldImplementation::LoadCustomStructures( std::string filename )
{
	// todo: add validation/error handling for I/O

	// local variables for temporarily storing of the read in data
	//std::string name;
	//int extentsX;
	//int extentsY;
	//int extentsZ;

	int type;
	int colour;
	int rotation;
	int positionX;
	int positionY;
	int positionZ;
	char ch;

	std::ifstream in( filename );
	if( in.good() )
	{
		while( in.good() )
		{
			std::string s;

			getline(in, s);
			std::istringstream iss( s );

			// nothing to read
			if( s == "" )
				return false;

			LegoStructure structure;

			iss >> structure.m_name >> structure.m_extents.m_x >> ch >> structure.m_extents.m_y >> ch >> structure.m_extents.m_z;

			//BrickDimensions dimensions(dimensionX, dimensionY, dimensionZ);

			//LegoStructure structure(name, dimensions);

			// Read in the bricks the structure consists of

			bool allBricksRead = false;

			while(!allBricksRead)
			{
				getline( in, s );
				std::istringstream iss( s );
			
				if(s != "End of structure")
				{
					iss >> type >> ch >> colour >> ch >> rotation >> ch >> positionX >> ch >> positionY >> ch >> positionZ;
		
					BasicBrickData brick( LegoBrickType(type), LegoBrickColour(colour), IntVector3(positionX, positionY, positionZ), rotation);
					structure.m_bricks.push_back( brick );
				}else
				{
					allBricksRead = true;
				}
			}

			m_legoStructures.push_back(structure);
		}

		in.close();
		return true;
	}else
	{
		// opening the file failed
		return false;
	}
}

const std::string& LegoWorldImplementation::GetCustomStructureName( int type ) const
{
	return m_legoStructures[type].m_name;
}

int	LegoWorldImplementation::GetNumberOfBricks( void ) const
{
	return m_numberOfBricks;
}

int	LegoWorldImplementation::GetNumberOfStuds( void ) const
{
	return m_numberOfStuds;
}