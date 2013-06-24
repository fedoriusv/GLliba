#include "CResourceManager.h"

#include "CRender.h"
#include "CTexture2D.h"
#include "CTextureCubeMap.h"
#include "CRenderTarget.h"
#include "CModel3DS.h"
#include "CModelF3D.h"
#include <boost/bind.hpp>

namespace glliba
{
	//////////////////////////////////////////////////////////////////////////////////////////////

	uint CResourceManager::s_iCountRes = 0;

	//////////////////////////////////////////////////////////////////////////////////////////////

	CResourceManager::CResourceManager()
	{
	}

	//////////////////////////////////////////////////////////////////////////////////////////////

	CResourceManager::~CResourceManager()
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

	void CResourceManager::transformString( std::string& _sting,  bool _toLower )
	{
		std::transform( _sting.begin(), _sting.end(), _sting.begin(), _toLower ? ::tolower : ::toupper );
	}

	//////////////////////////////////////////////////////////////////////////////////////////////

	bool CResourceManager::loadImage( STextureData2D& _textureData, const std::string& _imageFile )
	{
#ifdef _USE_DEVIL
		return loadImageDevil( _textureData, _imageFile );
#endif
		return false;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////

#ifdef _USE_DEVIL
	bool CResourceManager::loadImageDevil( STextureData2D& _textureData, const std::string& _imageFile )
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

	bool CResourceManager::findTextureByID( const Texture _texture, uint _iTextureID ) const
	{
		return _texture.second->m_iTextureID == _iTextureID;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////

	bool CResourceManager::findShaderByFileName( const CShader* _pShader, const std::string& _vertexShader, const std::string& _fragmentShader ) const
	{
		return (_pShader->m_vertexProgram.m_shaderName.compare(_vertexShader) == 0 &&
			_pShader->m_fragmentProgram.m_shaderName.compare(_fragmentShader) == 0 ? true : false); 
	}

	//////////////////////////////////////////////////////////////////////////////////////////////

	bool CResourceManager::findShaderByShaderID( const CShader* _pShader, uint _iShaderID ) const
	{
		return _pShader->m_iShaderID == _iShaderID;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////

	CTexture* CResourceManager::createTexture( const std::string& _imageFile )
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
			++s_iCountRes;
		}

		return (CTexture*)newTexture->getRef();
	}

	//////////////////////////////////////////////////////////////////////////////////////////////

	CTexture* CResourceManager::createCubeMap( const std::string _imageFile[6] )
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
			++s_iCountRes;
		}

		return (CTexture*)newTexture->getRef();
	}

	//////////////////////////////////////////////////////////////////////////////////////////////
	
	void CResourceManager::destroyTexture( CTexture* _pTexture )
	{
		if ( _pTexture->releaseRef() == 0 )
		{
			TextureList::const_iterator texIter = std::find_if(m_textures.begin(),m_textures.end(),
				boost::bind(&CResourceManager::findTextureByID,this,_1,_pTexture->getTextureID()));
			
			if (texIter != m_textures.end())
			{
				CTexture* texture = (*texIter).second;
				delete texture;
				texture = nullptr;

				m_textures.erase(texIter);
			}
			else
			{
				ASSERT( false && "Texture not Found" );
			}
		}
	}

	//////////////////////////////////////////////////////////////////////////////////////////////

	CShader* CResourceManager::createShader( const std::string& _vertShader, const std::string& _fragShader )
	{
		std::vector<CShader*>::iterator shaderIter = std::find_if( m_shaderList.begin(), m_shaderList.end(),
			boost::bind(&CResourceManager::findShaderByFileName,this,_1,_vertShader,_fragShader) );

		if (shaderIter != m_shaderList.end())
		{
			return (CShader*)(*shaderIter)->getRef();
		}

		CShader* newShader = new CShader();
		newShader->loadShader(_vertShader,_fragShader);

		m_shaderList.push_back(newShader);
		++s_iCountRes;

		return (CShader*)newShader->getRef();
	}

	//////////////////////////////////////////////////////////////////////////////////////////////

	void CResourceManager::destroyShader( CShader* _pShader )
	{
		if ( _pShader->releaseRef() == 0 )
		{
			std::vector<CShader*>::iterator shaderIter = std::find_if( m_shaderList.begin(), m_shaderList.end(),
				boost::bind(&CResourceManager::findShaderByShaderID,this,_1,_pShader->m_iShaderID) );

			if (shaderIter != m_shaderList.end())
			{
				CShader* shader = (*shaderIter);
				m_shaderList.erase(shaderIter);

				delete shader;
				shader = nullptr;
			}
			else
			{
				ASSERT( false && "Texture not Found" );
			}
		}
	}

	//////////////////////////////////////////////////////////////////////////////////////////////

	CModel* CResourceManager::loadModel( const std::string _nameFile )
	{
		std::string name = _nameFile;
		ResourceMgr->transformString( name, true );
		
		const std::string extens = getExtensionFile(name);
		
		CModel* model = NULL;
		if( extens.compare("f3d") == 0 )
		{
			model = new CModelF3D(NULL);
		}
		else if( extens.compare("3ds") == 0 )
		{
			model = new CModel3DS(NULL);
		}
		else
		{
			ASSERT(true && "Unknown file format");
			return NULL;
		}

		model->loadFromFile(_nameFile);

		return model;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////

	std::string CResourceManager::getExtensionFile( const std::string& _nameFile )
	{
		size_t pos = _nameFile.rfind('.');
		if(pos != std::string::npos)
		{
			return std::string(_nameFile.begin()+pos+1, _nameFile.end());
		}

		return std::string("");
	}

	//////////////////////////////////////////////////////////////////////////////////////////////

	CTexture* CResourceManager::createRenderTarget(uint _iWidth, uint _iHeight)
	{
		CRenderTarget* emptyTexture = new CRenderTarget();
		

		emptyTexture->m_sTextureData._iWidth = _iWidth;
		emptyTexture->m_sTextureData._iHeight = _iHeight;

		CRender::getInstance()->initRenderTarget(emptyTexture->m_iFrameBuffID, emptyTexture->m_iTextureID,_iWidth,_iHeight);

		return emptyTexture;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////

}