#include "CTimer.h"
#include <stdlib.h>

namespace gliba
{
	////////////////////////////////////////////////////////////////////////////////////////////////////////

	CTimer::CTimer()
	{
#ifdef _WIN32
		QueryPerformanceFrequency(&m_frequency);
		m_startCount.QuadPart = 0;
		m_endCount.QuadPart = 0;
#else
		m_startCount.tv_sec = m_startCount.tv_usec = 0;
		m_endCount.tv_sec = m_endCount.tv_usec = 0;
#endif
		m_stopped = 0;
		m_startTimeInMicroSec = 0;
		m_endTimeInMicroSec = 0;
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////

	CTimer::~CTimer()
	{
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////

	void CTimer::start()
	{
		m_stopped = 0; // reset stop flag
#ifdef _WIN32
		QueryPerformanceCounter(&m_startCount);
#else
		gettimeofday(&m_startCount, NULL);
#endif
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////

	void CTimer::stop()
	{
		m_stopped = 1; // set timer stopped flag
#ifdef WIN32
		QueryPerformanceCounter(&m_endCount);
#else
		gettimeofday(&m_endCount, NULL);
#endif
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////

	double CTimer::getElapsedTimeInMicroSec()
	{
#ifdef WIN32
		if(!m_stopped)
			QueryPerformanceCounter(&m_endCount);

		m_startTimeInMicroSec = m_startCount.QuadPart * (1000000.0 / m_frequency.QuadPart);
		m_endTimeInMicroSec = m_endCount.QuadPart * (1000000.0 / m_frequency.QuadPart);
#else
		if(!m_stopped)
			gettimeofday(&m_endCount, NULL);

		m_startTimeInMicroSec = (m_startCount.tv_sec * 1000000.0) + m_startCount.tv_usec;
		m_endTimeInMicroSec = (m_endCount.tv_sec * 1000000.0) + m_endCount.tv_usec;
#endif
		return m_endTimeInMicroSec - m_startTimeInMicroSec;
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////

	double CTimer::getElapsedTimeInMilliSec()
	{
		return getElapsedTimeInMicroSec() * 0.001;
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////

	double CTimer::getElapsedTimeInSec()
	{
		return getElapsedTimeInMicroSec() * 0.000001;
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////

	double CTimer::getElapsedTime()
	{
		return getElapsedTimeInSec();
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////

}