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
#include "CSkyBox.h"
#include "CFreeTypeFont.h"

#include "CRender.h"

#include <time.h>
#include <boost/bind.hpp>

namespace glliba
{
	//////////////////////////////////////////////////////////////////////////////////////////////

	CSceneManager::CSceneManager()
		: m_pCamera(nullptr)
		, m_pFog(nullptr)

		, m_dCurrentTime(0.0)
		, m_dDeltaTime(0.0)
		, m_dLastTime(0.0)
	{
	}

	
	CSceneManager::~CSceneManager()
	{
		CSceneManager::clear();
	}

	
	void CSceneManager::addNode( CNode* _object )
	{
		m_objects.push_back(_object);
	}

	
	void CSceneManager::addSubNode( CNode* _object )
	{
		m_subObjects.push_back(_object);
	}

	
	void CSceneManager::init()
	{
		for (std::vector<CNode*>::iterator iter = m_objects.begin(); iter < m_objects.end(); ++iter )
		{
			CNode* pItem = (*iter);
			pItem->init();
		}
	}

		
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

			for (CNode* object : m_subObjects)
			{
				object->render();
			}
		}

		CRender::getInstance()->endRender();
	}

	
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

	
	double CSceneManager::getDeltaTime() const
	{
		return m_dDeltaTime;
	}

	
	void CSceneManager::update( double _deltaTime )
	{
		for (auto iter = m_objects.begin(); iter < m_objects.end(); ++iter )
		{
			CNode* pItem = (*iter);
			switch(pItem->getNodeType())
			{
			case TYPE_NODE::TN_SHAPE:
			case TYPE_NODE::TN_MODEL:
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
			case TYPE_NODE::TN_CAMERA:
				{
					float priority = 1000000.0f;
					pItem->m_fPriority = priority; 
				}
				break;
			}
		}

		std::sort(m_objects.begin(),m_objects.end(), 
			[]( CNode* _obj0, CNode* _obj1 )
			{
				return  (_obj0->getPriority() > _obj1->getPriority());
			} );
	}

	
	void CSceneManager::clear()
	{
		for( CNode* object: m_objects ) 
		{
			delete object;
			object = nullptr;
		}
		m_objects.clear();


		for( CNode* object: m_subObjects ) 
		{
			delete object;
			object = nullptr;
		}
		m_subObjects.clear();
	}

	
	bool CSceneManager::drop( CNode* _object )
	{
		auto iter = std::find( m_objects.begin(), m_objects.end(), _object );
		
		if  ( iter != m_objects.end() )
		{
			delete (*iter);
			(*iter) = nullptr;
			m_objects.erase(iter);

			return true;
		}

		return false;
	}

	
	CObject* CSceneManager::getObjectByID( const uint _id )
	{
		std::function<bool(const CObject* _obj, const uint _id )> 
			objectByID = [](const CObject* _obj, const uint _id)
			{
				return _obj->getID() == _id;
			};

		auto iter = std::find_if(m_objects.begin(),m_objects.end(),boost::bind(objectByID,_1,_id));

		if (iter != m_objects.end())
		{
			return (*iter);
		}

		return nullptr;
	}

	
	CObject* CSceneManager::getObjectByName( const std::string& _name )
	{
		std::function<bool(const CObject* _obj, const std::string& _name)> 
			objectByName = [](const CObject* _obj, const std::string& _name)
			{
				return (_obj->getName().compare(_name) == 0) ? true : false;
			};

		auto iter = std::find_if(m_objects.begin(),m_objects.end(),boost::bind(objectByName,_1,_name));

		if (iter != m_objects.end())
		{
			return (*iter);
		}

		return nullptr;
	}

	
	void CSceneManager::setActiveCamera( CCamera* _camera )
	{
		if (m_pCamera)
		{
			m_pCamera->m_bIsActive = false;
		}
		m_pCamera = _camera;
		m_pCamera->m_bIsActive = true;
	}

	
	CFog* CSceneManager::getActiveFog() const
	{
		return m_pFog;
	}

	
	void CSceneManager::setActiveFog( CFog* _fog )
	{
		if (m_pFog)
		{
			m_pFog->m_bActive = false;
		}
		m_pFog = _fog;
		m_pFog->m_bActive = true;
	}

	
	CCamera* CSceneManager::getActiveCamera() const
	{
		return m_pCamera;
	}

	
	void CSceneManager::setActiveDebug( bool _bIsShowNormals )
	{
		CRender::getInstance()->setActiveDebug( _bIsShowNormals );
	}

	
	CTexture* CSceneManager::addRenderTargetTexture( uint _iWidth, uint _iHeight )
	{
		return CResourceManager::getInstance()->createRenderTarget(_iWidth,_iHeight);
	}

		
	void CSceneManager::setRenderTarget( uint _id, CTexture* _pTexture, Vector3 _fontColor)
	{
		CRender::getInstance()->renderToTexture(_id,1);
	}

	
	CNode* CSceneManager::addLight( CNode* _parent, const std::string _attribute,
		const Vector3& _pos, const Vector4& _diffuse, const float& _radius )
	{
		CLight* light = new CLight( _parent );
		(light)->setPosition( _pos );
		(light)->setDiffuseLight( _diffuse );
		(light)->setRadiusLight( _radius );
		(light)->setAttributeLight( _attribute );

		CSceneManager::addSubNode(light);
		return light;
	}

	
	CNode* CSceneManager::addFog( const std::string, const Vector4& _color,
		const float& _start, const float& _end )
	{
		CFog* obj = new CFog();
		(obj)->setColor( _color );
		(obj)->setStart( _start );
		(obj)->setEnd( _end );
		if (m_pFog)
		{
			m_pFog->m_bActive = false;
		}
		m_pFog = static_cast<CFog*>(obj);
		m_pFog->m_bActive = true;
		
		CSceneManager::addSubNode(obj);
		return obj;
	}

	
	CNode* CSceneManager::addCamera( CNode* _parent, const Vector3& _pos,
		const Vector3& _target, const Vector3& _up )
	{
		CCamera* obj = new CCamera( _parent );
		(obj)->setPosition( _pos );
		(obj)->setTarget( _target );
		(obj)->setUpVector( _up );
		if (m_pCamera)
		{
			m_pCamera->m_bIsActive = false;
		}
		m_pCamera = static_cast<CCamera*>(obj);
		m_pCamera->m_bIsActive = true;

		CSceneManager::addNode(obj);
		return obj;
	}

	
	CNode* CSceneManager::addFPSCamera( CNode* _parent, const Vector3& _pos,
		const Vector3& _target, const Vector3& _up )
	{
		CCamera* obj = new CFPSCamera( _parent );
		(obj)->setPosition( _pos );
		(obj)->setTarget( _target );
		(obj)->setUpVector( _up );
		if (m_pCamera)
		{
			m_pCamera->m_bIsActive = false;
		}
		m_pCamera = static_cast<CCamera*>(obj);
		m_pCamera->m_bIsActive = true;

		CSceneManager::addNode(obj);
		return obj;
	}

	
	CNode* CSceneManager::addCube( CNode* _parent, const Vector3& _pos, const float& _size )
	{
		CCubeShape* obj = new CCubeShape( _parent );
		(obj)->setPosition( _pos );
		(obj)->setScale(Vector3(_size));

		CSceneManager::addNode(obj);
		return obj;
	}

	
	CNode* CSceneManager::addSphere( CNode* _parent, const Vector3& _pos, const float& _radius)
	{
		CSphereShape* obj = new CSphereShape( _parent );
		(obj)->setPosition( _pos );
		(obj)->setScale( Vector3(_radius,_radius,_radius));

		CSceneManager::addNode(obj);
		return obj;
	}

	
	CNode* CSceneManager::addTorus( CNode* _parent, const Vector3& _pos,
		const float& _majorRadius, const float& _minorRadius)
	{
		CTorusShape* obj = new CTorusShape( _parent );
		(obj)->setPosition( _pos );
		(obj)->setMajorRadius(_majorRadius);
		(obj)->setMinorRadius(_minorRadius);
		
		CSceneManager::addNode(obj);
		return obj;
	}

	
	CNode* CSceneManager::addCylinder( CNode* _parent, const Vector3& _pos,
		const float& _radius, const float& _height)
	{
		CCylinderShape* obj = new CCylinderShape( _parent );
		(obj)->setPosition( _pos );
		(obj)->setRadius(_radius);
		(obj)->setHeight(_height);

		CSceneManager::addNode(obj);
		return obj;
	}

	
	CNode* CSceneManager::addDisk( CNode* _parent, const Vector3& _pos,
		const float& _innerRadius, const float& _outerRadius )
	{
		CDiskShape* obj = new CDiskShape( _parent );
		obj->setPosition( _pos );
		(obj)->setInnerRadius(_innerRadius);
		(obj)->setOuterRadius(_outerRadius);

		CSceneManager::addNode(obj);
		return obj;
	}

	
	CNode* CSceneManager::addPlane( CNode* _parent, const Vector3& _pos)
	{
		CNode* obj = new CPlaneShape( _parent );
		obj->setPosition( _pos );
		
		CSceneManager::addNode(obj);
		return obj;
	}

	
	CNode* CSceneManager::addModel( const std::string& _nameFile, CNode* _parent, const Vector3& _pos )
	{
		CNode* obj = ResourceMgr->loadModel(_nameFile);
		obj->setParent(_parent);
		obj->setPosition( _pos );
				
		CSceneManager::addNode(obj);
		return obj;
	}

	
	CNode* CSceneManager::addSkyBox( const std::string _skyBox[6] )
	{
		CSkyBox* obj = new CSkyBox();
		obj->loadSkyBox( _skyBox );

		CSceneManager::addNode(obj);
		return obj;
	}


	CNode* CSceneManager::addFreeTypeFont( const std::string& _string, const uint& _posX, const uint& _posY,
		const uint& _size, const std::string& _fontName )
	{
		CFreeTypeFont* obj = new CFreeTypeFont();
		obj->loadSystemFont(_fontName);

		return obj;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////

}