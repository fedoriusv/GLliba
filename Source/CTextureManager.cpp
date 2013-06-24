#include "CTextureManager.h"

#include "CTexture2D.h"
#include "CTextureCubeMap.h"
#include "CRender.h"

#include <string>
#include <boost/bind.hpp>

namespace glliba
{
	//////////////////////////////////////////////////////////////////////////////////////////////

	CTextureManager::CTextureManager()
		: m_iCountTextures(0)
	{
	}

	//////////////////////////////////////////////////////////////////////////////////////////////
	
	CTextureManager::~CTextureManager()
	{
		for (auto& texturelist : m_textures)
		{
			CTexture* texture = texturelist.second;
			destroyTexture(texture);

			if (texture == nullptr)
			{
				ASSERT( false || "Lost ref recognize");
			}
		}
	}

	//////////////////////////////////////////////////////////////////////////////////////////////

	void CTextureManager::transformString( std::string& _string,  bool _toLower )
	{
		std::transform( _string.begin(), _string.end(), _string.begin(), _toLower ? ::tolower : ::toupper );
	}

	//////////////////////////////////////////////////////////////////////////////////////////////

	bool CTextureManager::loadImage( STextureData2D& _textureData, const std::string& _imageFile )
	{
#ifdef _USE_DEVIL
		return loadImageDevil( _textureData, _imageFile );
#endif
		return false;
	}

#ifdef _USE_DEVIL
	bool CTextureManager::loadImageDevil( STextureData2D& _textureData, const std::string& _imageFile )
	{
		uint success = -1;

		//http://content.gpwiki.org/index.php/DevIL:Tutorials:Basics

		success = ilLoadImage( (char*)_imageFile.data() );
		ASSERT( success == 1 && "Invalid Texture");
		
		_textureData._iWidth  = ilGetInteger(IL_IMAGE_WIDTH);
		_textureData._iHeight = ilGetInteger(IL_IMAGE_HEIGHT);
		_textureData._iDepth  = ilGetInteger(IL_IMAGE_DEPTH);
		_textureData._eFormat = (IMAGE_FORMAT)ilGetInteger(IL_IMAGE_FORMAT);
		_textureData._eType   = (IMAGE_TYPE)ilGetInteger(IL_IMAGE_TYPE);

		ilConvertImage(_textureData._eFormat, _textureData._eType);
		
		if (_textureData._data != NULL)
		{
			delete _textureData._data;
			_textureData._data = NULL;
		}
		
		_textureData._data = (ILubyte*)malloc(ilGetInteger(IL_IMAGE_SIZE_OF_DATA));
		memcpy(_textureData._data, ilGetData(),ilGetInteger(IL_IMAGE_SIZE_OF_DATA));

		return (success == 1) ? true : false;
	}
#endif

	//////////////////////////////////////////////////////////////////////////////////////////////

	bool CTextureManager::findTextureByID( const Texture _texture, uint _iTextureID ) const
	{
		return _texture.second->m_iTextureID == _iTextureID;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////

	CTexture* CTextureManager::createTexture( const std::string& _imageFile )
	{
		StringList textureList;
		textureList.push_back(_imageFile);
		auto texureIter = m_textures[textureList];

		if (texureIter != nullptr)
		{
			return (CTexture*)texureIter->getRef();
		}

		CTexture2D* newTexture = new CTexture2D();
		
		bool loaded = false;
		loaded = loadImage(newTexture->m_sTextureData, _imageFile);

		if (loaded)
		{
			RENDERER->initTexture2D( newTexture->m_iTextureID, newTexture->m_sTextureData );
			LOG_CONSOLE( "Texture loaded success: " << _imageFile.c_str() );
			
			m_textures[textureList] = newTexture;
			++m_iCountTextures;
		}

		return (CTexture*)newTexture->getRef();
	}

	//////////////////////////////////////////////////////////////////////////////////////////////

	CTexture* CTextureManager::createCubeMap( const std::string _imageFile[6] )
	{
		StringList textureList;
		for ( int texure = 0; texure < 6U; ++texure )
		{
			textureList.push_back(_imageFile[texure]);
		}
		auto texureIter = m_textures[textureList];

		if (texureIter != nullptr)
		{
			return (CTexture*)texureIter->getRef();
		}

		CTextureCubeMap* newTexture = new CTextureCubeMap();
		
		bool loaded = false;
		for ( int texure = 0; texure < 6U; ++texure )
		{
			loaded = loadImage(newTexture->m_cubeMapData[texure],_imageFile[texure]);
			if (!loaded)
			{
				break;
			}
		}

		if (loaded)
		{
			RENDERER->initTextureCubeMap( newTexture->m_iTextureID, newTexture->m_cubeMapData, true );
			
			for ( uint texure = 0; texure < 6U; ++texure )
			{
				LOG_CONSOLE( "Cube Map Texture loaded success: " << _imageFile[texure].c_str() );
			}
							
			m_textures[textureList] = newTexture;
			++m_iCountTextures;
		}

		return (CTexture*)newTexture->getRef();
	}

	//////////////////////////////////////////////////////////////////////////////////////////////
	
	void CTextureManager::destroyTexture( CTexture* _pTexture )
	{
		if ( _pTexture->releaseRef() == 0 )
		{
			TextureList::const_iterator texIter = std::find_if(m_textures.begin(),m_textures.end(),
				boost::bind(&CTextureManager::findTextureByID,this,_1,_pTexture->getTextureID()));
			
			if (texIter != m_textures.end())
			{
				CTexture* texture = (*texIter).second;
				delete texture;
				texture = nullptr;

				m_textures.erase(texIter);
				--m_iCountTextures;
			}
			else
			{
				ASSERT( false && "Texture not Found" );
			}
		}
	}

	//////////////////////////////////////////////////////////////////////////////////////////////

}