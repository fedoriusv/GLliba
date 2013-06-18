#ifndef _CSHADERUNIFORM_H_
#define _CSHADERUNIFORM_H_

#include "CObject.h"

namespace glliba
{
	//////////////////////////////////////////////////////////////////////////////////////////////////////

	enum SHADER_UNIFORM_TYPE
	{
		SUT_UNIFORM_INVALID,
		SUT_UNIFORM_INT,
		SUT_UNIFORM_FLOAT,
		SUT_UNIFORM_VECTOR2,
		SUT_UNIFORM_VECTOR3,
		SUT_UNIFORM_VECTOR4,
		SUT_UNIFORM_MATRIX3,
		SUT_UNIFORM_MATRIX4,
		 
		SUT_COUNT,
	};

	//////////////////////////////////////////////////////////////////////////////////////////////////////

	class CMaterial;

	class CShaderUniform : public CObject
	{
	protected:
		friend				CMaterial;

		SHADER_UNIFORM_TYPE	m_eShaderType;
		std::string			m_attribute;
		void*				m_uniformValue;

		void*				allocMemory( SHADER_UNIFORM_TYPE _eType,  void* _value);
	
	public:
		CShaderUniform();
		virtual			~CShaderUniform();

		void			setUniform( SHADER_UNIFORM_TYPE _eType, std::string _attribute, void* _value );

	};

	//////////////////////////////////////////////////////////////////////////////////////////////////////
}

#endif