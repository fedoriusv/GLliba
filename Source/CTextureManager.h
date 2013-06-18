#ifndef _CTEXTUREMANAGER_H_
#define _CTEXTUREMANAGER_H_

#include <vector>

#include "CSingleton.h"

#include "CTexture2D.h"
#include "CTextureCubeMap.h"



namespace gllib
{
	class CTexture;

	class CTextureManager : public CSingleton<CTextureManager>
	{
	private:
		friend					CTexture;
				
		uint					m_iCount;
		std::vector<CTexture*>	m_textureList;
		CTexture*				findTextureByNames( const std::vector<const char*>* _nameFiles ) const;

	public:
		CTextureManager();
		virtual					~CTextureManager();

		bool					isExist( const CTexture* _texture ) const;

		CTexture*				createTexture2D( const char* _nameFile );
		CTexture*				createTextureCubeMap( const char** _nameFiles );
	
	};
}

#endif