#include "CApplication.h"

#include "CShape.h"
#include "CModel.h"
#include "CLight.h"
#include "CTorusShape.h"
#include "CRenderGL.h"
#include "CResourceManager.h"
#include "CTextureManager.h"
#include "CShaderManager.h"

CApplication::CApplication()
{
	m_scene = CSceneManager::getInstance();
	m_render =  CRender::getInstance();
	m_reciever = CReciever::getInstance();
}

CApplication::~CApplication()
{
	CSceneManager::freeInstance();
	CReciever::freeInstance();
	CResourceManager::freeInstance();
	CShaderManager::freeInstance();
	CTextureManager::freeInstance();
}

CReciever* CApplication::getReciever()
{
	return m_reciever;
}

void CApplication::init()
{
	//TODO: Create objects--------------------------------------------------------------------
	m_scene->setActiveDebug(true);
	const std::string skybox[6] = { "data/skybox/jajlands/jajlands1_ft.jpg",
									"data/skybox/jajlands/jajlands1_bk.jpg",
									"data/skybox/jajlands/jajlands1_lf.jpg",
									"data/skybox/jajlands/jajlands1_rt.jpg",
									"data/skybox/jajlands/jajlands1_up.jpg",
									"data/skybox/jajlands/jajlands1_dn.jpg", };
	m_scene->addSkyBox(skybox);

	CNode* cube1 = m_scene->addCube(0,Vector3(-1.0f,1.0f,-2.0f));
	cube1->setName("cube0");

	CNode* cube2 = m_scene->addCube(0,Vector3(-1.0f,1.0f,0.0f));
	cube1->setName("cube0");
	static_cast<CShape*>(cube1)->getMaterial()->setTexture(0,"texture0","Data/Stone.jpg");

	/*CNode* model0 = m_scene->addModel("data/fullscene.f3d", NULL, Vector3(0,0,-5));
	model0->setName("cube0");
	for (int i = 0; i < static_cast<CModel*>(model0)->getMeshCount(); ++i)
	{
		static_cast<CModel*>(model0)->getMesh(i)->getMaterial()->setShader("data/shaders/defaultWithFog.vsh","data/shaders/defaultWithFog.psh");
	}*/
	CNode* light = m_scene->addLight(0,"light0",Vector3(0,0,4));
	
	//Camera
	CNode* Camera0 = m_scene->addFPSCamera(0,Vector3(0,1,0),Vector3(0,0,-3));
	Camera0->setName("camera0");

	//CNode* fog = m_scene->addFog();
	
	//__asm int 3
	//__debugbreak();

	/*initialize*/
	//-----------------------------------------------------------------------------------------
}

void CApplication::run()
{
	/*static_cast<CNode*>(m_scene->getObjectByName("cube1"))->setVisible(true);
	static_cast<CNode*>(m_scene->getObjectByName("cube0"))->setVisible(false);
	m_scene->setActiveCamera(static_cast<CCamera*>(m_scene->getObjectByName("camera1")));
	m_scene->setRenderTarget(1,0);
	m_scene->render();
	m_scene->setRenderTarget(0,0);
	m_scene->setActiveCamera(static_cast<CCamera*>(m_scene->getObjectByName("camera0")));
	static_cast<CNode*>(m_scene->getObjectByName("cube0"))->setVisible(true);
	static_cast<CNode*>(m_scene->getObjectByName("cube1"))->setVisible(false);*/

	m_scene->draw();
	CApplication::updateReciever(m_scene->getDeltaTime());
}

bool CApplication::isExecute()
{
	return true;
}

