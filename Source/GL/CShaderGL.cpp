#include "CShaderGL.h"
#include "CLogger.h"
#include <functional>

namespace glliba
{
	bool CShaderGL::intShaderProgramGL( uint& _shaderID, const uint _typeShader, void* _shaderBody )
	{
		_shaderID = glCreateShader( _typeShader == 1 ? GL_VERTEX_SHADER : GL_FRAGMENT_SHADER );
		
		GLchar* fsStringPtr[1];
		fsStringPtr[0] = (GLchar*)_shaderBody;
		glShaderSource( _shaderID, 1, (const GLchar**)fsStringPtr, NULL );

		glCompileShader( _shaderID );

		GLint testVal;
		glGetShaderiv( _shaderID, GL_COMPILE_STATUS, &testVal );
		ASSERT(testVal == GL_TRUE || "Invalid Shader Program");
#ifdef _DEBUG
		GLint length;
		GLchar buffer[1024];
		glGetShaderInfoLog(_shaderID, 1024, &length, buffer);
		if (strlen(buffer) > 0)
		{
			std::function<const char*(int)> strFunc = [](int _type) 
			{ 
				return _type == 1 ? "Vertex" : "Fragment"; 
			};

			LOG_CONSOLE("Shader Program "<< strFunc(_typeShader) 
				<< " id " << _shaderID << " :\n" << (const char*)buffer);
		}
#endif
		return (testVal == GL_TRUE) ? true : false;
	}


	void CShaderGL::initShaderGL( uint& _shaderID, std::vector<uint>& _shaderProgramID )
	{
		_shaderID = glCreateProgram();

		for ( uint i = 0; i < _shaderProgramID.size(); ++i )
		{
			glAttachShader( _shaderID, _shaderProgramID[i] );
		}
		
		glBindAttribLocation( _shaderID, GL_ATTRIBUTE_VERTEX,	"position" );
		glBindAttribLocation( _shaderID, GL_ATTRIBUTE_NORMAL,	"normal"   );
		glBindAttribLocation( _shaderID, GL_ATTRIBUTE_TEXTURE0,"texCoord0");

		glLinkProgram(_shaderID );
		glValidateProgram( _shaderID );

		GLint positionLocation = glGetAttribLocation(_shaderID, "position");
		ASSERT( positionLocation == GL_ATTRIBUTE_VERTEX && "Invalid attribute vertex Index" );
		GLint normalLocation =	glGetAttribLocation(_shaderID, "normal");
		//ASSERT( normalLocation == GL_ATTRIBUTE_NORMAL && "Invalid attribute normal Index" );
		GLint texCoord0Location = glGetAttribLocation(_shaderID, "texCoord0");
		//ASSERT( texCoord0Location == GL_ATTRIBUTE_TEXTURE0 && "Invalid attribute texCoord0 Index" );

#ifdef _DEBUG
		GLint testVal;
		GLint length;
		GLchar buffer[1024];
		glGetProgramiv( _shaderID, GL_LINK_STATUS, &testVal );
		ASSERT(testVal == GL_TRUE && "Invalid Shader");
		glGetProgramInfoLog( _shaderID, 1024, &length, buffer);
		if (strlen(buffer) > 0)
		{
			LOG_CONSOLE("Shader: " << (const char*)buffer);
		}
#endif
	}


	void CShaderGL::deleteShader( const uint _shaderID )
	{
		if ( _shaderID != 0 )
		{
			ASSERT(glIsShader( _shaderID ) || "Invalid Index Deleted Shader");
			glDeleteShader( _shaderID );
		}
	}
}