#include "CShader.h"
#include "CRender.h"
#include "CShaderUniform.h"

namespace glliba
{
	//////////////////////////////////////////////////////////////////////////////////////////////////////

	CShader::CShader()
		: m_bEnable(true)
		, m_bIsActive(false)
		, m_iShaderID(0)

	{
		m_eTypeObject = OT_SHADER;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////

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

		RENDERER->deleteShader(m_iShaderID);
		m_iShaderID = 0;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////

	bool CShader::loadShader( const std::string& _vertShader, const std::string& _fragShader )
	{
		if ( _vertShader.empty() || _fragShader.empty() )
		{
			ASSERT( false && "Empty Shader FileName"  );
			return false;
		}

		m_vertexProgram.loadShaderProgram	( _vertShader, SPT_VERTEX	);
		m_fragmentProgram.loadShaderProgram	( _fragShader, SPT_FRAGMENT);

		if ( m_vertexProgram.m_shaderBody == NULL || m_fragmentProgram.m_shaderBody == NULL )
		{
			ASSERT( false && "Invalid Shader Read"  );
			return false;
		}

		RENDERER->initShader( m_iShaderID, m_vertexProgram.m_iShaderID, m_fragmentProgram.m_iShaderID );

		m_vertexProgram.clearShaderBody();
		m_fragmentProgram.clearShaderBody();
		
		return true;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////

	void CShader::setEnable( const bool _enable )
	{
		m_bEnable = _enable;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////

	bool CShader::isEnable() const
	{
		return m_bEnable;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////

	uint CShader::getShaderID() const
	{
		return m_iShaderID;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////

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

	//////////////////////////////////////////////////////////////////////////////////////////////////////

	void CShader::setUniformInt( const std::string& _attribute, const int _iValue )
	{
		if ( isExistAttribute(_attribute) )
		{
			m_uniformList[_attribute]->setUniform( SUT_UNIFORM_INT, (_attribute), (void*)(&_iValue) );
		}
		else
		{
			CShaderUniform* uniform = new CShaderUniform();

			uniform->setUniform( SUT_UNIFORM_INT, (_attribute), (void*)(&_iValue) );
			m_uniformList[_attribute] = uniform;
		}
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////
	
	void CShader::setUniformFloat( const std::string& _attribute, const float _fValue )
	{
		if ( isExistAttribute(_attribute) )
		{
			m_uniformList[_attribute]->setUniform( SUT_UNIFORM_FLOAT, (_attribute), (void*)(&_fValue) );
		}
		else
		{
			CShaderUniform* uniform = new CShaderUniform();

			uniform->setUniform( SUT_UNIFORM_FLOAT, (_attribute), (void*)(&_fValue) );
			m_uniformList[_attribute] = uniform;
		}
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////
	
	void CShader::setUniformVector2( const std::string& _attribute, const Vector2 _v2Vector )
	{
		if ( isExistAttribute(_attribute) )
		{
			m_uniformList[_attribute]->setUniform( SUT_UNIFORM_VECTOR2, (_attribute), (void*)(&_v2Vector) );
		}
		else
		{
			CShaderUniform* uniform = new CShaderUniform();

			uniform->setUniform( SUT_UNIFORM_VECTOR2, (_attribute), (void*)(&_v2Vector) );
			m_uniformList[_attribute] = uniform;
		}
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////
	
	void CShader::setUniformVector3( const std::string& _attribute, const Vector3 _v3Vector )
	{
		if ( isExistAttribute(_attribute) )
		{
			m_uniformList[_attribute]->setUniform( SUT_UNIFORM_VECTOR3, (_attribute), (void*)(&_v3Vector) );
		}
		else
		{
			CShaderUniform* uniform = new CShaderUniform();

			uniform->setUniform( SUT_UNIFORM_VECTOR3, (_attribute), (void*)(&_v3Vector) );
			m_uniformList[_attribute] = uniform;
		}
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////
	
	void CShader::setUniformVector4( const std::string& _attribute, const Vector4 _v4Vector )
	{
		if ( isExistAttribute(_attribute) )
		{
			m_uniformList[_attribute]->setUniform( SUT_UNIFORM_VECTOR4, (_attribute), (void*)(&_v4Vector) );
		}
		else
		{
			CShaderUniform* uniform = new CShaderUniform();

			uniform->setUniform( SUT_UNIFORM_VECTOR4, (_attribute), (void*)(&_v4Vector) );
			m_uniformList[_attribute] = uniform;
		}
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////

	void CShader::setUniformMatrix3( const std::string& _attribute, const Matrix3 _m3Matrix )
	{
		if ( isExistAttribute(_attribute) )
		{
			m_uniformList[_attribute]->setUniform( SUT_UNIFORM_MATRIX3, (_attribute), (void*)(&_m3Matrix) );
		}
		else
		{
			CShaderUniform* uniform = new CShaderUniform();

			uniform->setUniform( SUT_UNIFORM_MATRIX3, (_attribute), (void*)(&_m3Matrix) );
			m_uniformList[_attribute] = uniform;
		}
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////

	void CShader::setUniformMatrix4( const std::string& _attribute, const Vector4 _m4Matrix )
	{
		if ( isExistAttribute(_attribute) )
		{
			m_uniformList[_attribute]->setUniform( SUT_UNIFORM_MATRIX4, (_attribute), (void*)(&_m4Matrix) );
		}
		else
		{
			CShaderUniform* uniform = new CShaderUniform();

			uniform->setUniform( SUT_UNIFORM_MATRIX4, (_attribute), (void*)(&_m4Matrix) );
			m_uniformList[_attribute] = uniform;
		}
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////
}