/* 
*  Kevin Meergans, Improved Lego Editor, 2014
*  LegoWorldNodeImplementation.cpp
*  Contains the function definitions for the LegoWorldNodeImplementation class.
*/

#include "LegoWorldNodeImplementation.h"

LegoWorldNodeImplementation::LegoWorldNodeImplementation( IntVector3 centre, IntVector3 size, int treeLevel ) : 
								m_centre( centre ), 
								m_size( size ), 
								m_treeLevel( treeLevel )
{
	// Initialise bounding box

	m_boundingBox[0].m_x = centre.m_x - size.m_x/2;
	m_boundingBox[0].m_y = centre.m_y - size.m_y/2;
	m_boundingBox[0].m_z = centre.m_z - size.m_z/2;

	m_boundingBox[1].m_x = centre.m_x + size.m_x/2;
	m_boundingBox[1].m_y = centre.m_y + size.m_y/2;
	m_boundingBox[1].m_z = centre.m_z + size.m_z/2;
}

//--------------------------------------------------------------------------------------
// Add a new brick to the tree. If necessary new tree nodes will be created and added.
// The brick is added to the smallest node fully encompassing it.
//--------------------------------------------------------------------------------------
bool LegoWorldNodeImplementation::AddBrick( const LegoBrick& brick, const IntVector3& brickPositionOnGrid, const IntVector3& brickExtentsOnGrid )
{
	if( IsFullyEncompassingBrick( brickPositionOnGrid, brickExtentsOnGrid ) )
	{
		if( m_children.size() > 0 )
		{
			// Check if there is even a child and therefore smaller noder fully encompassing the brick.

			bool addedByChild = false;
			unsigned int i = 0;

			while( !addedByChild && i < m_children.size() )
			{
				if( m_children[i].AddBrick( brick, brickPositionOnGrid, brickExtentsOnGrid ) )
				{
					addedByChild = true;
				}
				++i;
			}

			// No child node fully encompasses the brick, so this brick is the smallest one doing so -> add the brick
			if( !addedByChild )
			{
				m_bricks.push_back( brick );
			}
		}else
		{
			if( m_treeLevel < MAX_TREE_LEVEL )
			{
				// todo: here 7 nodes are created that don't hold any data at all, better solution?

				// add 8 new equal sized children to this node and try to add the brick to one of these
				m_children.push_back( LegoWorldNode( IntVector3( m_centre.m_x + m_size.m_x/4, m_centre.m_y + m_size.m_y/4, m_centre.m_z + m_size.m_z/4 ), IntVector3( m_size.m_x/2, m_size.m_y/2, m_size.m_z/2 ), m_treeLevel + 1 ) );
				m_children.push_back( LegoWorldNode( IntVector3( m_centre.m_x + m_size.m_x/4, m_centre.m_y + m_size.m_y/4, m_centre.m_z - m_size.m_z/4 ), IntVector3( m_size.m_x/2, m_size.m_y/2, m_size.m_z/2 ), m_treeLevel + 1 ) );
				m_children.push_back( LegoWorldNode( IntVector3( m_centre.m_x + m_size.m_x/4, m_centre.m_y - m_size.m_y/4, m_centre.m_z + m_size.m_z/4 ), IntVector3( m_size.m_x/2, m_size.m_y/2, m_size.m_z/2 ), m_treeLevel + 1 ) );
				m_children.push_back( LegoWorldNode( IntVector3( m_centre.m_x + m_size.m_x/4, m_centre.m_y - m_size.m_y/4, m_centre.m_z - m_size.m_z/4 ), IntVector3( m_size.m_x/2, m_size.m_y/2, m_size.m_z/2 ), m_treeLevel + 1 ) );
				m_children.push_back( LegoWorldNode( IntVector3( m_centre.m_x - m_size.m_x/4, m_centre.m_y + m_size.m_y/4, m_centre.m_z + m_size.m_z/4 ), IntVector3( m_size.m_x/2, m_size.m_y/2, m_size.m_z/2 ), m_treeLevel + 1 ) );
				m_children.push_back( LegoWorldNode( IntVector3( m_centre.m_x - m_size.m_x/4, m_centre.m_y + m_size.m_y/4, m_centre.m_z - m_size.m_z/4 ), IntVector3( m_size.m_x/2, m_size.m_y/2, m_size.m_z/2 ), m_treeLevel + 1 ) );
				m_children.push_back( LegoWorldNode( IntVector3( m_centre.m_x - m_size.m_x/4, m_centre.m_y - m_size.m_y/4, m_centre.m_z + m_size.m_z/4 ), IntVector3( m_size.m_x/2, m_size.m_y/2, m_size.m_z/2 ), m_treeLevel + 1 ) );
				m_children.push_back( LegoWorldNode( IntVector3( m_centre.m_x - m_size.m_x/4, m_centre.m_y - m_size.m_y/4, m_centre.m_z - m_size.m_z/4 ), IntVector3( m_size.m_x/2, m_size.m_y/2, m_size.m_z/2 ), m_treeLevel + 1 ) );

				// try to add the brick to one of the new children
				bool addedByChild = false;
				unsigned int i = 0;

				while( !addedByChild && i < m_children.size() )
				{
					if( m_children[i].AddBrick( brick, brickPositionOnGrid, brickExtentsOnGrid ) )
					{
						addedByChild = true;
					}
					++i;
				}

				// No child node fully encompasses the brick, so this brick is the smallest one doing so -> add the brick
				if( !addedByChild )
				{
					m_bricks.push_back( brick );
				}
			}else
			{
				// The node doesn't have any children but as the maximal tree depth is already reached, it is not allowed
				// to add further children. Therefore this node has to add the brick itself
				m_bricks.push_back( brick );
			}
		}
		return true;
	}else
	{
		// Brick not encompassed by this node, parent has to find other node to add the brick to
		return false;
	}
}

