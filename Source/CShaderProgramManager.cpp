#include "CShaderProgramManager.h"
#include "CShaderProgram.h"

#include <boost\bind.hpp>

namespace glliba
{
	//////////////////////////////////////////////////////////////////////////////////////////////

	CShaderProgramManager::CShaderProgramManager()
		: m_nCountRes(0)
	{
	}


	CShaderProgramManager::~CShaderProgramManager()
	{
		for (auto& shader : m_shaderPrograms)
		{
			CShaderProgram* shaderProg = shader.second;

			delete shaderProg;
			shaderProg = nullptr;
		}
		m_shaderPrograms.clear();
		m_nCountRes = 0;
	}


	bool CShaderProgramManager::findShaderProgramByID( const ShaderProgram& _shaderProg, uint _id )
	{
		return _shaderProg.second->getShaderProgramID() == _id;
	}


	CShaderProgram* CShaderProgramManager::createShaderProgram( 
		const std::string& _shaderFile, SHADER_PROGRAM_TYPE _shaderType )
	{
		CShaderProgram* shaderProg = m_shaderPrograms[_shaderFile];

		if (shaderProg != nullptr)
		{
			return (CShaderProgram*)shaderProg->getRef();
		}

		CShaderProgram* newShaderProg = new CShaderProgram();
		newShaderProg->loadShaderProgram( _shaderFile, _shaderType );

		m_shaderPrograms[_shaderFile] = newShaderProg;
		++m_nCountRes;
		
		return (CShaderProgram*)newShaderProg->getRef();
	}


	void CShaderProgramManager::destroyShaderProgram( CShaderProgram* _shaderProgram )
	{
		if ( _shaderProgram->releaseRef() == 0 )
		{
			auto shaderIter = std::find_if( m_shaderPrograms.begin(), m_shaderPrograms.end(),
				boost::bind(&CShaderProgramManager::findShaderProgramByID,this,_1,_shaderProgram->getShaderProgramID()) );

			if (shaderIter != m_shaderPrograms.end())
			{
				CShaderProgram* shader = (*shaderIter).second;
				delete shader;
				shader = nullptr;

				m_shaderPrograms.erase(shaderIter);
				--m_nCountRes;
			}
			else
			{
				ASSERT( false && "Shader not Found" );
			}
		}
	}

	
	void CShaderProgramManager::transformString( std::string& _string, bool _toLower )
	{
		std::transform( _string.begin(), _string.end(), _string.begin(), _toLower ? ::tolower : ::toupper );
	}

	//////////////////////////////////////////////////////////////////////////////////////////////
}