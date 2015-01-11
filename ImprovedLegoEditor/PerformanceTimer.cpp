/* 
*  Kevin Meergans, Improved Lego Editor, 2014
*  PerformanceTimer.cpp
*  Contains the function definitions for the PerformanceTimer class. Calls to these
*  functions will be forwarded to the implementation part of the PerformanceTimer class
*  "PerformanceTimerImplementation".
*/

#include "PerformanceTimer.h"
#include "PerformanceTimerImplementation.h"

PerformanceTimer::PerformanceTimer() : m_pImplementation( new PerformanceTimerImplementation() )
{
}


HRESULT PerformanceTimer::Initialise( void )
{
	return m_pImplementation -> Initialise();
}

HRESULT PerformanceTimer::Cleanup( void )
{
	return m_pImplementation -> Cleanup();
}

void PerformanceTimer::Update( void )
{
	m_pImplementation -> Update();
}

const PerformanceData& PerformanceTimer::GetPerformanceData( void ) const
{
	return m_pImplementation -> GetPerformanceData();
}