//--------------------------------------------------------------------------------------
// Remove a brick from the tree. If the removed brick was the only brick stored in a node,
// that node will be removed as well. Information on the deleted brick is returned to the caller
// by using the passed in pointers.
//--------------------------------------------------------------------------------------
bool LegoWorldNodeImplementation::RemoveBrick( unsigned int deleteId, LegoBrickType& deleteType, IntVector3& deletePosition, int& deleteRotation )
{
	std::vector<LegoBrick>::iterator deleteIterator = std::find_if( m_bricks.begin(), m_bricks.end(), FindBrickById( deleteId ) );

	if( deleteIterator != m_bricks.end() )
	{
		// Brick is part of this node's data, return information on the deleted brick, delete the brick and return
		deleteType = deleteIterator -> m_type;
		deletePosition = deleteIterator -> m_position;
		deleteRotation = deleteIterator -> m_rotation;

		m_bricks.erase( deleteIterator );

		return true;
	}else
	{
		if( m_children.size() > 0 )
		{
			// try to delete the brick in the children, provided that one of them contains them
			bool deletedByChild = false;
			unsigned int i = 0;

			while( !deletedByChild && i < m_children.size() )
			{
				if( m_children[i].RemoveBrick( deleteId, deleteType, deletePosition, deleteRotation ) )
				{
					deletedByChild = true;
				}
				++i;
			}

			return deletedByChild;
		}else
		{
			// none of the children contains the brick to be deleted
			return false;
		}
	}
}

//--------------------------------------------------------------------------------------
// Save all bricks encompassed in this node using the passed in output stream and pass on
// the command to the child nodes.
//--------------------------------------------------------------------------------------
void LegoWorldNodeImplementation::SaveBricks(std::ofstream& out)
{
	// Write the bricks this node holds to the stream
	for( std::vector<LegoBrick>::iterator brickIt = m_bricks.begin(); brickIt != m_bricks.end(); ++brickIt )
	{
		out << brickIt->m_type << "," << brickIt->m_colour << "," << brickIt->m_rotation << "," << brickIt->m_position.m_x << "," << brickIt->m_position.m_y << "," << brickIt->m_position.m_z << "\n";
	}

	// If the node has children, have them write their children to the stream as well
	for( std::vector<LegoWorldNode>::iterator childrenIt = m_children.begin(); childrenIt != m_children.end(); ++childrenIt )
	{
		childrenIt -> SaveBricks( out );
	}

}

