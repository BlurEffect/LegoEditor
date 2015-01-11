/* 
*  Kevin Meergans, Improved Lego Editor, 2014
*  LegoWorldNodeImplementation.h
*  Implementation part of the LegoWorldNode class.The public interface of this class
*  and the one of the LegoWorldNode class have to be kept consistent.
*/

#ifndef LEGO_WORLD_NODE_IMPLEMENTATION_H
#define LEGO_WORLD_NODE_IMPLEMENTATION_H

#include "Settings.h"
#include "CommonDataStructures.h"
#include <vector>
#include "LegoBrickData.h"
#include <windows.h>
#include <xnamath.h>
#include "RenderContext.h"
#include "LegoWorldNode.h"
#include <algorithm>
#include "Helpers.h"


class LegoWorldNodeImplementation
{
public:
	LegoWorldNodeImplementation( IntVector3 centre, IntVector3 size, int treeLevel );
	bool AddBrick( const LegoBrick& brick, const IntVector3& brickPositionOnGrid, const IntVector3& brickExtentsOnGrid );
	bool RemoveBrick( unsigned int deleteId, LegoBrickType& deleteType, IntVector3& deletePosition, int& deleteRotation );
	bool AddStud( const LegoStud& stud, const IntVector3& gridPosition );
	bool RemoveStud( const IntVector3& deletePosition );
	void SaveBricks(std::ofstream& out);
	void Clear( void );
	void UpdateVisibility( RenderContext* pRenderContext, const XMFLOAT4 frustumPlanes[6] );
	const LegoBrick* const GetLegoBrick( long id ) const;
private:
	bool IsFullyEncompassingBrick( const IntVector3& brickGridOrigin, const IntVector3& brickGridExtents );
	bool IsFullyEncompassingStud( const IntVector3& gridPosition );
	bool IsVisible( const XMFLOAT4 frustumPlanes[6] );

	std::vector<LegoWorldNode> m_children;		 // the children of this node, should be 8
	std::vector<LegoBrick>     m_bricks;		 // the bricks fully encompassed by this node's bounding box
	std::vector<LegoStud>      m_studs;
	IntVector3				   m_boundingBox[2]; // the bounding box of the node, contains minimal and maximal points
	IntVector3				   m_centre;		 // centre of the node/bounding box
	IntVector3                 m_size;           // size of the node/bounding box
	int						   m_treeLevel;		 // depth of this node into the tree

	// for faster calculations of visibility
	//XMFLOAT3				   m_actualCentre;	 // the centre of the node in actual coordinates, not in grid units
	//XMFLOAT3				   m_actualSize;	 // the actual size of the node, not in grid units
};


#endif