#ifndef _CIMAGE_H_
#define _CIMAGE_H_

#include "CObject.h"
#include "Param.h"

namespace glliba
{
	   
	///////////////////////////////////////////////////////////////////////////////////////////////////////////
	class CResourceManager;
	class CTexture2D;

	class CImage : public CObject
	{
	protected:

		friend			CResourceManager;
		friend			CTexture2D;

		uint			m_iWidth;
		uint			m_iHeight;
		uint			m_iDepth;
		IMAGE_FORMAT	m_eFormat;
		IMAGE_TYPE		m_eType;
		void*			m_data;

		uint			m_iImageID;

		std::string		m_imageFile;

		void			clearData();

		bool			m_bIsLoaded;

#ifdef _USE_DEVIL
		bool	loadImageDevil( const std::string* _nameFile );
#endif

	public:
		CImage();
		virtual ~CImage();

		uint	getWidth() const;
		uint	getHeight() const;
		uint	getDepth() const;
		uint	getFormat() const;
		uint	getType() const;
		void*	getData() const;

		bool	loadImage( const std::string* _nameFile );
	};

	///////////////////////////////////////////////////////////////////////////////////////////////////////////

}

#endif