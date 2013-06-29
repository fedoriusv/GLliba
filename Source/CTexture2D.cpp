#include "CTexture2D.h"
#include "CRender.h"


namespace glliba
{
	////////////////////////////////////////////////////////////////////////////////////////////////////////

	CTexture2D::CTexture2D()
	{
		m_sTextureData._iWidth	= 0;
		m_sTextureData._iHeight = 0;
		m_sTextureData._iDepth	= 0;
		m_sTextureData._eFormat = IF_RGB;
		m_sTextureData._eType	= IT_UNSIGNED_BYTE;
		m_sTextureData._data	= NULL;

		m_eTarget = TT_TEXTURE2D;
	}

	
	CTexture2D::~CTexture2D()
	{
		if (m_sTextureData._data != NULL)
		{
			delete m_sTextureData._data;
			m_sTextureData._data = NULL;
		}
	}

	
	bool CTexture2D::isValid()
	{
		return ( m_sTextureData._data != NULL && m_sTextureData._iWidth != 0 && m_sTextureData._iHeight != 0 );
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////////////

} //glliba