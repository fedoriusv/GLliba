#ifndef _CRENDER_H_
#define _CRENDER_H_

#include "Param.h"
#include "Vertex.h"

namespace glliba
{
	////////////////////////////////////////////////////////////////////////////////////////////////////////

	enum TYPE_DRIVER
	{
		TD_UNKNOWN,
		TD_OPENGL,

		TD_OTHER,
	};

	////////////////////////////////////////////////////////////////////////////////////////////////////////

	struct STextureData2D;
	struct SMaterialData;
	struct SLightData;
	struct SVertexData;
	struct SShaderData;
	struct SFogData;
	struct SDrawParam;

		
	class CRender
	{
	protected:

		static CRender*		s_pRender;
		CRender();

		static TYPE_DRIVER	m_eTypeDriver;
		
		bool				m_bFullscreen;
		uint				m_iScreenWidth;
		uint				m_iScreenHeight;

		Vector3				m_backColor;

		bool				m_bIsShowDebug;

	public:
		uint				getWidth() const;
		uint				getHeight() const;

		void				setActiveDebug( bool _bIsShowNormals );

		~CRender();
		static CRender*		getInstance();

		virtual void		beginRender()							= 0;
		virtual void		endRender()								= 0;
		virtual bool		init( void* _hWnd )						= 0;
		virtual void		reshape( uint _width, uint _height )	= 0;

		void				setBackColor( const Vector3& _color = Vector3(0.0f) );

		//init objects
		//------------------------------------------------------------------------------------------
		
		virtual void		initTexture2D( 
								uint&				_textureID, 
								const STextureData2D& _textureData, 
								const bool			_isMipMap = true)	= 0;

		virtual void		initTextureCubeMap( 
								uint& _textureID,
								const STextureData2D* _textureData,
								const bool			_isMipMap = true )	= 0;

		virtual void		initSampler( 
								uint&				_samplerID,
								WRAP_TYPE			_wrapType,
								FILTER_TYPE			_minFilerType,
								FILTER_TYPE			_magFilerType )		= 0;

		virtual void		initBufferObjects( 
								SVertexData&		_vertexData )		= 0;
		
		virtual void		intShaderProgram( 
								uint&				_shaderID,
								const uint			_iTypeShader,
								void*				_shaderBody )		= 0;

		virtual void		initRenderTarget( 
								uint&				_frameBuffID,
								uint&				_textireID,
								const uint			_width,
								const uint			_height )			= 0;

		virtual void		initShader( 
								uint&				_shaderID,
								const uint			_vertexShader,
								const uint			_fragmentShader )	= 0;

		//render objects
		//----------------------------------------------------------------------------------------

		virtual void		renderLight( 
								const std::string&	_attribute,  
								Vector4&			_position,
								SLightData&			_sLightData )		= 0;
		
		virtual void		bindTexture( 
								const uint&			_textureID,
								const uint&			_samplerID,
								const uint&			_activeTexture,
								const std::string&	_attribute,
								const TEXTURE_TYPE	_type, 
								Vector2&			_scale )			= 0;

		virtual void		bindShader( 
								const uint			_shaderID )			= 0;

		virtual void		renderMaterial(
								SMaterialData&		_SMatrialData )		= 0;

		virtual void		renderFog( 
								const std::string&	_attribute,
								SFogData&			_fogData )			= 0;

		virtual void		renderToTexture( 
								const uint			_id,
								const uint			_texId )			= 0;

		virtual void		updateSampler( uint&	_samplerID,
								const WRAP_TYPE		_wrapType,
								const FILTER_TYPE	_minFilerType,
								const FILTER_TYPE	_magFilerType )		= 0;

		virtual void		udateCamera( 
								const Vector3&		_position,
								const Vector3&		_target,
								const Vector3&		_up )				= 0;

		virtual void		updateTransform( 
								Matrix4&			_transform,
								Vector3&			_offset )			= 0;

		virtual void		updateBufferObject(
								SVertexData&		_vertexData )		= 0;

		virtual void		preDrawSimple( 
								const SDrawParam& _currentParam )		= 0;
			
		virtual void		drawSimple( 
								const DRAW_MODE&	_mode,
								SVertexData&		_vertexData,
								const uint&			_firstPoint = 0,
								const uint&			_count = 0 )		= 0;

		virtual void		postDrawSimple()							= 0;
		
		virtual bool		setShaderUniform(
								SHADER_UNIFORM_TYPE	_param,
								const uint			_shaderID,
								const std::string&	_attribute,
								void*				_value )			= 0;

		//delete object
		//-------------------------------------------------------------------------------------------

		virtual void		deleteTexture(
								const uint	_textureID )		= 0;
		
		virtual void		deleteSampler( 
								const uint	_samplerID )		= 0;

		virtual void		deleteBufferObjects(
								SVertexData& _vertexData )		= 0;

		virtual void		deleteShader( 
								const uint	_shaderID   )		= 0;

	};

	////////////////////////////////////////////////////////////////////////////////////////////////////////

#define RENDERER	CRender::getInstance()

	////////////////////////////////////////////////////////////////////////////////////////////////////////
}

#endif