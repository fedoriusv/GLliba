#include "CShaderProgram.h"

#include "CRender.h"

namespace glliba
{
	////////////////////////////////////////////////////////////////////////////////////////////////////////

	CShaderProgram::CShaderProgram()
		: m_uShaderProgramID(0)
		, m_eType(SPT_UNKNOWN)
		, m_bCompileStatus(false)
		, m_shaderBody(NULL)
	{
		m_eTypeObject = OT_SHADER_PROGRAM;
	}

	
	CShaderProgram::~CShaderProgram()
	{
		clearShaderBody();
		
		RENDERER->deleteShader(m_uShaderProgramID);
		m_uShaderProgramID = 0;
	}

	
	uint CShaderProgram::getShaderProgramID() const
	{
		return m_uShaderProgramID;
	}

	
	SHADER_PROGRAM_TYPE CShaderProgram::getShaderProgramType() const
	{
		return m_eType;
	}

	
	bool CShaderProgram::getCompileStatus() const
	{
		return m_bCompileStatus;
	}

	
	const char* CShaderProgram::readShader( const std::string& _shaderFileName )
	{
		FILE* pFile;
		char* content = NULL;

		int count = 0;

		if ( !_shaderFileName.empty() )
		{
			fopen_s( &pFile, _shaderFileName.c_str(), "rt" );

			if (pFile != NULL)
			{
				fseek( pFile, 0, SEEK_END );
				count = ftell(pFile);
				rewind(pFile);

				if (count > 0) 
				{
					content = (char *)malloc(sizeof(char) * ( count+1 ));
					count = fread( content, sizeof(char), count, pFile );
					content[count] = '\0';
				}

				fclose(pFile);
			}
		}

		return content;
	}

	
	void CShaderProgram::clearShaderBody()
	{
		if (m_shaderBody != NULL)
		{
			delete m_shaderBody;
			m_shaderBody = NULL;
		}
	}

	
	bool CShaderProgram::loadShaderProgram( const std::string& _shaderFileName, SHADER_PROGRAM_TYPE _type )
	{
		m_shaderBody  = (void*)readShader( _shaderFileName );
		m_shaderName  = _shaderFileName;
		m_eType = _type;

		if (!m_shaderBody)
		{
			ASSERT( false && "Invalid Shader Program" );
			return false;
		}

		m_bCompileStatus = RENDERER->intShaderProgram( m_uShaderProgramID, m_eType, m_shaderBody );
		CShaderProgram::clearShaderBody();

		return true;
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////
}
