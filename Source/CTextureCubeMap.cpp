#include "CTextureCubeMap.h"

#include "CRender.h"
#include "CResourceManager.h"

namespace glliba
{
	////////////////////////////////////////////////////////////////////////////////////////////////////////

	CTextureCubeMap::CTextureCubeMap()
		: m_iCOUNT(6U)

	{
		for ( uint i = 0; i < m_iCOUNT; ++i )
		{
			m_cubeMapData[i]._iWidth	= 0;
			m_cubeMapData[i]._iHeight	= 0;
			m_cubeMapData[i]._iDepth	= 0;
			m_cubeMapData[i]._eFormat	= IF_RGB;
			m_cubeMapData[i]._eType		= IT_UNSIGNED_BYTE;
			m_cubeMapData[i]._data		= NULL;
		}

		m_eTarget = TT_TEXTURE_CUBEMAP;
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////

	CTextureCubeMap::~CTextureCubeMap()
	{
		for ( uint i = 0; i < m_iCOUNT; ++i )
		{
			if (m_cubeMapData[i]._data != NULL)
			{
				free(m_cubeMapData[i]._data);
				m_cubeMapData[i]._data = NULL;
			}
		}
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////

	bool CTextureCubeMap::isValid()
	{
		for ( uint i = 0; i < m_iCOUNT; ++i )
		{
			if ( m_cubeMapData[i]._data == NULL || m_cubeMapData[i]._iWidth == 0 || m_cubeMapData[i]._iHeight == 0 )
			{
				return false;
			}
		}
		return true;
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////

}