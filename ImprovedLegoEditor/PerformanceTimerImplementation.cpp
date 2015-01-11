/* 
*  Kevin Meergans, Improved Lego Editor, 2014
*  PerformanceTimerImplementation.cpp
*  Contains the function definitions for the PerformanceTimerImplementation class.
*/

# include "PerformanceTimerImplementation.h"


PerformanceTimerImplementation::PerformanceTimerImplementation() : m_frameCount( 0 ), 
																   m_startTime( 0 )
{
}

//--------------------------------------------------------------------------------------
// Initialise the performance counter.
//--------------------------------------------------------------------------------------
HRESULT PerformanceTimerImplementation::Initialise( void )
{
	m_startTime = timeGetTime();
	
	return S_OK;
}

//--------------------------------------------------------------------------------------
// Free any allocated resources.
//--------------------------------------------------------------------------------------
HRESULT PerformanceTimerImplementation::Cleanup( void )
{
	// at the moment more of a placeholder

	return S_OK;
}

//--------------------------------------------------------------------------------------
// Update the performance counter (game loop finished)
//--------------------------------------------------------------------------------------
void PerformanceTimerImplementation::Update( void )
{
	// update the frame count

	++m_frameCount;

	if( timeGetTime() >= ( m_startTime + 1000 ) )
	{
		m_performanceData.m_framesPerSecond = m_frameCount;
		m_frameCount = 0;
		
		m_startTime = timeGetTime();
	}
}

//--------------------------------------------------------------------------------------
// Returns a reference to a structure containing the bundled performance data.
//--------------------------------------------------------------------------------------
const PerformanceData& PerformanceTimerImplementation::GetPerformanceData( void ) const
{
	return m_performanceData;
}