/* 
*  Kevin Meergans, Improved Lego Editor, 2014
*  LegoWorldNode.h
*  Part of the octree space partitioning used for the lego world. Each node is an axis aligned bounding
*  volume that contains bricks that are fully enclosed in it. 
	// todo: add more description
*/

#ifndef LEGO_WORLD_NODE_H
#define LEGO_WORLD_NODE_H

#include "CommonDataStructures.h"
#include <memory>
#include <windows.h>
#include <xnamath.h>
#include <fstream>

// forward declaration
class LegoWorldNodeImplementation;
class RenderContext;
enum LegoBrickType;
struct LegoBrick;
struct LegoStud;

class LegoWorldNode
{
public:
	LegoWorldNode( IntVector3 centre, IntVector3 size, int treeLevel );

	bool AddBrick( const LegoBrick& brick, const IntVector3& brickPositionOnGrid, const IntVector3& brickExtentsOnGrid );
	bool RemoveBrick( unsigned int deleteId, LegoBrickType& deleteType, IntVector3& deletePosition, int& deleteRotation );
	bool AddStud( const LegoStud& stud, const IntVector3& gridPosition );
	bool RemoveStud( const IntVector3& deletePosition );
	void SaveBricks(std::ofstream& out);
	void Clear( void );
	void UpdateVisibility( RenderContext* pRenderContext, const XMFLOAT4 frustumPlanes[6] );
	const LegoBrick* const GetLegoBrick( long id ) const;
private:
	std::tr1::shared_ptr<LegoWorldNodeImplementation> m_pImplementation;
};


#endif