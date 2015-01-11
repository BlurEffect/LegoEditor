/* 
*  Kevin Meergans, Improved Lego Editor, 2014
*  PerformanceTimer.h
*  Used to measure several stats of the application such as the framerate.
*/

#ifndef PERFORMANCE_TIMER_H
#define PERFORMANCE_TIMER_H

#include <windows.h>
#include <memory>

// forward declaration
class PerformanceTimerImplementation;
struct PerformanceData;

class PerformanceTimer
{
public:
	PerformanceTimer( void );
	HRESULT Initialise( void );
	HRESULT Cleanup( void );
	void	Update( void );
	const PerformanceData& PerformanceTimer::GetPerformanceData( void ) const;
private:
	std::tr1::shared_ptr<PerformanceTimerImplementation> m_pImplementation;
};

#endif