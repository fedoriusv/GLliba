#include "CShaderManager.h"
#include "CShaderProgram.h"
#include "CRender.h"

#include <boost\bind.hpp>

namespace glliba
{
	//////////////////////////////////////////////////////////////////////////////////////////////

	CShaderManager::CShaderManager()
	{
	}


	CShaderManager::~CShaderManager()
	{
		for (auto& shader : m_shaders)
		{
			CShader* pShader = shader.second;

			delete pShader;
			pShader = nullptr;
		}
		m_shaders.clear();

		for (auto& shaderPog : m_shaderPrograms)
		{
			CShaderProgram* pShaderProg = shaderPog.second;

			delete pShaderProg;
			pShaderProg = nullptr;
		}
		m_shaderPrograms.clear();
	}


	bool CShaderManager::findShaderProgramByID( const ShaderProg& _shaderProg, uint _id )
	{
		return _shaderProg.second->getShaderProgramID() == _id;
	}


	bool CShaderManager::findShaderByID( const Shader& _shader, uint _id )
	{
		return _shader.second->getShaderID() == _id;
	}


	CShaderProgram* CShaderManager::createShaderProgram( 
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
		
		return (CShaderProgram*)newShaderProg->getRef();
	}


	void CShaderManager::destroyShaderProgram( CShaderProgram* _shaderProgram )
	{
		if ( _shaderProgram->releaseRef() == 0 )
		{
			auto shaderIter = std::find_if( m_shaderPrograms.begin(), m_shaderPrograms.end(),
				boost::bind(&CShaderManager::findShaderProgramByID,this,_1,_shaderProgram->getShaderProgramID()) );

			if (shaderIter != m_shaderPrograms.end())
			{
				CShaderProgram* shader = (*shaderIter).second;
				delete shader;
				shader = nullptr;

				m_shaderPrograms.erase(shaderIter);
			}
			else
			{
				ASSERT( false && "Shader not Found" );
			}
		}
	}

	
	void CShaderManager::transformString( std::string& _string, bool _toLower )
	{
		std::transform( _string.begin(), _string.end(), _string.begin(), _toLower ? ::tolower : ::toupper );
	}

	CShader* CShaderManager::createShader( const std::string& _vertShader, const std::string& _fragShader, uint _countArg, ... )
	{
		if ( _vertShader.empty() || _fragShader.empty() )
		{
			ASSERT( false && "Empty Shader FileName"  );
			return nullptr;
		}

		StringList nameList;
		nameList.push_back(_vertShader);
		nameList.push_back(_fragShader);

		va_list argList;
		va_start(argList, _countArg);
		for(uint i = 0; i < _countArg; i+=2)
		{
			char* strName = va_arg(argList, char*);
			int type = va_arg(argList, int);
			nameList.push_back(std::string(strName));
		}
		va_end(argList);


		CShader* shader = m_shaders[nameList];
		if (shader != nullptr)
		{
			return (CShader*)shader->getRef();
		}

		shader = new CShader();
				
		shader->addShaderProgram(SHADER_MGR->createShaderProgram(_vertShader, SPT_VERTEX  ));
		shader->addShaderProgram(SHADER_MGR->createShaderProgram(_fragShader, SPT_FRAGMENT));

		va_start(argList, _countArg);
		for(uint i = 0; i < _countArg; i+=2)
		{
			char* strName = va_arg(argList, char*);
			int type = va_arg(argList, int);

			shader->addShaderProgram(SHADER_MGR->createShaderProgram( strName, (SHADER_PROGRAM_TYPE)type ));
		}
		va_end(argList);

		
		std::vector<uint> _shadersId;
		shader->getShaderIDArray( _shadersId );
		
		RENDERER->initShader( shader->m_uShaderID, _shadersId );
		_shadersId.clear();

		m_shaders[nameList] = shader;
		return (CShader*)shader->getRef();
	}
	
	void CShaderManager::destroyShader( CShader* _shader )
	{
		if ( _shader->releaseRef() == 0 )
		{
			auto shaderIter = std::find_if( m_shaders.begin(), m_shaders.end(),
				boost::bind(&CShaderManager::findShaderByID,this,_1,_shader->getShaderID()) );

			if (shaderIter != m_shaders.end())
			{
				CShader* shader = (*shaderIter).second;
				delete shader;
				shader = nullptr;

				m_shaders.erase(shaderIter);
			}
			else
			{
				ASSERT( false && "Shader not Found" );
			}
		}
	}


	//////////////////////////////////////////////////////////////////////////////////////////////
}