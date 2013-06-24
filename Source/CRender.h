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

		
	class CRender
	{
	protected:

		static CRender*			s_pRender;
		CRender();

		static TYPE_DRIVER		m_eTypeDriver;
		
		bool					m_bFullscreen;
		uint					m_iScreenWidth;
		uint					m_iScreenHeight;

		Vector3					m_backColor;

		bool					m_bIsShowDebug;

	public:
		uint					getWidth() const;
		uint					getHeight() const;

		void					setActiveDebug( bool _bIsShowNormals );

		~CRender();
		static CRender*			getInstance();

		virtual void			beginRender()							= 0;
		virtual void			endRender()								= 0;
		virtual bool			init( void* _hWnd )						= 0;
		virtual void			reshape( uint _iWidth, uint _iHeight )	= 0;

		void					setBackColor( const Vector3& _col = Vector3(0, 0, 0) );

		//init objects
		//------------------------------------------------------------------------------------------
		
		virtual void			initTexture2D	  (	uint&			_iTextureID,
													const STextureData2D& _sTextureData,
													const bool		_bMipMap = true)		= 0;

		virtual void			initTextureCubeMap(	uint&			_iTextureID,
													const STextureData2D* _sTextureData,
													const bool		_bMipMap = true )		= 0;

		virtual void			initSampler		  ( uint&			_iSamplerID,
													WRAP_TYPE		_eWrapType,
													FILTER_TYPE		_eMinFilerType,
													FILTER_TYPE		_eMagFilerType )		= 0;

		virtual void			initBufferObjects ( SVertexData&	_sVertexData )			= 0;
		
		virtual void			intShaderProgram  (	uint&			_iShaderID,
													const uint		_iTypeShader,
													void*			_shaderBody )			= 0;

		virtual void			initRenderTarget  ( uint&			_iFrameBuffID,
													uint&			_itextireID,
													const uint		_iWidth,
													const uint		_iHeight )				= 0;

		virtual void			initShader		  (	uint&			_ishaderID,
													const uint		_iVertexShader,
													const uint		_iFragmentShader )		= 0;

		//render objects
		//----------------------------------------------------------------------------------------

		virtual void			renderLight		  (	const std::string&	_attribute,  
													Vector4&			_position,
													SLightData&			_sLightData )		= 0;
		
		virtual void			bindTexture		  (	const uint&			_iTextureID,
													const uint&			_iSamplerID,
													const uint&			_iActiveTexture,
													const std::string&	_attribute,
													const TEXTURE_TYPE	_iType, 
													Vector2&			_scale )			= 0;

		virtual void			bindShader		  ( const uint			_iShaderID )		= 0;

		virtual void			renderMaterial	  (	SMaterialData&		_SMatrialData )		= 0;

		virtual void			renderFog		  (	const bool		_bEnabled, 
													SFogData&		_sFogData )				= 0;

		virtual void			renderToTexture	  ( const uint		_id,
													const uint		_texId )				= 0;

		virtual void			updateSampler	  ( uint&				_iSamplerID,
													const WRAP_TYPE		_eWrapType,
													const FILTER_TYPE	_eMinFilerType,
													const FILTER_TYPE	_eMagFilerType )	= 0;

		virtual void			udateCamera		  (	const Vector3&		_position,
													const Vector3&		_target,
													const Vector3&		_up )				= 0;

		virtual void			updateTransform	  (	Matrix4&			_transform,
													Vector3&			_offset )			= 0;

		virtual void			updateBufferObject(	SVertexData&		_sVertexData )		= 0;
			
		virtual void			drawSimple		  (	const DRAW_MODE&	_iMode,
													SVertexData&		_vertexData,
													const uint&			_iFirstPoint = 0,
													const uint&			_iCount		 = 0 )	= 0;
		
		virtual bool			setShaderUniform  (	const uint			_eParam,
													const uint			_iShaderID,
													const std::string*  _attribute,
													void*				_value )			= 0;

		//delete object
		//-------------------------------------------------------------------------------------------

		virtual void			deleteTexture		( const uint	_iTextureID  )		= 0;
		
		virtual void			deleteSampler		( const uint	_iSamplerID  )		= 0;

		virtual void			deleteBufferObjects	( SVertexData&	_sVertexData )		= 0;

		virtual void			deleteShader		( const uint	_iShaderID   )		= 0;

	};

	////////////////////////////////////////////////////////////////////////////////////////////////////////

#define RENDERER	CRender::getInstance()

	////////////////////////////////////////////////////////////////////////////////////////////////////////
}

#endif