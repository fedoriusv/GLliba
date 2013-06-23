#include "CRenderTarget.h"

namespace glliba
{
	CRenderTarget::CRenderTarget()
		: m_iFrameBuffID(0)
	{
		m_sTextureData._iWidth	= 0;
		m_sTextureData._iHeight = 0;
		m_sTextureData._iDepth	= 0;
		m_sTextureData._eFormat = IF_RGB;
		m_sTextureData._eType	= IT_UNSIGNED_BYTE;
		m_sTextureData._data	= NULL;

		m_eTarget = TT_TEXTURE2D;
	}

	CRenderTarget::~CRenderTarget()
	{
	}

	bool CRenderTarget::isValid()
	{
		return ( m_sTextureData._iWidth != 0 && m_sTextureData._iHeight != 0 );
	}
}