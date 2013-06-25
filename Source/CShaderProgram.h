#ifndef _CSHADER_PROGRAM_H_ 
#define _CSHADER_PROGRAM_H_

#include "CObject.h"

namespace glliba
{

	////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	enum SHADER_PROGRAM_TYPE
	{
		SPT_UNKNOWN = 0,
		SPT_VERTEX,
		SPT_FRAGMENT,
	};

	////////////////////////////////////////////////////////////////////////////////////////////////////////

	class CShader;
	class CResourceManager;

	class CShaderProgram : public CObject
	{
	private:
		friend					CShader;
		friend					CResourceManager;

		uint					m_iShaderID;
		SHADER_PROGRAM_TYPE		m_eType;
		bool					m_CompileStatus;
		void*					m_shaderBody;

		std::string				m_shaderName;
		const char*				readShader( const std::string& _shaderFileName );
		void					clearShaderBody();

	public:

		CShaderProgram();
		virtual					~CShaderProgram();
		bool					loadShaderProgram( const std::string& _shaderFileName, SHADER_PROGRAM_TYPE _type );

		uint					getShaderID() const;
		SHADER_PROGRAM_TYPE		getShaderType() const;
		bool					getCompileStatus() const;

	};

	////////////////////////////////////////////////////////////////////////////////////////////////////////
}

#endif