//--------------------------------------------------------------------------------------
// Remove all bricks and children from the node. Resets the tree to the original state.
//--------------------------------------------------------------------------------------
void LegoWorldNodeImplementation::Clear( void )
{
	// Clear the tree bottom up

	for( std::vector<LegoWorldNode>::iterator childrenIt = m_children.begin(); childrenIt != m_children.end(); ++childrenIt )
	{
		childrenIt -> Clear();
	}

	m_bricks.clear();
	m_children.clear();
}

//--------------------------------------------------------------------------------------
// Check the node for visibility given the passed in frustum planes and in case of being
// visible, add all contained bricks to the render context. Returns true if the node is visible
//--------------------------------------------------------------------------------------
void LegoWorldNodeImplementation::UpdateVisibility( RenderContext* pRenderContext, const XMFLOAT4 frustumPlanes[6] )
{
	// Only check for visibility if necessary -> save calculations
	if( ( m_bricks.size() > 0 || m_studs.size() > 0  ||m_children.size() > 0 ) && IsVisible( frustumPlanes ) )
	{
		// This node lies within the view frustum, add all nodes associated to this node to the renderContext and check
		// the children of this node for visibility as well.

		for( std::vector<LegoBrick>::iterator brickIt = m_bricks.begin(); brickIt != m_bricks.end(); ++brickIt )
		{
			pRenderContext -> AddBrick( *brickIt );
		}
		for( std::vector<LegoStud>::iterator studIt = m_studs.begin(); studIt != m_studs.end(); ++studIt )
		{
			pRenderContext -> AddStud( *studIt );
		}


		for( std::vector<LegoWorldNode>::iterator childrenIt = m_children.begin(); childrenIt != m_children.end(); ++childrenIt )
		{
			childrenIt -> UpdateVisibility( pRenderContext, frustumPlanes );
		}
	}
}

//--------------------------------------------------------------------------------------
// Returns true if the bounding box of this node fully encompasses the volume, defined
// by the passed in position and size.
//--------------------------------------------------------------------------------------
bool LegoWorldNodeImplementation::IsFullyEncompassingBrick( const IntVector3& brickGridOrigin, const IntVector3& brickGridExtents )
{
	// todo: check if these comparisons are correct or one off
	return ( m_boundingBox[0].m_x <= brickGridOrigin.m_x ) && ( (brickGridOrigin.m_x + brickGridExtents.m_x) <= m_boundingBox[1].m_x ) &&
		   ( m_boundingBox[0].m_y <= brickGridOrigin.m_y ) && ( (brickGridOrigin.m_y + brickGridExtents.m_y) <= m_boundingBox[1].m_y ) &&
		   ( m_boundingBox[0].m_z <= brickGridOrigin.m_z ) && ( (brickGridOrigin.m_z + brickGridExtents.m_z) <= m_boundingBox[1].m_z );
}

//--------------------------------------------------------------------------------------
// Returns true if the bounding box of this node lies within the view frustum defined by
// the six planes passed in as parameter.
// Bounding box test for culling adaped from: "Mathematics for 3D Game Programming and Computer Graphics", p.228f
//--------------------------------------------------------------------------------------
bool LegoWorldNodeImplementation::IsVisible( const XMFLOAT4 frustumPlanes[6] )
{

	// todo: check if this function works correctly, check with solutions from tutorials
	// todo: DOES THIS WORK AT ALL WITH GRID UNITS -> probably needs real values

	int i = 0;

	//XMFLOAT3 centre(m_centre.m_x, m_centre.m_y, m_centre.m_z);

	while( i < 6 )
	{
		XMFLOAT3 planeNormal;
		planeNormal.x = frustumPlanes[i].x;
		planeNormal.y = frustumPlanes[i].y;
		planeNormal.z = frustumPlanes[i].z;
		
		// Determine the effective radius

		float dotProduct1 = 0;
		float dotProduct2 = 0;
		float dotProduct3 = 0;
		
		// todo: save size*gridunit and centre*gridunit instead of computing every time. Tried to do that but GrigUnit constant
		// was still zero when executing the constructor. Problem with initialisation order? Need init function?

		XMStoreFloat( &dotProduct1, XMVector3Dot( XMLoadFloat3( &planeNormal ), XMVectorSet( m_size.m_x * 8.0f, 0, 0, 0 ) ) );
		XMStoreFloat( &dotProduct2, XMVector3Dot( XMLoadFloat3( &planeNormal ), XMVectorSet( 0, m_size.m_y * 3.2f, 0, 0 ) ) );
		XMStoreFloat( &dotProduct3, XMVector3Dot( XMLoadFloat3( &planeNormal ), XMVectorSet( 0, 0, m_size.m_z * 8.0f, 0 ) ) );

		float effectiveRadius = (abs(dotProduct1) + abs(dotProduct2) + abs(dotProduct3)) * 0.5f;

		float dotProduct;
		XMStoreFloat( &dotProduct, XMPlaneDotCoord( XMLoadFloat4( &frustumPlanes[i] ) , XMVectorSet( m_centre.m_x * 8.0f, m_centre.m_y * 3.2f, m_centre.m_z * 8.0f, 0 ) ) );

		float x = GRID_UNIT.x;

		if( dotProduct + effectiveRadius < 0 )
		{
			return false;
		}
		
		++i;
	}

	return true;
}

