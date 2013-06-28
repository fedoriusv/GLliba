#ifndef _CSHADERGL_H_
#define _CSHADERGL_H_

#include "Types.h"
#include "Param.h"
#include <string>

namespace glliba
{
	class CShaderGL
	{
	public:

		static bool intShaderProgramGL( uint& _shaderID, const uint _typeShader, void* _shaderBody );
		static void initShaderGL( uint& _shaderID, std::vector<uint>& _shaderProgramID );

		static void deleteShader( const uint _shaderID );
	};
}

#endif