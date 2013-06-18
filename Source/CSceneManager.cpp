#include "CSceneManager.h"

#include "CLight.h"
#include "CFog.h"
#include "CFPSCamera.h"
#include "CCubeShape.h"
#include "CSphereShape.h"
#include "CCylinderShape.h"
#include "CDiskShape.h"
#include "CTorusShape.h"
#include "CPlaneShape.h"
#include "CResourceManager.h"
#include "CShader.h"
#include "CModel3DS.h"
#include "CModelF3D.h"

#include "CRender.h"

#include <time.h>

namespace glliba
{
	//////////////////////////////////////////////////////////////////////////////////////////////

	bool sortByDepth( CNode* _obj0, CNode* _obj1 )
	{
		return  (_obj0->getPriority() > _obj1->getPriority());
	}

	//////////////////////////////////////////////////////////////////////////////////////////////

	uint	CSceneManager::s_iCount = 0;

	//////////////////////////////////////////////////////////////////////////////////////////////

	CSceneManager::CSceneManager()
		: m_pCamera(NULL)
		, m_pFog(NULL)
		, m_pShader(NULL)

		, m_dCurrentTime(0.0)
		, m_dDeltaTime(0.0)
		, m_dLastTime(0.0)
	{
	}

	//////////////////////////////////////////////////////////////////////////////////////////////

	CSceneManager::~CSceneManager()
	{
		for (std::vector<CNode*>::iterator iter = m_objects.begin(); iter < m_objects.end(); ++iter )
		{
			delete (*iter);
			(*iter) = NULL;
		}

		m_objects.clear();
	}

	//////////////////////////////////////////////////////////////////////////////////////////////

