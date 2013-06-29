#ifndef _CSHADER_H_
#define _CSHADER_H_

#include "CObject.h"
#include "CShaderProgram.h"
#include "CShaderUniform.h"
#include "Types.h"

#define STR_SIMPLE_VERTEX_SHADER	"data/shaders/default.vsh"
#define STR_SIMPLE_FRAGMENT_SHADER	"data/shaders/default.psh"

namespace glliba
{
	//////////////////////////////////////////////////////////////////////////////////////////////////////

	class CMaterial;
	class CShaderManager;

	typedef std::map<std::string, CShaderUniform*>	UniformList;
	typedef std::pair<std::string, CShaderUniform*>	UniformUnit;
	typedef std::vector<CShaderProgram*>			ShaderPrograms;

	class CShader : public CObject
	{
	protected:
		friend				CMaterial;
		friend				CShaderManager;

		ShaderPrograms		m_shaderPrograms;

		uint				m_uShaderID;

		bool				m_bEnable;
		bool				m_bIsActive;

		UniformList			m_uniformList;

		bool				isExistAttribute( const std::string& _attribute ); 
		void				getShaderIDArray( std::vector<uint>& _shaderId );

		void				destroyShaderProgram( CShaderProgram* _shaderProgram );
		void				addShaderProgram( CShaderProgram* _shaderProgram );
	public:

		CShader();
		virtual				~CShader();
			
		void				setEnable( const bool _enable );
		bool				isEnable() const;

		uint				getShaderID() const;

		void				setUniformInt	 ( const std::string& _attribute, const int	 _value  );
		void				setUniformFloat	 ( const std::string& _attribute, const float   _value  );
		void				setUniformVector2( const std::string& _attribute, const Vector2 _vector );
		void				setUniformVector3( const std::string& _attribute, const Vector3 _vector );
		void				setUniformVector4( const std::string& _attribute, const Vector4 _vector );
		void				setUniformMatrix3( const std::string& _attribute, const Matrix3 _matrix );
		void				setUniformMatrix4( const std::string& _attribute, const Vector4 _matrix );

	};

	//////////////////////////////////////////////////////////////////////////////////////////////////////
}

#endif