//--------------------------------------------------------------------------------------
// Add a new stud to the tree. If necessary new tree nodes will be created and added.
// The stud is added to the smallest node fully encompassing it.
//--------------------------------------------------------------------------------------
bool LegoWorldNodeImplementation::AddStud( const LegoStud& stud, const IntVector3& gridPosition )
{
	if( IsFullyEncompassingStud( gridPosition ) )
	{
		if( m_children.size() > 0 )
		{
			// Check if there is even a child and therefore smaller noder fully encompassing the brick.

			bool addedByChild = false;
			unsigned int i = 0;

			while( !addedByChild && i < m_children.size() )
			{
				if( m_children[i].AddStud( stud, gridPosition ) )
				{
					addedByChild = true;
				}
				++i;
			}

			// No child node fully encompasses the brick, so this brick is the smallest one doing so -> add the brick
			if( !addedByChild )
			{
				m_studs.push_back( stud );
			}
		}else
		{
			if( m_treeLevel < MAX_TREE_LEVEL )
			{
				// todo: here 7 nodes are created that don't hold any data at all, better solution?

				// add 8 new equal sized children to this node and try to add the brick to one of these
				m_children.push_back( LegoWorldNode( IntVector3( m_centre.m_x + m_size.m_x/4, m_centre.m_y + m_size.m_y/4, m_centre.m_z + m_size.m_z/4 ), IntVector3( m_size.m_x/2, m_size.m_y/2, m_size.m_z/2 ), m_treeLevel + 1 ) );
				m_children.push_back( LegoWorldNode( IntVector3( m_centre.m_x + m_size.m_x/4, m_centre.m_y + m_size.m_y/4, m_centre.m_z - m_size.m_z/4 ), IntVector3( m_size.m_x/2, m_size.m_y/2, m_size.m_z/2 ), m_treeLevel + 1 ) );
				m_children.push_back( LegoWorldNode( IntVector3( m_centre.m_x + m_size.m_x/4, m_centre.m_y - m_size.m_y/4, m_centre.m_z + m_size.m_z/4 ), IntVector3( m_size.m_x/2, m_size.m_y/2, m_size.m_z/2 ), m_treeLevel + 1 ) );
				m_children.push_back( LegoWorldNode( IntVector3( m_centre.m_x + m_size.m_x/4, m_centre.m_y - m_size.m_y/4, m_centre.m_z - m_size.m_z/4 ), IntVector3( m_size.m_x/2, m_size.m_y/2, m_size.m_z/2 ), m_treeLevel + 1 ) );
				m_children.push_back( LegoWorldNode( IntVector3( m_centre.m_x - m_size.m_x/4, m_centre.m_y + m_size.m_y/4, m_centre.m_z + m_size.m_z/4 ), IntVector3( m_size.m_x/2, m_size.m_y/2, m_size.m_z/2 ), m_treeLevel + 1 ) );
				m_children.push_back( LegoWorldNode( IntVector3( m_centre.m_x - m_size.m_x/4, m_centre.m_y + m_size.m_y/4, m_centre.m_z - m_size.m_z/4 ), IntVector3( m_size.m_x/2, m_size.m_y/2, m_size.m_z/2 ), m_treeLevel + 1 ) );
				m_children.push_back( LegoWorldNode( IntVector3( m_centre.m_x - m_size.m_x/4, m_centre.m_y - m_size.m_y/4, m_centre.m_z + m_size.m_z/4 ), IntVector3( m_size.m_x/2, m_size.m_y/2, m_size.m_z/2 ), m_treeLevel + 1 ) );
				m_children.push_back( LegoWorldNode( IntVector3( m_centre.m_x - m_size.m_x/4, m_centre.m_y - m_size.m_y/4, m_centre.m_z - m_size.m_z/4 ), IntVector3( m_size.m_x/2, m_size.m_y/2, m_size.m_z/2 ), m_treeLevel + 1 ) );

				// try to add the brick to one of the new children
				bool addedByChild = false;
				unsigned int i = 0;

				while( !addedByChild && i < m_children.size() )
				{
					if( m_children[i].AddStud( stud, gridPosition ) )
					{
						addedByChild = true;
					}
					++i;
				}

				// No child node fully encompasses the brick, so this brick is the smallest one doing so -> add the brick
				if( !addedByChild )
				{
					m_studs.push_back( stud );
				}
			}else
			{
				// The node doesn't have any children but as the maximal tree depth is already reached, it is not allowed
				// to add further children. Therefore this node has to add the brick itself
				m_studs.push_back( stud );
			}
		}
		return true;
	}else
	{
		// Brick not encompassed by this node, parent has to find other node to add the brick to
		return false;
	}
}