void CApplication::updateReciever( double _dDeltaTime )
{
	float deltaRot = (float)_dDeltaTime * 0.05f;
	float deltaPos = (float)_dDeltaTime * 0.009f;
	//CShader* shader = static_cast<CModel*>(m_scene->getObjectByName("model0"))->getMesh(0)->getMaterial()->getShader();
	//CShader* shader = static_cast<CShape*>(m_scene->getObjectByName("cube0"))->getMaterial()->getShader();
	//shader->setUniformVector3("eye",static_cast<CNode*>(m_scene->getObjectByName("camera0"))->getPosition());
	
	if (getReciever()->isKeyDown(KEY_LEFT))
	{
		CNode* obj = static_cast<CNode*>(m_scene->getObjectByName("cube0"));
		obj->setRotation(Vector3(obj->getRotation().getX(), obj->getRotation().getY()-deltaRot, obj->getRotation().getZ()));
	}

	if (getReciever()->isKeyDown(KEY_RIGHT))
	{
		CNode* obj = static_cast<CNode*>(m_scene->getObjectByName("cube0"));
		obj->setRotation(Vector3(obj->getRotation().getX(), obj->getRotation().getY()+deltaRot, obj->getRotation().getZ()));
	}

	if (getReciever()->isKeyDown(KEY_UP))
	{
		CNode* obj = static_cast<CNode*>(m_scene->getObjectByName("cube0"));
		obj->setRotation(Vector3(obj->getRotation().getX()+deltaRot, obj->getRotation().getY(), obj->getRotation().getZ()));
	}

	if (getReciever()->isKeyDown(KEY_DOWN))
	{
		CNode* obj = static_cast<CNode*>(m_scene->getObjectByName("cube0"));
		obj->setRotation(Vector3(obj->getRotation().getX()-deltaRot, obj->getRotation().getY(), obj->getRotation().getZ()));
	}

	if (getReciever()->isKeyDown(KEY_NEXT))
	{
		CNode* obj = static_cast<CNode*>(m_scene->getObjectByName("cube0"));
		obj->setRotation(Vector3(obj->getRotation().getX(), obj->getRotation().getY(), obj->getRotation().getZ()+deltaRot));
	}

	if (getReciever()->isKeyDown(KEY_PRIOR))
	{
		CNode* obj = static_cast<CNode*>(m_scene->getObjectByName("cube0"));
		obj->setRotation(Vector3(obj->getRotation().getX(), obj->getRotation().getY(), obj->getRotation().getZ()-deltaRot));
	}

	if (getReciever()->isKeyDown(KEY_KEY_O)) //O
	{
		CNode* obj = static_cast<CNode*>(m_scene->getObjectByName("cube0"));
		obj->setPosition(Vector3(obj->getPosition().getX(), obj->getPosition().getY(), obj->getPosition().getZ()-deltaPos));
	}

	if (getReciever()->isKeyDown(KEY_KEY_L)) //L
	{
		CNode* obj = static_cast<CNode*>(m_scene->getObjectByName("cube0"));
		obj->setPosition(Vector3(obj->getPosition().getX(), obj->getPosition().getY(), obj->getPosition().getZ()+deltaPos));
	}

	if (getReciever()->isKeyDown(KEY_KEY_I)) //I
	{
		CNode* obj = static_cast<CNode*>(m_scene->getObjectByName("cube0"));
		obj->setPosition(Vector3(obj->getPosition().getX(),obj->getPosition().getY()+0.2f,obj->getPosition().getZ()));
	}

	if (getReciever()->isKeyDown(KEY_KEY_K)) //K
	{
		CNode* obj = static_cast<CNode*>(m_scene->getObjectByName("cube0"));
		obj->setPosition(Vector3(obj->getPosition().getX(),obj->getPosition().getY()-0.2f,obj->getPosition().getZ()));
	}

	if (getReciever()->isKeyDown(KEY_KEY_U)) //U
	{
		CNode* obj = static_cast<CNode*>(m_scene->getObjectByName("cube0"));
		obj->setPosition(Vector3(obj->getPosition().getX()+0.2f,obj->getPosition().getY(),obj->getPosition().getZ()));
	}

	if (getReciever()->isKeyDown(KEY_KEY_J)) //J
	{
		CNode* obj = static_cast<CNode*>(m_scene->getObjectByName("cube0"));
		obj->setPosition(Vector3(obj->getPosition().getX()-0.8f,obj->getPosition().getY(),obj->getPosition().getZ()));
	}

	//if (getReciever()->isKeyDown(KEY_SPACE))
	//{
	//	static_cast<CLight*>(light)->setVisible(static_cast<CLight*>(light)->isVisible() ? false : true );
	//	getReciever()->resetKeyPress();
	//}

	//if (getReciever()->isMouseDown(EMIE_MOUSE_WHEEL) )
	//{
	//	int a = 0;
	//	getReciever()->resetKeyPress();
	//	/*CNode* obj = static_cast<CNode*>(m_scene->getObjectByName("cube0"));
	//	obj->setPosition(Vector3(obj->getPosition().getX()-0.8,obj->getPosition().getY(),obj->getPosition().getZ()));*/
	//}

}