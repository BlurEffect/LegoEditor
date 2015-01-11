/* 
*  Kevin Meergans, Improved Lego Editor, 2014
*  RenderContext.h
*  Gets passed down the octree representing the lego world and accumulates the data that should be rendered.
*/

#ifndef RENDER_CONTEXT_H
#define RENDER_CONTEXT_H

#include "LegoBrickData.h"
#include <memory>
#include <Windows.h>

// forward declaration
struct Instance;
class  RenderContextImplementation;
struct LegoStud;

class RenderContext
{
public:
	RenderContext( void );

	HRESULT Initialise( void );
	HRESULT Cleanup( void );

	bool AddBrick( const LegoBrick& brick );
	bool AddStud( const LegoStud& stud );


	void Reset( void );
	int  GetInstanceCount( LegoBrickType type ) const;

	const Instance* const GetInstances( LegoBrickType type ) const;

	int GetStudInstanceCount( void ) const;
	const Instance* const GetStudInstances( void ) const;

private:
	std::tr1::shared_ptr<RenderContextImplementation> m_pImplementation;
};

#endif