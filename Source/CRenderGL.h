#ifndef _CRENDER_GL_H_
#define _CRENDER_GL_H_

#include "CRender.h"

#define TEXTURE_CUBE_MAP_COUNT 6
#define BUFFER_OFFSET(i) ((void*)(i))


namespace glliba
{
	////////////////////////////////////////////////////////////////////////////////////////////////////////

	enum GL_SHADER_ATTRIBUTE
	{ 
		GL_ATTRIBUTE_VERTEX = 0,
		GL_ATTRIBUTE_COLOR,
		GL_ATTRIBUTE_NORMAL,
		GL_ATTRIBUTE_BINORMAL,
		GL_ATTRIBUTE_TANGENT,
		GL_ATTRIBUTE_TEXTURE0,
		GL_ATTRIBUTE_TEXTURE1,
		GL_ATTRIBUTE_TEXTURE2,
		GL_ATTRIBUTE_TEXTURE3,
		
		GL_ATTRIBUTE_COUNT
	};

	////////////////////////////////////////////////////////////////////////////////////////////////////////

	class CRenderGL : public CRender
	{
	private:
		int				m_iMaxTextureUnits;

		uint			m_iCurrentShader;

		Matrix4			m_projectionMatrix;
		Matrix4			m_viewMatrix;

		CRenderGL();
		void			beginRender();
		void			endRender();

		void			drawDebugNormals( SVertexData& _vertexData );
		void			drawDebugLight( Vector4& _pos, SLightData& _data );
	public:
		static CRender*	getInstance();

		virtual			~CRenderGL();
		bool			init( void* _hWnd );
		void			reshape( uint _iWidth, uint _iHeight );

		void			printOpenGLInfo();
		void			printOpenGLError( const std::string& _errorString );
		

		//init objects
		//--------------------------------------------------------------------------------------------

		void			initTexture2D			( uint&		  _iTextureID,
												 const STextureData2D& _sTextureData,
												 const bool	  _bMipMap = true );

		void			initTextureCubeMap		( uint&		  _iIndexTexture,
												 const STextureData2D* _sTextureData,
												 const bool	  _bMipMap = true );

		void			initSampler				( uint&		  _iSamplerID,
												  WRAP_TYPE	  _eWrapType,
												  FILTER_TYPE _eMinFilerType,
												  FILTER_TYPE _eMagFilerType );

		void			initRenderTarget		( uint&		  _iFrameBuffID,
												  uint&		  _itextireID,
												  const uint  _iWidth,
												  const uint  _iHeight );

		void			initBufferObjects		( SVertexData& _sVertexData );

		void			intShaderProgram		( uint&		  _iShaderID,
												  const uint  _iTypeShader,
												  void*		  _shaderBody );

		void			initShader				( uint&		  _ishaderID,
												  const uint  _iVertexShader,
												  const uint  _iFragmentShader );

		void			initVertexAttribPointer ( const uint  _iVertexAttrib,
												  const uint  _iSize );

		//render objects
		//---------------------------------------------------------------------------------------------

		void			renderLight		  (	const std::string&	_attribute, 
											Vector4&			_position,
											SLightData&			_sLightData );

		void			renderMaterial	  (	SMaterialData&		_sMatrialData );

		void			renderFog		  (	const bool		_bEnabled, 
											SFogData&		_sFogData );

		void			renderToTexture	  ( const uint		_id,
											const uint		_texId );

		void			bindTexture		  (	const uint&			_iTextureID,
											const uint&			_iSamplerID,
											const uint&			_iActiveTexture,
											const std::string&	_attribute,
											const TEXTURE_TYPE	_iType,
											Vector2&			_scale );

		void			bindShader		  (	const uint			_iShaderID );

		void			updateSampler	  ( uint&				_iSamplerID,
											const WRAP_TYPE		_eWrapType,
											const FILTER_TYPE	_eMinFilerType,
											const FILTER_TYPE	_eMagFilerType );

		void			udateCamera		  (	const Vector3&		_position,
											const Vector3&		_target,
											const Vector3&		_up );

		void			updateTransform	  (	Matrix4&			_tyransform,
											Vector3&			_offset );

		void			updateBufferObject(	SVertexData&		_sVertexData );

		void			drawSimple		  (	const DRAW_MODE&	_mode,
											SVertexData&		_vertexData,
											const uint&			_iCountTexLayer );

		bool			setShaderUniform  (	const uint			_eParam,
											const uint			_iShaderID,
											const std::string*	_attribute,
											void*				_value );

		//delete object
		//--------------------------------------------------------------------------------------------

		void			deleteTexture		( const	uint	_iTextureID );

		void			deleteSampler		( const uint	_iSamplerID );

		void			deleteBuffers		( const uint	_iVertexID  );

		void			deleteBufferObjects	( SVertexData& _sVertexData );

		void			deleteShader		( const uint   _iShaderID   );

		
		void			showFPS();
		void			drawString(const char *str, int x, int y, float color[4], void *font);
	};

	////////////////////////////////////////////////////////////////////////////////////////////////////////
}

#endif