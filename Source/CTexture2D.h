#ifndef _CTEXTURE2D_H_
#define _CTEXTURE2D_H_

#include "CTexture.h"

namespace glliba
{
	////////////////////////////////////////////////////////////////////////////////////////////////////////
	class CFreeTypeFont;
	class CTextureManager;

	class CTexture2D : public CTexture
	{
	protected:
		friend			CTextureManager;
		friend			CFreeTypeFont;

		STextureData2D	m_sTextureData;

	public:

		CTexture2D();
		virtual			~CTexture2D();

		bool			isValid();
	};

	////////////////////////////////////////////////////////////////////////////////////////////////////////
}

#endif