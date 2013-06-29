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
	typedef std::pair<const std::string, CShaderProgram*>	ShaderProg;
	typedef std::map<StringList, CShader*>					ShaderList;
	typedef std::pair<StringList, CShader*>					Shader;


	class CShaderManager : public CSingleton<CShaderManager>
	{
	private:

		ShaderList			m_shaders;
		ShaderProgList		m_shaderPrograms;

		bool				findShaderProgramByID( const ShaderProg& _shaderProg, uint _id );
		bool				findShaderByID( const Shader& _shader, uint _id );

	public:
		CShaderManager();
		virtual				~CShaderManager();
		
		CShaderProgram*		createShaderProgram( const std::string& _shaderFile, SHADER_PROGRAM_TYPE _shaderType );
		void				destroyShaderProgram( CShaderProgram* _shaderProgram );

		CShader*			createShader( const std::string& _vertShader, const std::string& _fragShader, uint _countArg = 0, ... );
		void				destroyShader( CShader* _shader );

		void				transformString( std::string& _string, bool _toLower = true );
	};

	//////////////////////////////////////////////////////////////////////////////////////////////

#define SHADER_MGR	CShaderManager::getInstance()

	//////////////////////////////////////////////////////////////////////////////////////////////
};

#endif