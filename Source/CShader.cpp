#include "CShader.h"
#include "CRender.h"
#include "CShaderManager.h"

namespace glliba
{
	//////////////////////////////////////////////////////////////////////////////////////////////////////

	CShader::CShader()
		: m_bEnable(true)
		, m_bIsActive(false)
		, m_uShaderID(0)

	{
		m_eTypeObject = OT_SHADER;
	}

	CShader::~CShader()
	{
		UniformList::iterator iter = m_uniformList.begin();
		while( m_uniformList.begin() !=  m_uniformList.end() )
		{
			CShaderUniform* uniform = iter->second;
			
			delete uniform;
			uniform = nullptr;

			++iter;
		}
		m_uniformList.clear();

		for (auto* ShaderProgram : m_shaderPrograms)
		{
			destroyShaderProgram(ShaderProgram);
		}
		m_shaderPrograms.clear();

		RENDERER->deleteShader(m_uShaderID);
		m_uShaderID = 0;
	}


	void CShader::getShaderIDArray( std::vector<uint>& _shadersId )
	{
		for ( uint i = 0; i < m_shaderPrograms.size(); ++i)
		{
			_shadersId.push_back(m_shaderPrograms[i]->getShaderProgramID());
		}
	}
	

	void CShader::setEnable( const bool _enable )
	{
		m_bEnable = _enable;
	}

	
	bool CShader::isEnable() const
	{
		return m_bEnable;
	}

	
	uint CShader::getShaderID() const
	{
		return m_uShaderID;
	}

	
	bool CShader::isExistAttribute( const std::string& _attribute )
	{
		UniformList::iterator iter = m_uniformList.begin();

		while (iter != m_uniformList.end())
		{
			if ( (*iter).first.compare(_attribute)  == 0 )
			{
				return true;
			}
			++iter;
		}
		return false;
	}


	void CShader::addShaderProgram( CShaderProgram* _shaderProgram )
	{
		if (_shaderProgram)
		{
			m_shaderPrograms.push_back(_shaderProgram);
		}
	}


	void CShader::destroyShaderProgram( CShaderProgram* _shaderProgram )
	{
		if (_shaderProgram)
		{
			auto shader = std::find(m_shaderPrograms.begin(),m_shaderPrograms.end(),_shaderProgram);
			if (shader == m_shaderPrograms.end())
			{
				ASSERT(false && "Shader Program not found");
				return;
			}

			SHADER_MGR->destroyShaderProgram(*shader);
		}
	}

	
	void CShader::setUniformInt( const std::string& _attribute, const int _value )
	{
		if ( isExistAttribute(_attribute) )
		{
			m_uniformList[_attribute]->setUniform( SUT_UNIFORM_INT, (_attribute), (void*)(&_value) );
		}
		else
		{
			CShaderUniform* uniform = new CShaderUniform();

			uniform->setUniform( SUT_UNIFORM_INT, (_attribute), (void*)(&_value) );
			m_uniformList[_attribute] = uniform;
		}
	}

		
	void CShader::setUniformFloat( const std::string& _attribute, const float _value )
	{
		if ( isExistAttribute(_attribute) )
		{
			m_uniformList[_attribute]->setUniform( SUT_UNIFORM_FLOAT, (_attribute), (void*)(&_value) );
		}
		else
		{
			CShaderUniform* uniform = new CShaderUniform();

			uniform->setUniform( SUT_UNIFORM_FLOAT, (_attribute), (void*)(&_value) );
			m_uniformList[_attribute] = uniform;
		}
	}

		
	void CShader::setUniformVector2( const std::string& _attribute, const Vector2 _vector )
	{
		if ( isExistAttribute(_attribute) )
		{
			m_uniformList[_attribute]->setUniform( SUT_UNIFORM_VECTOR2, (_attribute), (void*)(&_vector) );
		}
		else
		{
			CShaderUniform* uniform = new CShaderUniform();

			uniform->setUniform( SUT_UNIFORM_VECTOR2, (_attribute), (void*)(&_vector) );
			m_uniformList[_attribute] = uniform;
		}
	}

		
	void CShader::setUniformVector3( const std::string& _attribute, const Vector3 _vector )
	{
		if ( isExistAttribute(_attribute) )
		{
			m_uniformList[_attribute]->setUniform( SUT_UNIFORM_VECTOR3, (_attribute), (void*)(&_vector) );
		}
		else
		{
			CShaderUniform* uniform = new CShaderUniform();

			uniform->setUniform( SUT_UNIFORM_VECTOR3, (_attribute), (void*)(&_vector) );
			m_uniformList[_attribute] = uniform;
		}
	}

		
	void CShader::setUniformVector4( const std::string& _attribute, const Vector4 _vector )
	{
		if ( isExistAttribute(_attribute) )
		{
			m_uniformList[_attribute]->setUniform( SUT_UNIFORM_VECTOR4, (_attribute), (void*)(&_vector) );
		}
		else
		{
			CShaderUniform* uniform = new CShaderUniform();

			uniform->setUniform( SUT_UNIFORM_VECTOR4, (_attribute), (void*)(&_vector) );
			m_uniformList[_attribute] = uniform;
		}
	}

	
	void CShader::setUniformMatrix3( const std::string& _attribute, const Matrix3 _matrix )
	{
		if ( isExistAttribute(_attribute) )
		{
			m_uniformList[_attribute]->setUniform( SUT_UNIFORM_MATRIX3, (_attribute), (void*)(&_matrix) );
		}
		else
		{
			CShaderUniform* uniform = new CShaderUniform();

			uniform->setUniform( SUT_UNIFORM_MATRIX3, (_attribute), (void*)(&_matrix) );
			m_uniformList[_attribute] = uniform;
		}
	}

	
	void CShader::setUniformMatrix4( const std::string& _attribute, const Vector4 _matrix )
	{
		if ( isExistAttribute(_attribute) )
		{
			m_uniformList[_attribute]->setUniform( SUT_UNIFORM_MATRIX4, (_attribute), (void*)(&_matrix) );
		}
		else
		{
			CShaderUniform* uniform = new CShaderUniform();

			uniform->setUniform( SUT_UNIFORM_MATRIX4, (_attribute), (void*)(&_matrix) );
			m_uniformList[_attribute] = uniform;
		}
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////
}