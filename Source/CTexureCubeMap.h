#ifndef _CTEXTURECUBEMAP_H_
#define _CTEXTURECUBEMAP_H_

#include "CTexture.h"

namespace gllib
{
	class CTextureCubeMap : public CTexture
	{
	protected:
		size_t				m_COUNT;
		STextureData		m_cubeMapData[6U];
	public:
		CTextureCubeMap();
		virtual				~CTextureCubeMap();
		void				render();
		void				update();
		bool				isValid();
		void				loadImage( const char* _fileName );
		virtual void		loadCubeMap( const char* _textureName[6] );
	};
}

#endif