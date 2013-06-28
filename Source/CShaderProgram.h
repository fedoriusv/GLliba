#ifndef _CSHADER_PROGRAM_H_ 
#define _CSHADER_PROGRAM_H_

#include "CObject.h"
#include "Param.h"

namespace glliba
{

	////////////////////////////////////////////////////////////////////////////////////////////////////////

	class CShader;
	class CResourceManager;

	class CShaderProgram : public CObject
	{
	private:
		friend					CShader;
		friend					CResourceManager;

		uint					m_uShaderProgramID;
		SHADER_PROGRAM_TYPE		m_eType;
		bool					m_bCompileStatus;
		void*					m_shaderBody;

		std::string				m_shaderName;
		const char*				readShader( const std::string& _shaderFileName );
		void					clearShaderBody();

	public:

		CShaderProgram();
		virtual					~CShaderProgram();
		bool					loadShaderProgram( const std::string& _shaderFileName, SHADER_PROGRAM_TYPE _type );

		uint					getShaderProgramID() const;
		SHADER_PROGRAM_TYPE		getShaderProgramType() const;
		bool					getCompileStatus() const;

	};

	////////////////////////////////////////////////////////////////////////////////////////////////////////
}

#endif