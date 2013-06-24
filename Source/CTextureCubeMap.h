#ifndef _CTEXTURECUBEMAP_H_
#define _CTEXTURECUBEMAP_H_

#include "CTexture.h"

namespace glliba
{

	////////////////////////////////////////////////////////////////////////////////////////////////////////

	class CTextureCubeMap : public CTexture
	{
	protected:
		friend				CTextureManager;

		uint				m_iCOUNT;
		STextureData2D		m_cubeMapData[6U];

	public:

		CTextureCubeMap();
		virtual				~CTextureCubeMap();

		bool				isValid();
	};

	////////////////////////////////////////////////////////////////////////////////////////////////////////
}

#endif