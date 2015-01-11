/* 
*  Kevin Meergans, Improved Lego Editor, 2014
*  RenderContextImplementation.h
*  Implementation part of the RenderContext class.The public interface of this class
*  and the one of the RenderContext class have to be kept consistent.
*/

#ifndef RENDER_CONTEXT_IMPLEMENTATION_H
#define RENDER_CONTEXT_IMPLEMENTATION_H

#include "MeshDataStructures.h"
#include "LegoBrickData.h"

class RenderContextImplementation
{
public:
	RenderContextImplementation( void );

	HRESULT Initialise( void );
	HRESULT Cleanup( void );

	bool AddBrick( const LegoBrick& brick );
	bool AddStud( const LegoStud& stud );

	void Reset( void );

	int GetInstanceCount( LegoBrickType type ) const;
	const Instance* const GetInstances( LegoBrickType type ) const;

	int GetStudInstanceCount( void ) const;
	const Instance* const GetStudInstances( void ) const;

private:
	
	int m_instanceCounts[NumberOfBrickTypes];							 // Keep track of how many instances of each brick type are to be rendered
	Instance m_instances[NumberOfBrickTypes][NUMBER_OF_BRICKS_PER_TYPE]; // The instances to be drawn for every brick type. Bucket sort 
	int m_studInstanceCount;
	Instance m_studInstances[NUMBER_OF_STUDS];
};

#endif