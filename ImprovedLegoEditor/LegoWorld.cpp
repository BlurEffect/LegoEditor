/* 
*  Kevin Meergans, Improved Lego Editor, 2014
*  LegoWorld.cpp
*  Contains the function definitions for the LegoWorld class. Calls to these
*  functions will be forwarded to the implementation part of the LegoWorld class
*  "LegoWorldImplementation".
*/

#include "LegoWorld.h"
#include "LegoWorldImplementation.h"


LegoWorld::LegoWorld( void ) : m_pImplementation( new LegoWorldImplementation() )
{
}

HRESULT LegoWorld::Initialise( void )
{
	return m_pImplementation -> Initialise();
}

bool LegoWorld::AddLegoBrick( int type, const IntVector3& gridPosition, int rotation, LegoBrickColour colour )
{
	return m_pImplementation -> AddLegoBrick( type, gridPosition, rotation, colour );
}

bool LegoWorld::AddLegoStructure( unsigned int type, const IntVector3& gridPosition, int rotation )
{
	return m_pImplementation -> AddLegoStructure( type, gridPosition, rotation );
}

bool LegoWorld::RemoveLegoBrick( const IntVector3& gridPosition )
{
	return m_pImplementation -> RemoveLegoBrick( gridPosition );
}



HRESULT LegoWorld::Cleanup( void )
{
	return m_pImplementation -> Cleanup();
}

void LegoWorld::Update( RenderContext* pRenderContext, const XMFLOAT4 frustumPlanes[6] )
{
	return m_pImplementation -> Update( pRenderContext, frustumPlanes );
}


bool LegoWorld::Save( std::string filename )
{
	return m_pImplementation -> Save( filename );
}

bool LegoWorld::Load( std::string filename )
{
	return m_pImplementation -> Load( filename );
}

void LegoWorld::StartRecording()
{
	m_pImplementation -> StartRecording();
}

bool LegoWorld::StopRecording( bool doSave, std::string name)
{
	return m_pImplementation -> StopRecording( doSave, name );
}

void LegoWorld::GetExtentsOfStructure( int index, IntVector3* pDestination )
{
	m_pImplementation -> GetExtentsOfStructure( index, pDestination );
}

int LegoWorld::GetNumberOfCustomStructures( void ) const
{
	return m_pImplementation -> GetNumberOfCustomStructures();
}

const std::string& LegoWorld::GetCustomStructureName( int type ) const
{
	return m_pImplementation -> GetCustomStructureName( type );
}

int	LegoWorld::GetNumberOfBricks( void ) const
{
	return m_pImplementation -> GetNumberOfBricks();
}

int	LegoWorld::GetNumberOfStuds( void ) const
{
	return m_pImplementation -> GetNumberOfStuds();
}

