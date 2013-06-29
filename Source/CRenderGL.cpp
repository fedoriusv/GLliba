#include "CRenderGL.h"

#include "GL\CVertexBufferGL.h"
#include "GL\CShaderGL.h"

#include "CTimer.h"
#include "CLight.h"
#include "CFog.h"
#include "CTexture.h"
#include "CMaterial.h"
#include "CNode.h"
#include "Param.h"

#include <iostream>
#include <sstream>

namespace glliba
{
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	GLenum CUBE_MAP[TEXTURE_CUBE_MAP_COUNT] =
	{
		GL_TEXTURE_CUBE_MAP_POSITIVE_X,
		GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
		GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
		GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
		GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
		GL_TEXTURE_CUBE_MAP_NEGATIVE_Z
	};

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	CRenderGL::CRenderGL()
		: m_iMaxTextureUnits(1U)
		, m_iCurrentShader(0U)

		, m_projectionMatrix(Matrix4::identity())
		, m_viewMatrix(Matrix4::identity())
		, m_viewPosition(Vector3(0.0f))
	{
		LOG_CONSOLE("Init OpenGL driver ");
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	CRenderGL::~CRenderGL()
	{
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	CRender* CRenderGL::getInstance()
	{
		if (!s_pRender)
		{
			s_pRender = new CRenderGL();
		}

		return s_pRender;
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	void CRenderGL::printOpenGLInfo()
	{
		const char *szVendorString = (const char *)glGetString(GL_VENDOR);
		LOG_CONSOLE( "OpenGL vendor " << szVendorString );
		const char *szRendererString = (const char *)glGetString(GL_RENDERER);
		LOG_CONSOLE( "OpenGL renderer " << szRendererString );
		const char *szGLSLString = (const char *)glGetString(GL_SHADING_LANGUAGE_VERSION);
		LOG_CONSOLE( "GLSL version " << szGLSLString );
		const char *szVersionString = (const char *)glGetString(GL_VERSION);
		LOG_CONSOLE( "OpenGL version " << szVersionString << '\n' );

		ASSERT(glewIsSupported("GL_ARB_multitexture") && "Multitexture not supported");
		LOG_CONSOLE( "Multitexture supported" );
		
		ASSERT(glewIsSupported("GL_ARB_vertex_buffer_object") && "Vertex Buffer not supported");
		LOG_CONSOLE( "Vertex Buffer supported" );

		ASSERT(glewIsSupported("GL_ARB_vertex_array_object") && "Array Buffer not supported");
		LOG_CONSOLE( "Array Buffer supported" );

		ASSERT(glewIsSupported("GL_ARB_sampler_objects") && "Sampler object not supported");
		LOG_CONSOLE( "Sampler object supported" << '\n' );
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	void CRenderGL::printOpenGLError( const std::string& _errorString )
	{
#ifdef _DEBUG
		GLenum error = glGetError();
		if ( error != GL_NO_ERROR )
		{
			LOG_CONSOLE( _errorString << glewGetErrorString(error));
		}
#endif
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	bool CRenderGL::init( void* _hWnd )
	{
		HWND hWnd = (HWND)_hWnd;
		printOpenGLInfo();
				
#ifdef _USE_DEVIL
		ilInit();
		LOG_CONSOLE( "Initialize DevIl lib\n");
#endif

		RECT rect;
		GetClientRect(hWnd,&rect);
		reshape( rect.right, rect.bottom );
		
		glGetIntegerv( GL_MAX_TEXTURE_UNITS, &m_iMaxTextureUnits );
		glEnable(GL_MULTISAMPLE);

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		
		//glEnable(GL_DEPTH);
		glEnable(GL_DEPTH_TEST);
		glClearDepth(1.0f);
		//glDepthFunc(GL_LEQUAL);	
		//glShadeModel(GL_SMOOTH);

		glDisable(GL_CULL_FACE);
		//glEnable(GL_CULL_FACE);
		glFrontFace(GL_CW);
		
		
		//glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		printOpenGLError( "GLError Init GL: ");
		return true;
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	void CRenderGL::reshape( uint _iWidth, uint _iHeight )
	{
		if ( _iHeight == 0 )
		{
			_iHeight = 1;
		}
		m_iScreenWidth = _iWidth;
		m_iScreenHeight = _iHeight;

		glViewport( 0, 0, m_iScreenWidth, m_iScreenHeight );

		GLfloat aspectRatio = (GLfloat)m_iScreenWidth/(GLfloat)m_iScreenHeight;
		m_projectionMatrix =  Vectormath::transpose(Matrix4::perspectiveDegree( 45.0f, aspectRatio, 0.1f, 100.0f ));
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	void CRenderGL::beginRender()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	
		glClearColor(m_backColor[0], m_backColor[1], m_backColor[2], 0.0f);
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	void CRenderGL::endRender()
	{
#ifdef _DEBUG
		GLenum error = glGetError();
		if (error != GL_NO_ERROR )
		{
			LOG_CONSOLE( "GLError: " << glewGetErrorString(error));
			LOG_CONSOLE( "WinError: " << GetLastError());
		}
#endif

		glFlush();
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	void CRenderGL::initSampler( uint&	_iSamplerID, WRAP_TYPE _eWrapType,
		FILTER_TYPE _eMinFilerType, FILTER_TYPE	_eMagFilerType )
	{
		glGenSamplers(1, &_iSamplerID);
		
		glSamplerParameteri( _iSamplerID, GL_TEXTURE_WRAP_S,	_eWrapType);
		glSamplerParameteri( _iSamplerID, GL_TEXTURE_WRAP_T,	_eWrapType);
		glSamplerParameteri( _iSamplerID, GL_TEXTURE_WRAP_R,	_eWrapType);
		glSamplerParameteri( _iSamplerID, GL_TEXTURE_MAG_FILTER,_eMagFilerType );
		glSamplerParameteri( _iSamplerID, GL_TEXTURE_MIN_FILTER,_eMinFilerType );
		
		if (glewIsSupported("GL_EXT_texture_filter_anisotropic"))
		{
			GLfloat fLargest;
			glGetFloatv( GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &fLargest) ;
			glSamplerParameterf(_iSamplerID, GL_TEXTURE_MAX_ANISOTROPY_EXT, fLargest);
		}

		glBindSampler(0, _iSamplerID);

		printOpenGLError( "GLError init Sampler: ");
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	void CRenderGL::initTexture2D( uint& _iTextureID, const STextureData2D& _sTextureData, const bool _bMipMap )
	{
		glGenTextures(1, &_iTextureID);
		glBindTexture( GL_TEXTURE_2D, _iTextureID );
		ASSERT(glIsTexture(_iTextureID ) || "Invalid texture index");

		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		
		glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, _sTextureData._iWidth, _sTextureData._iHeight,
			0, _sTextureData._eFormat, _sTextureData._eType, _sTextureData._data );

		if (_bMipMap)
		{
			glGenerateMipmap( GL_TEXTURE_2D );
		}

		glBindTexture(GL_TEXTURE_2D, 0);

		printOpenGLError( "GLError init Texture2D: ");
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	void CRenderGL::initTextureCubeMap( uint& _iTextureID, const STextureData2D* _sTextureData, const bool _bMipMap )
	{
		glGenTextures( 1, &_iTextureID );
		glBindTexture( GL_TEXTURE_CUBE_MAP, _iTextureID );
		ASSERT(glIsTexture( _iTextureID ) || "Invalid texture index");

		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

		for (uint i = 0; i < TEXTURE_CUBE_MAP_COUNT; ++i )
		{
			glTexImage2D( CUBE_MAP[i], 0, GL_RGB, _sTextureData[i]._iWidth, _sTextureData[i]._iHeight,
				0, _sTextureData[i]._eFormat, _sTextureData[i]._eType, _sTextureData[i]._data );
		}

		if (_bMipMap)
		{
			glGenerateMipmap( GL_TEXTURE_CUBE_MAP );
		}

		glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

		printOpenGLError( "GLError init CubeMap: ");
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	void CRenderGL::initRenderTarget( uint& _iFrameBuffID, uint& _itextireID, uint _iWidth, uint _iHeight )
	{
		glGenTextures( 1, &_itextireID );
		glBindTexture( GL_TEXTURE_2D, _itextireID );
		ASSERT(glIsTexture(_itextireID ) || "Invalid texture index");

		//glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, _iWidth, _iHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL );
		glTexImage2D( GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, _iWidth, _iHeight, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, NULL );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE); 
		glBindTexture(GL_TEXTURE_2D, 0);

		/*if (int a == GL_DEPTH_COMPONENT)
		{
		glDrawBuffer(GL_NONE);
		glReadBuffer(GL_NONE);
		}*/

		glGenFramebuffers(1, &_iFrameBuffID);
		glBindFramebuffer(GL_FRAMEBUFFER, _iFrameBuffID);
		ASSERT(glIsFramebuffer(_iFrameBuffID ) || "Invalid framebuffer index");

		//glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _iFrameBuffID, 0);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, _iFrameBuffID, 0);
		GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
		if(status != GL_FRAMEBUFFER_COMPLETE)
		{
			ASSERT(false || "Error in framebuffer created");
		}
		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		/*GLuint rboId;
		glGenRenderbuffers(1, &rboId);
		glBindRenderbuffer(GL_RENDERBUFFER, rboId);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, _iWidth, _iHeight);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rboId);
		glBindRenderbuffer(GL_RENDERBUFFER, 0);*/

	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	void CRenderGL::renderToTexture( uint _id, uint __texId)
	{
		if (_id != 0)
		{
			//glBindRenderbuffer(GL_RENDERBUFFER, 1);

			glBindFramebuffer(GL_FRAMEBUFFER, _id);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glClearColor(1,1,1,1.0f);
			glEnable(GL_DEPTH_TEST);
			glEnable(GL_CULL_FACE);
			//glDisable(GL_DEPTH);



		}
		else
		{
			//glBindRenderbuffer(GL_RENDERBUFFER, 0);
			glBindFramebuffer(GL_FRAMEBUFFER, 0);

			glBindTexture(GL_TEXTURE_2D, __texId);
			glGenerateMipmap(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, 0);
			//glEnable(GL_DEPTH);
		}

	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	void CRenderGL::deleteSampler( const uint _iSamplerID )
	{
		if ( _iSamplerID != 0 )
		{
			ASSERT(glIsShader( _iSamplerID ) || "Invalid Index Sampler");
			glDeleteSamplers( 1, &_iSamplerID );
		}
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	void CRenderGL::deleteTexture( const uint _iTextureID )
	{
		if ( _iTextureID != 0 )
		{
			ASSERT(glIsShader( _iTextureID ) || "Invalid Index Texture");
			glDeleteTextures( 1, &_iTextureID );
		}
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	void CRenderGL::deleteShader( const uint _shaderID )
	{
		CShaderGL::deleteShader(_shaderID);
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	void CRenderGL::deleteBufferObjects( SVertexData& _vertexData )
	{
		CVertexBufferGL::deleteBufferObjectsGL(_vertexData);
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	void CRenderGL::initBufferObjects( SVertexData& _vertexData )
	{
		CVertexBufferGL::initBufferObjectsGL(_vertexData);

		printOpenGLError("GLError init VBO: ");
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	void CRenderGL::updateSampler( uint& _iSamplerID, const WRAP_TYPE _eWrapType,
		const FILTER_TYPE _eMinFilerType, const FILTER_TYPE	_eMagFilerType )
	{
		glBindSampler( 0, _iSamplerID );

		glSamplerParameteri( _iSamplerID, GL_TEXTURE_WRAP_S,	_eWrapType		);
		glSamplerParameteri( _iSamplerID, GL_TEXTURE_WRAP_T,	_eWrapType		);
		glSamplerParameteri( _iSamplerID, GL_TEXTURE_WRAP_R,	_eWrapType		);
		glSamplerParameteri( _iSamplerID, GL_TEXTURE_MAG_FILTER,_eMagFilerType	);
		glSamplerParameteri( _iSamplerID, GL_TEXTURE_MIN_FILTER,_eMinFilerType	);

		printOpenGLError("GLError Update Simpler: ");
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	void CRenderGL::updateBufferObject( SVertexData& _vertexData )
	{
		CVertexBufferGL::updateBufferObjectGL(_vertexData);

		printOpenGLError("GLError update VBO: ");
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	void bindBlend( bool _transparent )
	{
		if (_transparent)
		{
			glDisable(GL_CULL_FACE);
			glEnable(GL_BLEND);
			glDepthMask(FALSE); 
		}
		else
		{
			glEnable(GL_CULL_FACE);
			glDisable(GL_BLEND);
			glDepthMask(TRUE); 
		}
	}
	
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	void CRenderGL::updateTransform( Matrix4& _transform, Vector3& _offset )
	{
		if ( !m_iCurrentShader )
		{
			return;
		}

		GLint location = -1;

		location = glGetUniformLocation(m_iCurrentShader, "transform.projectionMatrix");
		glUniformMatrix4fv(location, 1, GL_TRUE, &m_projectionMatrix[0][0]);
		
		location = glGetUniformLocation(m_iCurrentShader, "transform.modelMatrix");
		glUniformMatrix4fv(location, 1, GL_TRUE, &_transform[0][0]);

		location = glGetUniformLocation(m_iCurrentShader, "transform.viewMatrix");
		glUniformMatrix4fv(location, 1, GL_TRUE, &m_viewMatrix[0][0]);
		
		Matrix4 normalMatrix = Vectormath::transpose(Vectormath::inverse(_transform));
		location = glGetUniformLocation(m_iCurrentShader, "transform.normalMatrix");
		glUniformMatrix4fv(location, 1, GL_TRUE, &normalMatrix[0][0]);

		location = glGetUniformLocation(m_iCurrentShader, "transform.viewPosition");
		glUniform3fv(location, 1, &m_viewPosition[0]);

		printOpenGLError("GLError update Transform: ");
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	bool CRenderGL::intShaderProgram( uint& _shaderID, const uint _typeShader, void* _shaderBody )
	{
		bool compileStatus = false;
		compileStatus = CShaderGL::intShaderProgramGL(_shaderID, _typeShader, _shaderBody);
		
		printOpenGLError("GLError init Shader Program: ");

		return compileStatus;
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	void CRenderGL::initShader( uint& _shaderID, std::vector<uint>& _shaderProgramID )
	{
		CShaderGL::initShaderGL(_shaderID, _shaderProgramID);

		printOpenGLError("GLError init Shader: ");
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	void CRenderGL::bindShader( uint _iShaderID )
	{
		m_iCurrentShader = _iShaderID;
		glUseProgram( m_iCurrentShader );

		printOpenGLError("GLError Bind Shader: ");
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	bool CRenderGL::setShaderUniform( SHADER_UNIFORM_TYPE _param, const uint _shaderID,
		const std::string& _attribute, void* _value )
	{
		int location = -1;

		switch( _param )
		{
		case SUT_UNIFORM_INVALID:
			{
				location = -1;
			}
			break;
		case SUT_UNIFORM_INT:
			{
				GLint value = *(GLint*)_value;
				location = glGetUniformLocation( _shaderID, (_attribute).data() );
				glUniform1i( location, value );
			}
			break;
		case SUT_UNIFORM_FLOAT:
			{
				GLfloat value = *(GLfloat*)_value;
				location = glGetUniformLocation( _shaderID, (_attribute).data() );
				glUniform1f( location, value );
			}
			break;
		case SUT_UNIFORM_VECTOR2:
			{
				Vector2 value = *(Vector2*)_value;
				location = glGetUniformLocation( _shaderID, (_attribute).data() );
				glUniform2fv( location, 1, &value[0] );
			}
			break;
		case SUT_UNIFORM_VECTOR3:
			{
				Vector3 value = *(Vector3*)_value;
				location = glGetUniformLocation( _shaderID, (_attribute).data() );
				glUniform3fv( location, 1, &value[0] );
			}
			break;
		case SUT_UNIFORM_VECTOR4:
			{
				Vector4 value = *(Vector4*)_value;
				location = glGetUniformLocation( _shaderID, (_attribute).data() );
				glUniform4fv( location, 1, &value[0] );
			}
			break;
		case SUT_UNIFORM_MATRIX3:
			{
				Matrix3 value = *(Matrix3*)_value;
				location = glGetUniformLocation( _shaderID, (_attribute).data() );
				glUniformMatrix3fv( location, 1, GL_TRUE, &value[0][0] );
			}
			break;
		case SUT_UNIFORM_MATRIX4:
			{
				Matrix4 value = *(Matrix4*)_value;
				location = glGetUniformLocation( _shaderID, (_attribute).data() );
				glUniformMatrix4fv( location, 1, GL_TRUE, &value[0][0] );
			}
			break;
		default:
			break;
		}

		if (location == -1)
		{
			LOG_CONSOLE(" Error Uniform Location: "  << (_attribute).data() <<". Shader ID:" << _shaderID);
		}

		return (location != -1);
	}

	/*---------------------------------------------GLRender--------------------------------------------*/
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	void CRenderGL::bindTexture(const uint& _iTextureID, const uint& _iSamplerID, const uint& _iActiveTexture, 
		const std::string& _attribute, const TEXTURE_TYPE _iType, Vector2& _scale )
	{
		ASSERT((uint)m_iMaxTextureUnits >= _iActiveTexture || "Not supported count texture units");

		glActiveTexture(GL_TEXTURE0 + _iActiveTexture);
		glBindTexture( _iType, _iTextureID );
		glBindSampler( _iSamplerID, _iTextureID );
		
		GLint location = -1;
		std::string strAttribute = "material." + _attribute;
		location = glGetUniformLocation( m_iCurrentShader, strAttribute.c_str() );
		glUniform1i( location, _iActiveTexture );

		location = glGetUniformLocation( m_iCurrentShader, "material.textureScale" );
		glUniform2f( location, _scale[0], _scale[1] );

		printOpenGLError("GLError Bind Texture: ");
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	void CRenderGL::udateCamera( const Vector3& _position, const Vector3& _target, const Vector3& _up )
	{
		m_viewMatrix = Vectormath::transpose(Matrix4::lookAt(Point3(_position), Point3(_target), _up));
		m_viewPosition = _position;
		
		printOpenGLError("GLError Update Camera: ");
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	void CRenderGL::renderLight( const std::string& _attribute, Vector4& _position, SLightData& _lightData )
	{
		if ( !m_iCurrentShader )
		{
			return;
		}

		GLint location = -1;
		std::string strAttribute("");

		strAttribute = _attribute + ".position";
		location = glGetUniformLocation(m_iCurrentShader, strAttribute.c_str());
		glUniform4fv( location, 1, &_position[0] );

		strAttribute = _attribute + ".ambient";
		location = glGetUniformLocation(m_iCurrentShader, strAttribute.c_str());
		glUniform4fv( location,	1, &_lightData._ambient[0] );

		strAttribute = _attribute + ".diffuse";
		location = glGetUniformLocation(m_iCurrentShader, strAttribute.c_str());
		glUniform4fv( location,	1, &_lightData._diffuse[0] );

		strAttribute = _attribute + ".specular";
		location = glGetUniformLocation(m_iCurrentShader, strAttribute.c_str());
		glUniform4fv( location, 1, &_lightData._specular[0] );

		strAttribute = _attribute + ".attenuation";
		location = glGetUniformLocation(m_iCurrentShader, strAttribute.c_str());
		glUniform3fv( location, 1, &_lightData._attenuation[0] );

		printOpenGLError("GLError Render Light: ");
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	void CRenderGL::renderFog( const std::string& _attribute, SFogData& _fogData )
	{
		if ( !m_iCurrentShader )
		{
			return;
		}

		GLint location = -1;
		std::string strAttribute("");

		strAttribute = _attribute + ".fogColor";
		location = glGetUniformLocation(m_iCurrentShader, strAttribute.c_str());
		glUniform4fv( location, 1, &_fogData._color[0] );

		strAttribute = _attribute + ".fogStart";
		location = glGetUniformLocation(m_iCurrentShader, strAttribute.c_str());
		glUniform1f( location, _fogData._fStart );

		strAttribute = _attribute + ".fogEnd";
		location = glGetUniformLocation(m_iCurrentShader, strAttribute.c_str());
		glUniform1f( location, _fogData._fEnd );

		strAttribute = _attribute + ".fogDensity";
		location = glGetUniformLocation(m_iCurrentShader, strAttribute.c_str());
		glUniform1f( location, _fogData._fDensity );

		strAttribute = _attribute + ".fogEquation";
		location = glGetUniformLocation(m_iCurrentShader, strAttribute.c_str());
		glUniform1i( location, _fogData._eMode );

		printOpenGLError("GLError Render Fog: ");
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	void CRenderGL::renderMaterial(  SMaterialData& _sMatrialData )
	{
		if ( !m_iCurrentShader )
		{
			return;
		}

		GLint location = -1;
		location = glGetUniformLocation(m_iCurrentShader, "material.ambient");
		glUniform4fv( location,  1, &_sMatrialData._ambient[0] );

		location = glGetUniformLocation(m_iCurrentShader, "material.diffuse");
		glUniform4fv( location,  1, &_sMatrialData._diffuse[0] );

		location = glGetUniformLocation(m_iCurrentShader, "material.specular");
		glUniform4fv( location, 1, &_sMatrialData._specular[0]);

		location = glGetUniformLocation(m_iCurrentShader, "material.emission");
		glUniform4fv( location, 1, &_sMatrialData._emission[0]);

		location = glGetUniformLocation(m_iCurrentShader, "material.shininess");
		glUniform1fv( location, 1 , &_sMatrialData._iShininess  );

		printOpenGLError("GLError Render Material: ");
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	void CRenderGL::drawDebugNormals( SVertexData& _sVertexData )
	{
		glColor3f(0.0f,1.0f,0.0f);
		

		float s = 0.3f;
		for ( uint i = 0; i < _sVertexData.nVertices; ++i )
		{
			glBegin(GL_LINES);
			glVertex3fv(_sVertexData.Vertex.vertices[i].getArray());
			glVertex3f((_sVertexData.Vertex.vertices[i].getX() + _sVertexData.Normal.vertices[i].getX()*s),
				(_sVertexData.Vertex.vertices[i].getY() + _sVertexData.Normal.vertices[i].getY()*s) ,
				(_sVertexData.Vertex.vertices[i].getZ() + _sVertexData.Normal.vertices[i].getZ()*s));
			glEnd();
		}
		glColor3f(1.0f,1.0f,1.0f);
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	void CRenderGL::drawDebugLight( Vector4& _v4Pos, SLightData& _sLightData )
	{
		glColor3f(0.0f,1.0f,0.0f);
		glPointSize(40);
		glDisable(GL_LIGHTING);

		float s = 1.0f;

		glBegin(GL_POINTS);
		glVertex3fv(_v4Pos.getArray());
		glEnd();

		glColor3f(1.0f,1.0f,0.0f);

		glBegin(GL_LINES);
		glVertex3fv( _v4Pos.getArray() );
		glVertex3f( (_v4Pos.getX() + _sLightData._direction.getX() * s),
			(_v4Pos.getY() + _sLightData._direction.getY() * s),
			(_v4Pos.getZ() + _sLightData._direction.getZ()) * s );
		glEnd();

		glColor3f(1.0f,1.0f,1.0f);
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	void CRenderGL::drawSimple( const DRAW_MODE& _mode, SVertexData& _vertexData, 
		const uint& _firstPoint, const uint& _count )
	{
		glBindVertexArray(_vertexData.iVertexArrayID);

		if ( _vertexData.nIndices != 0 )
		{
			glDrawElements( _mode, _vertexData.nIndices, GL_UNSIGNED_INT, NULL );
		}
		else
		{
			glDrawArrays( _mode, _firstPoint, (_count == 0) ? _vertexData.nVertices : _count );
		}

		glBindVertexArray(NULL);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D,0);

		//bindShader(0);
		
		printOpenGLError("GLError Draw Simple: ");
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	void CRenderGL::preDrawSimple( const SDrawParam& _currentParam )
	{
		glGetIntegerv(GL_CULL_FACE_MODE, &m_eDrawParam._iCullFaceMode);
		glGetIntegerv(GL_DEPTH_FUNC, &m_eDrawParam._iDepthFuncMode);

		glCullFace(_currentParam._iCullFaceMode);
		glDepthFunc(_currentParam._iDepthFuncMode);
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	void CRenderGL::postDrawSimple()
	{
		glCullFace(m_eDrawParam._iCullFaceMode);
		glDepthFunc(m_eDrawParam._iDepthFuncMode);
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	void CRenderGL::showFPS()
	{
		//static CTimer timer;
		//static int count = 0;
		//static std::string fps = "0.0 FPS";
		//double elapsedTime = 0.0;;

		//glPushMatrix();
		//glLoadIdentity(); 

		//glMatrixMode(GL_PROJECTION);        
		//glPushMatrix();                     
		//glLoadIdentity();                   
		//gluOrtho2D(0, m_iScreenWidth, 0, m_iScreenHeight); 

		//float color[4] = {1, 1, 0, 1};

		//elapsedTime = timer.getElapsedTime();
		//if(elapsedTime < 1.0)
		//{
		//	++count;
		//}
		//else
		//{
		//	std::stringstream ss;
		//	ss << std::fixed << std::setprecision(1);
		//	ss << (count / elapsedTime) << " FPS" << std::ends; // update fps string
		//	ss << std::resetiosflags(std::ios_base::fixed | std::ios_base::floatfield);
		//	fps = ss.str();
		//	count = 0;                      // reset counter
		//	timer.start();                  // restart timer
		//}
		//int textWidth = (int)fps.size() * TEXT_WIDTH;
		//drawString(fps.c_str(), screenWidth-textWidth, screenHeight-TEXT_HEIGHT, color, font);

		//// restore projection matrix
		//glPopMatrix();                      // restore to previous projection matrix

		//// restore modelview matrix
		//glMatrixMode(GL_MODELVIEW);         // switch to modelview matrix
		//glPopMatrix();                      // restore to previous modelview matrix
	}

	void CRenderGL::drawString(const char *str, int x, int y, float color[4], void *font)
	{
		//glPushAttrib(GL_LIGHTING_BIT | GL_CURRENT_BIT); // lighting and color mask
		//glDisable(GL_LIGHTING);     // need to disable lighting for proper text color
		//glDisable(GL_TEXTURE_2D);

		//glColor4fv(color);          // set text color
		//glRasterPos2i(x, y);        // place text position

		//// loop all characters in the string
		//while(*str)
		//{
		//	glutBitmapCharacter(font, *str);
		//	++str;
		//}

		//glEnable(GL_TEXTURE_2D);
		//glEnable(GL_LIGHTING);
		//glPopAttrib();
	}

}
