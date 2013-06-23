#ifndef _C_RENDERTARGET_H_
#define _C_RENDERTARGET_H_

#include "CTexture.h"

namespace glliba
{
	class CRenderTarget : public CTexture
	{
	private:
		friend				CResourceManager;

		uint				m_iFrameBuffID;
		STextureData2D		m_sTextureData;
	public:
		CRenderTarget();
		virtual ~CRenderTarget();

		bool	isValid();
	};
}

#endif