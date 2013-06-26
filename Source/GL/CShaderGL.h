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

		static void intShaderProgramGL( uint& _shaderID, const uint _typeShader, void* _shaderBody );
		static void initShaderGL( uint& _shaderID, const uint _vertexShader, const uint _fragmentShader );

		static void bindShader( uint _shaderID );
		static bool setShaderUniform( SHADER_UNIFORM_TYPE _param, const uint _shaderID, const std::string& _attribute, void* _value );

		static void deleteShader( const uint _shaderID );
	};
}

#endif