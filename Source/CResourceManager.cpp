#include "CResourceManager.h"

#include "CRender.h"
#include "CRenderTarget.h"
#include "CModel3DS.h"
#include "CModelF3D.h"
#include <boost/bind.hpp>

namespace glliba
{
	//////////////////////////////////////////////////////////////////////////////////////////////

	CResourceManager::CResourceManager()
		: m_nCountRes(0)
	{
	}

	//////////////////////////////////////////////////////////////////////////////////////////////

	CResourceManager::~CResourceManager()
	{
	}

	//////////////////////////////////////////////////////////////////////////////////////////////

	void CResourceManager::transformString( std::string& _string,  bool _toLower )
	{
		std::transform( _string.begin(), _string.end(), _string.begin(), _toLower ? ::tolower : ::toupper );
	}

	//////////////////////////////////////////////////////////////////////////////////////////////

	CModel* CResourceManager::loadModel( const std::string& _nameFile )
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