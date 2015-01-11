/* 
*  Kevin Meergans, Improved Lego Editor, 2014
*  RenderContext.cpp
*  Contains the function definitions for the RenderContext class. Calls to these
*  functions will be forwarded to the implementation part of the RenderContext class
*  "RenderContextImplementation".
*/

#include "RenderContext.h"
#include "RenderContextImplementation.h"

RenderContext::RenderContext() : m_pImplementation( new RenderContextImplementation() )
{
}

HRESULT RenderContext::Initialise( void )
{
	return m_pImplementation -> Initialise();
}

HRESULT RenderContext::Cleanup( void )
{
	return m_pImplementation -> Cleanup();
}

bool RenderContext::AddBrick( const LegoBrick& brick )
{
	return m_pImplementation -> AddBrick( brick );
}

bool RenderContext::AddStud( const LegoStud& stud )
{
	return m_pImplementation -> AddStud( stud );
}

void RenderContext::Reset( void )
{
	m_pImplementation -> Reset();
}

int  RenderContext::GetInstanceCount( LegoBrickType type ) const
{
	return m_pImplementation -> GetInstanceCount( type );
}

const Instance* const RenderContext::GetInstances( LegoBrickType type ) const
{
	return m_pImplementation -> GetInstances( type );
}

int RenderContext::GetStudInstanceCount() const
{
	return m_pImplementation -> GetStudInstanceCount();
}

const Instance* const RenderContext::GetStudInstances() const
{
	return m_pImplementation -> GetStudInstances();
}


