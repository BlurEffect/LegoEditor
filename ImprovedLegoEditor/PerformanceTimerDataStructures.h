/* 
*  Kevin Meergans, Improved Lego Editor, 2014
*  PerformanceTimerDataStructures.h
*  Contains data structures used by the performance timer and classes
*  requiring information on the performance of the application.
*/


#ifndef PERFORMANCE_TIMER_DATA_STRUCTURES_H
#define PERFORMANCE_TIMER_DATA_STRUCTURES_H

struct PerformanceData
{
	PerformanceData() : m_framesPerSecond( 0 ){}

	int m_framesPerSecond;
};

#endif