#ifndef _CSHADERUNIFORM_H_
#define _CSHADERUNIFORM_H_

#include "CObject.h"
#include "Param.h"

namespace glliba
{
	//////////////////////////////////////////////////////////////////////////////////////////////////////

	class CMaterial;

	class CShaderUniform : public CObject
	{
	protected:
		friend				CMaterial;

		SHADER_UNIFORM_TYPE	m_eShaderType;
		std::string			m_attribute;
		void*				m_uniformValue;

		void*				allocMemory( SHADER_UNIFORM_TYPE _type, void* _value);
	
	public:
		CShaderUniform();
		virtual				~CShaderUniform();

		void				setUniform( SHADER_UNIFORM_TYPE _type, const std::string& _attribute, void* _value );

	};

	//////////////////////////////////////////////////////////////////////////////////////////////////////
}

#endif