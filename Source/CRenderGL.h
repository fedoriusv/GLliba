#ifndef _CRENDER_GL_H_
#define _CRENDER_GL_H_

#include "CRender.h"

#define TEXTURE_CUBE_MAP_COUNT 6
#define BUFFER_OFFSET(i) ((void*)(i))


namespace glliba
{
	////////////////////////////////////////////////////////////////////////////////////////////////////////

	class CRenderGL : public CRender
	{
	private:
		int				m_iMaxTextureUnits;

		uint			m_iCurrentShader;

		Matrix4			m_projectionMatrix;
		Matrix4			m_viewMatrix;
		Vector3			m_viewPosition;

		CRenderGL();
		void			beginRender();
		void			endRender();

		void			drawDebugNormals( SVertexData& _vertexData );
		void			drawDebugLight( Vector4& _pos, SLightData& _data );
	public:
		static CRender*	getInstance();

		virtual			~CRenderGL();
		bool			init( void* _hWnd );
		void			reshape( uint _width, uint _height );

		void			printOpenGLInfo();
		void			printOpenGLError( const std::string& _errorString );
		

		//init objects
		//--------------------------------------------------------------------------------------------

		void			initTexture2D( 
							uint&				_textureID,
							const STextureData2D& _textureData,
							const bool 			_isMipMap = true );

		void			initTextureCubeMap( 
							uint&				_indexTexture,
							const STextureData2D* _textureData,
							const bool			_isMipMap = true );

		void			initSampler( 
							uint&				_samplerID,
							WRAP_TYPE			_wrapType,
							FILTER_TYPE			_minFilerType,
							FILTER_TYPE			_magFilerType );

		void			initRenderTarget( 
							uint&				_frameBuffID,
							uint&				_textireID,
							const uint			_width,
							const uint			_height );

		void			initBufferObjects( 
							SVertexData&		_vertexData );

		void			intShaderProgram( 
							uint&				_shaderID,
							const uint			_typeShader,
							void*				_shaderBody );

		void			initShader( 
							uint&				_shaderID,
							const uint			_vertexShader,
							const uint			_fragmentShader );

		//render objects
		//---------------------------------------------------------------------------------------------

		void			renderLight( 
							const std::string&	_attribute, 
							Vector4&			_position,
							SLightData&			_lightData );

		void			renderMaterial( 
							SMaterialData&		_matrialData );

		void			renderFog( 
							const bool			_enabled, 
							SFogData&			_fogData );

		void			renderToTexture( 
							const uint			_id,
							const uint			_texId );

		void			bindTexture( 
							const uint&			_textureID,
							const uint&			_samplerID,
							const uint&			_activeTexture,
							const std::string&	_attribute,
							const TEXTURE_TYPE	_type,
							Vector2&			_scale );

		void			bindShader( 
							const uint			_shaderID );

		void			updateSampler( 
							uint&				_samplerID,
							const WRAP_TYPE		_wrapType,
							const FILTER_TYPE	_minFilerType,
							const FILTER_TYPE	_magFilerType );

		void			udateCamera( 
							const Vector3&		_position,
							const Vector3&		_target,
							const Vector3&		_up );

		void			updateTransform( 
							Matrix4&			_tyransform,
							Vector3&			_offset );

		void			updateBufferObject(
							SVertexData&		_vertexData );

		void			preDrawSimple();

		void			drawSimple( 
							const DRAW_MODE&	_mode,
							SVertexData&		_vertexData,
							const uint&			_firstPoint = 0,
							const uint&			_count		 = 0);

		void			postDrawSimple();

		bool			setShaderUniform( 
							SHADER_UNIFORM_TYPE	_param,
							const uint			_shaderID,
							const std::string&	_attribute,
							void*				_value );

		//delete object
		//--------------------------------------------------------------------------------------------

		void			deleteTexture( 
							const	uint		_textureID );

		void			deleteSampler( 
							const uint			_samplerID );

		void			deleteBufferObjects( 
							SVertexData&		_vertexData );

		void			deleteShader( 
							const uint			_shaderID );

		
		void			showFPS();
		void			drawString(const char *str, int x, int y, float color[4], void *font);
	};

	////////////////////////////////////////////////////////////////////////////////////////////////////////
}

#endif