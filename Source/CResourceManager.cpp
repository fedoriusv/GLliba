#include "CResourceManager.h"

#include "CRender.h"
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
		
	}

	//////////////////////////////////////////////////////////////////////////////////////////////

	void CResourceManager::transformString( std::string& _string,  bool _toLower )
	{
		std::transform( _string.begin(), _string.end(), _string.begin(), _toLower ? ::tolower : ::toupper );
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