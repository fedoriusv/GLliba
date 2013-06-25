#include "CShaderUniform.h"

namespace glliba
{
	//////////////////////////////////////////////////////////////////////////////////////////////////////

	CShaderUniform::CShaderUniform()
		: m_eShaderType(SUT_UNIFORM_INVALID)
		, m_attribute("")
		, m_uniformValue(NULL)
	{
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////

	CShaderUniform::~CShaderUniform()
	{
		if (m_uniformValue != NULL)
		{
			delete m_uniformValue;
			m_uniformValue = NULL;
		}
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////

	void CShaderUniform::setUniform( SHADER_UNIFORM_TYPE _type, std::string _attribute, void* _value )
	{
		m_eShaderType	= _type;
		m_attribute		= _attribute;
		m_uniformValue	= allocMemory(_type, _value);
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////

	void* CShaderUniform::allocMemory( SHADER_UNIFORM_TYPE _type,  void* _value )
	{
		if (m_uniformValue != NULL)
		{
			delete m_uniformValue;
			m_uniformValue = NULL;
		}

		void* uniformValue;

		switch(_type)
		{
		case SUT_UNIFORM_INT:
			{
				uniformValue = (int*)malloc(sizeof(int));
				memcpy(uniformValue, _value, sizeof(int));

				return uniformValue;
			}
		case SUT_UNIFORM_FLOAT:
			{
				uniformValue = (float*)malloc(sizeof(float));
				memcpy(uniformValue, _value, sizeof(float));

				return uniformValue;
			}
		case SUT_UNIFORM_VECTOR2:
			{
				uniformValue = (Vector2*)malloc(sizeof(Vector2));
				memcpy(uniformValue, _value, sizeof(Vector2));

				return uniformValue;
			}
		case SUT_UNIFORM_VECTOR3:
			{
				uniformValue = (Vector3*)malloc(sizeof(Vector3));
				memcpy(uniformValue, _value, sizeof(Vector3));

				return uniformValue;
			}
		case SUT_UNIFORM_VECTOR4:
			{
				uniformValue = (Vector4*)malloc(sizeof(Vector4));
				memcpy(uniformValue, _value, sizeof(Vector4));

				return uniformValue;
			}
		case SUT_UNIFORM_MATRIX3:
			{
				uniformValue = (Matrix3*)malloc(sizeof(Matrix3));
				memcpy(uniformValue, _value, sizeof(Matrix3));

				return uniformValue;
			}
		case SUT_UNIFORM_MATRIX4:
			{
				uniformValue = (Matrix4*)malloc(sizeof(Matrix4));
				memcpy(uniformValue, _value, sizeof(Matrix4));

				return uniformValue;
			}
		}

		return NULL;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////

}