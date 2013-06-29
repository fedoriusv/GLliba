#ifndef _CRESOURCEMANAGER_H_
#define _CRESOURCEMANAGER_H_

#include "CSingleton.h"
#include <vector>


#include "CModel.h"
#include "CShader.h"


namespace glliba
{
	//////////////////////////////////////////////////////////////////////////////////////////////

	class CResourceManager : public CSingleton<CResourceManager>
	{
	private:

		uint					m_nCountRes;

		std::string				getExtensionFile( const std::string& _nameFile );

	public:
		CResourceManager();
		virtual					~CResourceManager();

		void					transformString( std::string& _string, bool _toLower = true );

		CModel*					loadModel( const std::string& _nameFile );

		CTexture*				createRenderTarget(uint _iWidth, uint _iHeight);

	};

	//////////////////////////////////////////////////////////////////////////////////////////////

#define ResourceMgr	CResourceManager::getInstance()

	//////////////////////////////////////////////////////////////////////////////////////////////
}

#endif