//--------------------------------------------------------------------------------------
// Remove a stud from the tree. If the removed stud was the only brick stored in a node,
// that node will be removed as well.
//--------------------------------------------------------------------------------------
bool LegoWorldNodeImplementation::RemoveStud( const IntVector3& deletePosition )
{
	std::vector<LegoStud>::iterator deleteIterator = std::find_if( m_studs.begin(), m_studs.end(), FindStudByPosition( deletePosition ) );

	if( deleteIterator != m_studs.end() )
	{
		m_studs.erase( deleteIterator );

		return true;
	}else
	{
		if( m_children.size() > 0 )
		{
			// try to delete the brick in the children, provided that one of them contains them
			bool deletedByChild = false;
			unsigned int i = 0;

			while( !deletedByChild && i < m_children.size() )
			{
				if( m_children[i].RemoveStud( deletePosition ) )
				{
					deletedByChild = true;
				}
				++i;
			}

			return deletedByChild;
		}else
		{
			// none of the children contains the brick to be deleted
			return false;
		}
	}
}

//--------------------------------------------------------------------------------------
// Returns true if the bounding box of this node fully encompasses the stud
//--------------------------------------------------------------------------------------
bool LegoWorldNodeImplementation::IsFullyEncompassingStud( const IntVector3& gridPosition )
{
	// todo: check if these comparisons are correct or one off
	return ( m_boundingBox[0].m_x <= gridPosition.m_x ) && ( (gridPosition.m_x + 1) <= m_boundingBox[1].m_x ) &&
		   ( m_boundingBox[0].m_y <= gridPosition.m_y ) && ( (gridPosition.m_y + 1) <= m_boundingBox[1].m_y ) &&
		   ( m_boundingBox[0].m_z <= gridPosition.m_z ) && ( (gridPosition.m_z + 1) <= m_boundingBox[1].m_z );
}

//--------------------------------------------------------------------------------------
// Returns true if the bounding box of this node fully encompasses the stud
//--------------------------------------------------------------------------------------
const LegoBrick* const LegoWorldNodeImplementation::GetLegoBrick( long id ) const
{
	std::vector<LegoBrick>::const_iterator brickIt = std::find_if( m_bricks.begin(), m_bricks.end(), FindBrickById( id ) );

	if( brickIt != m_bricks.end() )
	{
		return &(*brickIt);
	}else
	{
		if( m_children.size() > 0 )
		{
			bool foundByChild = false;
			const LegoBrick * brick = nullptr;
			unsigned int i = 0;

			while( !foundByChild && i < m_children.size() )
			{
				brick = m_children[i].GetLegoBrick( id );
				if( brick != nullptr )
				{
					foundByChild = true;
				}
				++i;
			}

			// is nullptr if not found in children, points to brick otherwise
			return brick;

		}else
		{
			return nullptr;
		}
	}
}