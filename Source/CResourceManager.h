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

		std::vector<CShader*>	m_shaderList;

		bool					findShaderByFileName( const CShader* _shader, const std::string& _vertexShader, const std::string& _fragmentShader ) const;
		bool					findShaderByShaderID( const CShader* _shader, uint _shaderID ) const;

		std::string				getExtensionFile( const std::string& _nameFile );

	public:
		CResourceManager();
		virtual					~CResourceManager();

		CShader*				createShader( const std::string& _vertShader, const std::string& _fragShader );
		void					destroyShader( CShader* _shader );

		void					transformString( std::string& _string, bool _toLower = true );

		CModel*					loadModel( const std::string& _nameFile );

		CTexture*				createRenderTarget(uint _iWidth, uint _iHeight);

	};

	//////////////////////////////////////////////////////////////////////////////////////////////

#define ResourceMgr	glliba::CResourceManager::getInstance()

	//////////////////////////////////////////////////////////////////////////////////////////////
}

#endif