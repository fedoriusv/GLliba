#ifndef _CTIMER_H_
#define _CTIMER_H_

#ifdef _WIN32   
#	include <windows.h>
#else     
#	include <sys/time.h>
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace gliba
{

	class CTimer
	{
	private:

		double			m_startTimeInMicroSec;                 
		double			m_endTimeInMicroSec;                   
		int				m_stopped;                             
#ifdef _WIN32
		LARGE_INTEGER	m_frequency;                    
		LARGE_INTEGER	m_startCount;                   
		LARGE_INTEGER	m_endCount;                     
#else
		timeval			m_startCount;                         
		timeval			m_endCount;                           
#endif

	public:
		CTimer();                                   
		~CTimer();                                  

		void   start();                             
		void   stop(); 

		double getElapsedTime();                    
		double getElapsedTimeInSec();               
		double getElapsedTimeInMilliSec();          
		double getElapsedTimeInMicroSec();          
	};

}

////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif
