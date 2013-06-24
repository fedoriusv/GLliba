#ifndef _CTEXTUREMANAGER_H_
#define _CTEXTUREMANAGER_H_

#include "CSingleton.h"
#include "Types.h"

#include <vector>
#include <map>



namespace glliba
{
	///////////////////////////////////////////////////////////////////////////////////////////

	class	CTexture;
	struct	STextureData2D;

	typedef std::vector<std::string>		StringList;
	typedef std::pair<StringList,CTexture*>	Texture;
	typedef std::map<StringList, CTexture*>	TextureList; 

	class CTextureManager : public CSingleton<CTextureManager>
	{
	private:

		uint					m_iCountTextures;
		TextureList				m_textures;

		bool					findTextureByID( const Texture _texture, uint _iTextureID ) const;
#ifdef _USE_DEVIL
		bool					loadImageDevil( STextureData2D& _textureData, const std::string& _imageFile );
#endif

	public:

		CTextureManager();
		virtual					~CTextureManager();

		CTexture*				createTexture( const std::string& _imageFile     );
		CTexture*				createCubeMap( const std::string  _imageFiles[6] );
		void					destroyTexture( CTexture* _pTexture );

		void					transformString( std::string& _string, bool _toLower = true );
		bool					loadImage(STextureData2D& _textureData, const std::string& _imageFile );
	
	
	};

	///////////////////////////////////////////////////////////////////////////////////////////

#define TEXTURE_MGR	glliba::CTextureManager::getInstance()

	///////////////////////////////////////////////////////////////////////////////////////////
}

#endif