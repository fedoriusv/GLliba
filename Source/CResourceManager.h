#ifndef _CRESOURCEMANAGER_H_
#define _CRESOURCEMANAGER_H_

#include <vector>

#include "CSingleton.h"

#include "CModel.h"
#include "CTexture.h"
#include "CShader.h"


namespace glliba
{
	//////////////////////////////////////////////////////////////////////////////////////////////

	class CResourceManager : public CSingleton<CResourceManager>
	{
	private:

		static uint				s_iCountRes;

		std::vector<CTexture*>	m_textureList;
		std::vector<CShader*>	m_shaderList;

		bool					findTextureByFileName( const CTexture* _pTexture, const std::string* _imageFile ) const;
		bool					findCubeMapByFileName( const CTexture* _pTexture, const std::string* _imageFile[6U] ) const;
		bool					findTextureByTextureID( const CTexture* _pTexture, uint _iTextureID ) const;
		
		bool					findShaderByFileName( const CShader* _pShader, const std::string& _vertexShader, const std::string& _fragmentShader ) const;
		bool					findShaderByShaderID( const CShader* _pShader, uint _iShaderID ) const;

#ifdef _USE_DEVIL
		bool					loadImageDevil( STextureData2D& _textureData, const std::string* _imageFile );
#endif
		std::string				getExtensionFile( const std::string* _nameFile );

	public:
		CResourceManager();
		virtual					~CResourceManager();

		CTexture*				createTexture( const std::string* _imageFile    );
		CTexture*				createCubeMap( const std::string _imageFiles[6] );
		void					destroyTexture( CTexture* _pTexture );

		CShader*				createShader( const std::string& _vertShader, const std::string& _fragShader );
		void					destroyShader( CShader* _pShader );

		void					transformString( std::string& _sting, bool _toLower = true );

		CModel*					loadModel( const std::string _nameFile );
		bool					loadImage(STextureData2D& _textureData, const std::string* _imageFile );

		CTexture*				createRenderTarget(uint _iWidth, uint _iHeight);

	};

	//////////////////////////////////////////////////////////////////////////////////////////////

#define ResourceMgr	glliba::CResourceManager::getInstance()

	//////////////////////////////////////////////////////////////////////////////////////////////
}

#endif