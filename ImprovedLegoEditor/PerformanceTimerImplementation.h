/* 
*  Kevin Meergans, Improved Lego Editor, 2014
*  PerformanceTimerImplementation.h
*  Implementation part of the PerformanceTimer class.The public interface of this class
*  and the one of the PerformanceTimer class have to be kept consistent. 
*/


#ifndef PERFORMANCE_TIMER_IMPLEMENTATION_H
#define PERFORMANCE_TIMER_IMPLEMENTATION_H

#include <windows.h>
#include <mmsystem.h>
#include "PerformanceTimerDataStructures.h"

class PerformanceTimerImplementation
{
public:
	PerformanceTimerImplementation( void );
	HRESULT Initialise( void );
	HRESULT Cleanup( void );
	void	Update( void );
	const PerformanceData& GetPerformanceData( void ) const;
private:
	int			    m_frameCount;
	unsigned long   m_startTime;
	PerformanceData m_performanceData;
};

#endif
