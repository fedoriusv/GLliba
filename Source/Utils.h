#pragma once

#ifndef _UTILS_H_
#define _UTILS_H_

#include "Types.h"

namespace glliba
{
	class Utils
	{
	public:
		inline static void transformString( std::string& _string, bool _toLower = true )
		{
			std::transform( _string.begin(), _string.end(), _string.begin(), _toLower ? ::tolower : ::toupper );
		}
	};
}

#endif