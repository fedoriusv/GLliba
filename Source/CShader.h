#ifndef _CSHADER_H_
#define _CSHADER_H_

#include "CShaderProgram.h"

#define STR_SIMPLE_VERTEX_SHADER	"data/default.vsh"
#define STR_SIMPLE_FRAGMENT_SHADER	"data/default.psh"

namespace glliba
{
	//////////////////////////////////////////////////////////////////////////////////////////////////////
	class CMaterial;
	class CResourceManager;
	class CShaderProgram;
	class CShaderUniform;

	typedef std::map<std::string, CShaderUniform*>	UniformList;
	typedef std::pair<std::string, CShaderUniform*>	UniformUnit; 

	class CShader : public CObject
	{

	protected:
		friend			CMaterial;
		friend			CResourceManager;

		CShaderProgram	m_vertexProgram;
		CShaderProgram	m_fragmentProgram;

		uint			m_iShaderID;

		bool			m_bEnable;
		bool			m_bIsActive;

		UniformList		m_uniformList;

		bool			isExistAttribute( const std::string& _attribute ); 

	public:
		CShader();
		virtual			~CShader();
			
		void			setEnable( const bool _enable );
		bool			isEnable() const;

		uint			getShaderID() const;

		void			setUniformInt	 ( const std::string& _attribute, const int	 _value  );
		void			setUniformFloat	 ( const std::string& _attribute, const float   _value  );
		void			setUniformVector2( const std::string& _attribute, const Vector2 _vector );
		void			setUniformVector3( const std::string& _attribute, const Vector3 _vector );
		void			setUniformVector4( const std::string& _attribute, const Vector4 _vector );
		void			setUniformMatrix3( const std::string& _attribute, const Matrix3 _matrix );
		void			setUniformMatrix4( const std::string& _attribute, const Vector4 _matrix );

		bool			loadShader( const std::string& _vertShader, const std::string& _fragShader );
	};

	//////////////////////////////////////////////////////////////////////////////////////////////////////
}

#endif