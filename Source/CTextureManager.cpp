#include "CTextureManager.h"

namespace gllib
{
	CTextureManager::CTextureManager()
		: m_iCount(0)
	{
	}

	CTextureManager::~CTextureManager()
	{
		for (std::vector<CTexture*>::iterator iter = m_textureList.begin(); iter < m_textureList.end(); ++iter )
		{
			delete (*iter);
			(*iter) = NULL;
			--m_iCount;
		}

		m_textureList.clear();
	}

	CTexture* CTextureManager::createTexture2D( const char* _imageFile )
	{
		std::vector<const char*> names;
		names.push_back(_imageFile);

		CTexture* texture;
		if ( (texture = findTextureByNames(&names)) != NULL )
		{
			return texture;
		}

		texture = new CTexture2D();
		texture->loadImage( _imageFile );

		CTextureManager::m_textureList.push_back(texture);
		++m_iCount;

		return texture;
	}

	CTexture* CTextureManager::createTextureCubeMap( const char** _imageFiles )
	{
		std::vector<const char*> names;
		for ( uint i = 0; i < 6; ++i )
		{
			names.push_back(_imageFiles[i]);
		}

		CTexture* texture;
		if ( (texture = findTextureByNames(&names)) != NULL )
		{
			return texture;
		}

		texture = new CTextureCubeMap();
		texture->loadCubeMap( _imageFiles );

		CTextureManager::m_textureList.push_back(texture);
		++m_iCount;

		return texture;
	}

	bool CTextureManager::isExist( const CTexture* _texture ) const
	{
		for (std::vector<CTexture*>::const_iterator iter = m_textureList.begin(); iter < m_textureList.end(); ++iter )
		{
			CTexture* texture = (*iter);
			if ( texture->compareByName(&_texture->m_TextureFilesList) )
			{
				return true;
			}
		}

		return false;
	}

	CTexture* CTextureManager::findTextureByNames( const std::vector<const char*>* _nameFiles ) const
	{
		for (std::vector<CTexture*>::const_iterator iter = m_textureList.begin(); iter < m_textureList.end(); ++iter )
		{
			CTexture* texture = (*iter);
			if ( texture->compareByName(_nameFiles) )
			{
				return texture;
			}
		}

		return NULL;
	}

}