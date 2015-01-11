/* 
*  Kevin Meergans, Improved Lego Editor, 2014
*  LegoWorldNode.cpp
*  Contains the function definitions for the LegoWorldNode class. Calls to these
*  functions will be forwarded to the implementation part of the LegoWorldNode class
*  "LegoWorldNodeImplementation".
*/

#include "LegoWorldNode.h"
#include "LegoWorldNodeImplementation.h"

LegoWorldNode::LegoWorldNode( IntVector3 centre, IntVector3 size, int treeLevel ) : m_pImplementation( new LegoWorldNodeImplementation( centre, size, treeLevel ) )
{
}

bool LegoWorldNode::AddBrick( const LegoBrick& brick, const IntVector3& brickPositionOnGrid, const IntVector3& brickExtentsOnGrid )
{
	return m_pImplementation -> AddBrick( brick, brickPositionOnGrid, brickExtentsOnGrid );
}

bool LegoWorldNode::RemoveBrick( unsigned int deleteId, LegoBrickType& deleteType, IntVector3& deletePosition, int& deleteRotation )
{
	return m_pImplementation -> RemoveBrick( deleteId, deleteType, deletePosition, deleteRotation );
}

bool LegoWorldNode::AddStud( const LegoStud& stud, const IntVector3& gridPosition )
{
	return m_pImplementation -> AddStud( stud, gridPosition );
}

bool LegoWorldNode::RemoveStud( const IntVector3& deletePosition )
{
	return m_pImplementation -> RemoveStud( deletePosition );
}

void LegoWorldNode::SaveBricks(std::ofstream& out)
{
	return m_pImplementation -> SaveBricks( out );
}

void LegoWorldNode::Clear( void )
{
	m_pImplementation -> Clear();
}

void LegoWorldNode::UpdateVisibility( RenderContext* pRenderContext, const XMFLOAT4 frustumPlanes[6] )
{
	m_pImplementation -> UpdateVisibility( pRenderContext, frustumPlanes );
}

const LegoBrick* const LegoWorldNode::GetLegoBrick( long id ) const
{
	return m_pImplementation -> GetLegoBrick( id );
}