	void CSceneManager::addNode( CNode* _pObject )
	{
		m_objects.push_back(_pObject);
		++s_iCount;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////

	void CSceneManager::init()
	{
		for (std::vector<CNode*>::iterator iter = m_objects.begin(); iter < m_objects.end(); ++iter )
		{
			CNode* pItem = (*iter);
			pItem->init();
		}
	}

	//////////////////////////////////////////////////////////////////////////////////////////////
	
	void CSceneManager::draw()
	{
		CSceneManager::updateDeltaTime();
		CSceneManager::update(m_dDeltaTime);
								
		CRender::getInstance()->beginRender();

		for (std::vector<CNode*>::iterator iter = m_objects.begin(); iter < m_objects.end(); ++iter )
		{
			CNode* pItem = (*iter);

			pItem->update(m_dDeltaTime);
			pItem->render();
		}

		CRender::getInstance()->endRender();
	}

	//////////////////////////////////////////////////////////////////////////////////////////////

	void CSceneManager::updateDeltaTime()
	{
#ifdef _WIN32
		LARGE_INTEGER nTime;
		QueryPerformanceCounter(&nTime);
		m_dCurrentTime = (double)nTime.QuadPart;
#endif
		m_dDeltaTime = (m_dCurrentTime - m_dLastTime) * 0.001;
		m_dLastTime = m_dCurrentTime;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////

	double CSceneManager::getDeltaTime() const
	{
		return m_dDeltaTime;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////

	void CSceneManager::update( double _dDeltaTime )
	{
		for (std::vector<CNode*>::iterator iter = m_objects.begin(); iter < m_objects.end(); ++iter )
		{
			CNode* pItem = (*iter);
			switch(pItem->getNodeType())
			{
			case TYPE_NODE::TN_SHAPE:
				{
					if (static_cast<CShape*>(pItem)->getMaterial()->getTransparency() > 0.0f)
					{
						float priority = 0.0f;
						if (m_pCamera)
						{
							priority = length(pItem->getPosition() - m_pCamera->getPosition());
						}
						else
						{
							priority = pItem->getPosition().getZ();
						}
						pItem->m_fPriority = priority;
					}
				}
				break;
			case TYPE_NODE::TN_MODEL:
				{
				}
				break;
			case TYPE_NODE::TN_CAMERA:
				{
					float priority = 1000000.0f;
					pItem->m_fPriority = priority; 
				}
				break;
			}
		}

		std::sort(m_objects.begin(),m_objects.end(),sortByDepth);
	}

	//////////////////////////////////////////////////////////////////////////////////////////////

	void CSceneManager::clear()
	{
		for (std::vector<CNode*>::iterator iter = m_objects.begin(); iter < m_objects.end(); ++iter )
		{
			delete (*iter);
			(*iter) = NULL;
		}

		m_objects.clear();
	}

	//////////////////////////////////////////////////////////////////////////////////////////////

	bool CSceneManager::drop( CNode* _pObject )
	{
		std::vector<CNode*>::iterator iter = std::find( m_objects.begin(), m_objects.end(), _pObject );
		
		if  ( iter != m_objects.end() )
		{
			delete (*iter);
			(*iter) = NULL;
			m_objects.erase(iter);

			return true;
		}

		return false;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////

	CObject* CSceneManager::getObjectByID( const uint _iId )
	{
		for (std::vector<CNode*>::iterator iter = m_objects.begin(); iter < m_objects.end(); ++iter )
		{
			if ((*iter)->getID() == _iId )
			{
				return (*iter);
			}
		}

		return NULL;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////

	CObject* CSceneManager::getObjectByName( std::string _name )
	{
		for (std::vector<CNode*>::const_iterator iter = m_objects.begin(); iter < m_objects.end(); ++iter )
		{
			if ( (*iter)->getName().compare(_name) == 0 )
			{
				return (*iter);
			}
		}

		return NULL;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////

	void CSceneManager::setActiveCamera( CCamera* _pCamera )
	{
		if (m_pCamera)
		{
			m_pCamera->m_bIsActive = false;
		}
		m_pCamera = _pCamera;
		m_pCamera->m_bIsActive = true;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////

	CFog* CSceneManager::getActiveFog() const
	{
		return m_pFog;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////

	void CSceneManager::setActiveFog( CFog* _pFog )
	{
		if (m_pFog)
		{
			m_pFog->m_bActive = false;
		}
		m_pFog = _pFog;
		m_pFog->m_bActive = true;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////

	CCamera* CSceneManager::getActiveCamera() const
	{
		return m_pCamera;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////

	void CSceneManager::setActiveDebug( bool _bIsShowNormals )
	{
		CRender::getInstance()->setActiveDebug( _bIsShowNormals );
	}

	//////////////////////////////////////////////////////////////////////////////////////////////

	CTexture* CSceneManager::addRenderTargetTexture( uint _iWidth, uint _iHeight )
	{
		return CResourceManager::getInstance()->createRenderTarget(_iWidth,_iHeight);
	}
	
	void CSceneManager::setRenderTarget( uint _id, CTexture* _pTexture, Vector3 _fontColor)
	{
		CRender::getInstance()->renderToTexture(_id,1);
	}

	//////////////////////////////////////////////////////////////////////////////////////////////

	CNode* CSceneManager::addLight( CNode* _pParent, const std::string _attribute,
		const Vector3& _pos, const Vector4& _diffuse, const float& _radius )
	{
		CLight* obj = new CLight( _pParent );
		(obj)->setPosition( _pos );
		(obj)->setDiffuseLight( _diffuse );
		(obj)->setRadiusLight( _radius );
		(obj)->setAttributeLight( _attribute );

		CSceneManager::addNode(obj);
		return obj;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////

	CNode* CSceneManager::addFog( const Vector4& _color, const float& _start, const float& _end )
	{
		CNode* obj = new CFog();
		static_cast<CFog*>(obj)->setColor( _color );
		static_cast<CFog*>(obj)->setStart( _start );
		static_cast<CFog*>(obj)->setEnd( _end );
		if (m_pFog)
		{
			m_pFog->m_bActive = false;
		}
		m_pFog = static_cast<CFog*>(obj);
		m_pFog->m_bActive = true;
		
		CSceneManager::addNode(obj);
		return obj;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////

	CNode* CSceneManager::addCamera( CNode* _pParent, const Vector3& _pos, const Vector3& _target, const Vector3& _up )
	{
		CNode* obj = new CCamera( _pParent );
		static_cast<CCamera*>(obj)->setPosition( _pos );
		static_cast<CCamera*>(obj)->setTarget( _target );
		static_cast<CCamera*>(obj)->setUpVector( _up );
		if (m_pCamera)
		{
			m_pCamera->m_bIsActive = false;
		}
		m_pCamera = static_cast<CCamera*>(obj);
		m_pCamera->m_bIsActive = true;

		CSceneManager::addNode(obj);
		return obj;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////

	CNode* CSceneManager::addFPSCamera( CNode* _pParent, const Vector3& _pos, const Vector3& _target, const Vector3& _up )
	{
		CNode* obj = new CFPSCamera( _pParent );
		static_cast<CCamera*>(obj)->setPosition( _pos );
		static_cast<CCamera*>(obj)->setTarget( _target );
		static_cast<CCamera*>(obj)->setUpVector( _up );
		if (m_pCamera)
		{
			m_pCamera->m_bIsActive = false;
		}
		m_pCamera = static_cast<CCamera*>(obj);
		m_pCamera->m_bIsActive = true;

		CSceneManager::addNode(obj);
		return obj;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////

	CNode* CSceneManager::addCube( CNode* _pParent, const Vector3& _pos, const float& _size )
	{
		CCubeShape* obj = new CCubeShape( _pParent );
		(obj)->setPosition( _pos );
		(obj)->setScale(Vector3(_size));

		CSceneManager::addNode(obj);
		return obj;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////

	CNode* CSceneManager::addSphere( CNode* _pParent,	const Vector3& _pos, const float& _radius)
	{
		CNode* obj = new CSphereShape( _pParent );
		static_cast<CSphereShape*>(obj)->setPosition( _pos );
		static_cast<CSphereShape*>(obj)->setScale( Vector3(_radius,_radius,_radius));

		CSceneManager::addNode(obj);
		return obj;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////

	CNode* CSceneManager::addTorus( CNode* _pParent, const Vector3& _pos, const float& _majorRadius, const float& _minorRadius)
	{
		CNode* obj = new CTorusShape( _pParent );
		static_cast<CTorusShape*>(obj)->setPosition( _pos );
		static_cast<CTorusShape*>(obj)->setMajorRadius(_majorRadius);
		static_cast<CTorusShape*>(obj)->setMinorRadius(_minorRadius);
		
		CSceneManager::addNode(obj);
		return obj;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////

	CNode* CSceneManager::addCylinder( CNode* _pParent, const Vector3& _pos, const float& _radius, const float& _height)
	{
		CNode* obj = new CCylinderShape( _pParent );
		static_cast<CCylinderShape*>(obj)->setPosition( _pos );
		static_cast<CCylinderShape*>(obj)->setRadius(_radius);
		static_cast<CCylinderShape*>(obj)->setHeight(_height);

		CSceneManager::addNode(obj);
		return obj;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////

	CNode* CSceneManager::addDisk( CNode* _pParent, const Vector3& _pos, const float& _radius )
	{
		CNode* obj = new CDiskShape( _pParent );
		obj->setPosition( _pos );
		static_cast<CDiskShape*>(obj)->setRadius(_radius);

		CSceneManager::addNode(obj);
		return obj;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////

	CNode* CSceneManager::addPlane( CNode* _pParent, const Vector3& _pos)
	{
		CNode* obj = new CPlaneShape( _pParent );
		obj->setPosition( _pos );
		
		CSceneManager::addNode(obj);
		return obj;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////

	CNode* CSceneManager::addModel( std::string _nameFile, CNode* _pParent, const Vector3& _pos )
	{
		CNode* obj = ResourceMgr->loadModel(_nameFile);
		obj->setParent(_pParent);
		obj->setPosition( _pos );
				
		CSceneManager::addNode(obj);
		return obj;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////

}