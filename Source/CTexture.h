#ifndef _CTEXTURE_H_
#define _CTEXTURE_H_

#include "CImage.h"
#include "Param.h"

namespace glliba
{

	//////////////////////////////////////////////////////////////////////////////////////////////////////////

	enum TEXTURE_LAYER
	{
	  TL_TEXTURE_0 = 0,
	  TL_TEXTURE_1,
	  TL_TEXTURE_2,
	  TL_TEXTURE_3,
	  
	  TL_TEXTURE_MAX,
	};

	//////////////////////////////////////////////////////////////////////////////////////////////////////////

	struct STextureData2D
	{
		uint			_iWidth;
		uint			_iHeight;
		uint			_iDepth;
		IMAGE_FORMAT	_eFormat;
		IMAGE_TYPE		_eType;
		void*			_data;
	};

	//////////////////////////////////////////////////////////////////////////////////////////////////////////

	class CMaterial;
	class CTextureManager;
	class CSampler;

	class CTexture : public CObject
	{
	protected:
		friend				CTextureManager;
		friend				CMaterial;

		static int			s_iTextureCount;

		uint				m_iTextureID;

		TEXTURE_TYPE		m_eTarget;
		CSampler*			m_pSampler;
		
		Vector2				m_scale;

		std::string			m_attribute;

	public:

		CTexture();
		~CTexture();

		virtual bool		isValid() = 0;
		
		void				bind( uint _textureLayer );
		
		Vector2				getScale() const;
		void				setScale( const Vector2& _scale );

		uint				getTextureID() const;
		uint				getSamplerID() const;

		CSampler*			getSampler() const;
		TEXTURE_TYPE		getTarget() const;

		void				setAttributeTexture( const std::string& _attribute );
		std::string			getAttributeTexture() const;
	};

	/////////////////////////////////////////////////////////////////////////////////////////////////////

} //glliba

#endif