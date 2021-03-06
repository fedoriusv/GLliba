#ifndef _CSCENEMANAGER_H_
#define _CSCENEMANAGER_H_

#include <vector>
#include <algorithm>

#include "CSingleton.h"
#include "CNode.h"
#include "CLight.h"

namespace glliba
{
	//////////////////////////////////////////////////////////////////////////////////////////////
	class CTexture;
	class CFog;
	class CCamera;
	class CShader;
	
	class CSceneManager : public CSingleton<CSceneManager>
	{
	private:

		std::vector<CNode*>	m_objects;
		std::vector<CNode*>	m_subObjects;
		
		CCamera*			m_pCamera;
		CFog*				m_pFog;

		void				update( double _deltaTime );

		double				m_dCurrentTime;
		double				m_dDeltaTime;
		double				m_dLastTime;
		void				updateDeltaTime();

	public:

		CSceneManager();
		virtual				~CSceneManager();

		void				init();

		void				draw();
	
		void				clear();
		bool				drop( CNode* _object );

		void				setActiveCamera( CCamera* _camera );
		CCamera*			getActiveCamera() const;

		void				setActiveFog( CFog* _fog );
		CFog*				getActiveFog() const;

		CObject*			getObjectByID( const uint _id );
		CObject*			getObjectByName( const std::string& _name );

		//void				setEnabledCullFace( bool _cullFase );
		//void				setPolygonMode();
		void				setActiveDebug( bool _bIsShowNormals );

		double				getDeltaTime() const;
								
		//////////////////////////////////////////////////////////////////////////////////////////////

		CTexture*			addRenderTargetTexture( uint _iWidth, uint _iHeight );
		void				setRenderTarget( uint id, CTexture* _pTexture, Vector3 _fontColor = Vector3(0.0f));

		//////////////////////////////////////////////////////////////////////////////////////////////

		void				addNode( CNode* _object );
		void				addSubNode( CNode* _object );

		CNode*				addFog(
								const std::string = "fog",
								const Vector4& _color = Vector4(1.0f),
								const float& _begin = 5.0f,
								const float& _end = 30.0f );

		CNode*				addLight(
								CNode* _parent = NULL,
								const std::string _attribute = "light0",
								const Vector3& _pos = Vector3(0.0f,0.0f,1.0f),
								const Vector4& _diffuse = Vector4(1.0f,1.0f,1.0f,1.0f),
								const float& _radius = 100.0f );

		CNode*				addCamera(
								CNode* _parent = NULL,
								const Vector3& _pos = Vector3(0.0f,0.0f,0.0f),
								const Vector3& _target = Vector3(0.0f,0.0f,-1.0f),
								const Vector3& _up = Vector3(0.0f,1.0f,0.0f));

		CNode*				addFPSCamera(
								CNode* _parent = NULL,
								const Vector3& _pos = Vector3(0.0f,0.0f,0.0f),
								const Vector3& _target = Vector3(0.0f,0.0f,-1.0f),
								const Vector3& _up = Vector3(0.0f,1.0f,0.0f));

		CNode*				addCube(
								CNode* _parent = NULL, 
								const Vector3& _pos = Vector3(0.0f,0.0f,0.0f), 
								const float& _size = 1.0f );

		CNode*				addSphere(
								CNode* _parent = NULL, 
								const Vector3& _pos = Vector3(0.0f,0.0f,0.0f), 
								const float& _radius = 1.0f);

		CNode*				addCylinder(
								CNode* _parent = NULL, 
								const Vector3& _pos = Vector3(0.0f,0.0f,0.0f), 
								const float& _radius = 0.5,
								const float& _height = 1.0f);

		CNode*				addDisk(
								CNode* _pParent = NULL, 
								const Vector3& _pos = Vector3(0.0f,0.0f,0.0f), 
								const float& _innerRadius = 1.0f,
								const float& _outerRadius = 2.0f);

		CNode*				addTorus(
								CNode* _parent = NULL, 
								const Vector3& _pos = Vector3(0.0f,0.0f,0.0f), 
								const float& _majorRadius = 1.0f,
								const float& _minorRadius = 0.5f);

		CNode*				addPlane(
								CNode* _parent = NULL, 
								const Vector3& _pos = Vector3(0.0f,0.0f,0.0f));

		CNode*				addModel(
								const std::string& _nameFile,
								CNode* _parent = NULL, 
								const Vector3& _pos = Vector3(0.0f,0.0f,0.0f));

		CNode*				addSkyBox( 
								const std::string _skyBox[6] );

		CNode*				addFreeTypeFont(
								const std::string& _string,
								CNode* _parent = NULL, 
								const Vector3& _pos = Vector3(0.0f),
								const uint& _size = 24U,
								const Vector4& _color = Vector4(1.0f),
								const std::string& _fontName = "arial.ttf" );

	};

	//////////////////////////////////////////////////////////////////////////////////////////////
}
#endif