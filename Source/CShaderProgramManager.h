#ifndef _C_SHADERMANAGER_H_
#define _C_SHADERMANAGER_H_

#include "CSingleton.h"
#include "Types.h"
#include "Param.h"
#include "CShader.h"

namespace glliba
{
	//////////////////////////////////////////////////////////////////////////////////////////////
	class CShaderProgram;

	typedef std::map<const std::string, CShaderProgram*>	ShaderProgList;
	typedef std::pair<const std::string, CShaderProgram*>	ShaderProgram;

	class CShaderProgramManager : public CSingleton<CShaderProgramManager>
	{
	private:

		uint				m_nCountRes;
		ShaderProgList		m_shaderPrograms;

		bool				findShaderProgramByID( const ShaderProgram& _shaderProg, uint _id );

	public:
		CShaderProgramManager();
		virtual				~CShaderProgramManager();
		
		CShaderProgram*		createShaderProgram( const std::string& _shaderFile, SHADER_PROGRAM_TYPE _shaderType );
		void				destroyShaderProgram( CShaderProgram* _shaderProgram );

		void				transformString( std::string& _string, bool _toLower = true );
	};

	//////////////////////////////////////////////////////////////////////////////////////////////

#define SHADER_MGR	CShaderProgramManager::getInstance()

	//////////////////////////////////////////////////////////////////////////////////////////////
};

#endif