#include "CApplication.h"

#include "CShape.h"
#include "CModel.h"
#include "CLight.h"
#include "CTorusShape.h"
#include "CRenderGL.h"

CApplication::CApplication()
{
	m_scene = CSceneManager::getInstance();
	m_render =  CRenderGL::getInstance();
	m_reciever = CReciever::getInstance();
}

CApplication::~CApplication()
{
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

	CNode* cube0 = m_scene->addCube(0,Vector3(0.0f,0.0f,-6.0f),3);
	cube0->setName("cube1");
	const std::string cubeFaces[6] = {	"data/cubemap/right.tga",
										"data/cubemap/left.tga",
										"data/cubemap/up.tga",
										"data/cubemap/down.tga",
										"data/cubemap/backward.tga",
										"data/cubemap/forward.tga" };

	static_cast<CShape*>(cube0)->getMaterial()->setTexture(0,"texture0",skybox);
	static_cast<CShape*>(cube0)->getMaterial()->setShader("data/defaultCubemap.vsh","data/defaultCubemap.psh");
	//static_cast<CShape*>(cube0)->getMaterial()->setShader("data/simple.vsh","data/simple.psh");
	
	CNode* cube1 = m_scene->addCylinder(0,Vector3(-1.0f,1.0f,-2.0f));
	cube1->setName("cube0");
	static_cast<CShape*>(cube1)->getMaterial()->setTexture(0,"texture0","Data/Stone.jpg");
	//static_cast<CShape*>(cube1)->getMaterial()->setShader("data/defaultCubemap.vsh","data/defaultCubemap.psh");

	/*static_cast<CShape*>(cube1)->getMaterial()->setTexture(1,"texture0","Data/mask123.jpg");
	static_cast<CShape*>(cube1)->getMaterial()->setTexture(0,"texture1","Data/Stone.jpg");
	static_cast<CShape*>(cube1)->getMaterial()->setShader("data/user.vsh","data/user.psh");
	//static_cast<CShape*>(cube1)->getMaterial()->setShader("data/simple01.vsh","data/simple01.psh");*/
	

	/*CNode* model0 = m_scene->addModel("data/cube.f3d", NULL, Vector3(0,0,-5));
	model0->setName("cube0");*/
	

	CNode* light = m_scene->addLight(0,"light0",Vector3(0,0,4));


	//CNode* cube1 = m_scene->addCube(0,Vector3(2.0f,0.0f,-5.0f));
	//static_cast<CShape*>(cube1)->getMaterial()->setTexture(0,"Data/Dirt.jpg");
	//cube1->setName("cube1");
	//
	//CNode* cube1 = m_scene->addCube(0,Vector3(0.0f,2.0f,-2.0f));
	//cube1->setName("cube1");
	//uint id = static_cast<CShape*>(cube0)->getMaterial()->getTexture(0)->getTextureIndex();
	//static_cast<CShape*>(cube0)->getMaterial()->getShader()->setUniformInt("texture0",id);
	//cube0->setPivot(Vector3(0,0,0));
	//static_cast<CShape*>(cube0)->getMaterial()->setSpecularColor(Vector4(1.0f));
	//static_cast<CShape*>(cube0)->getMaterial()->setDiffuseColor(Vector4(1.0f,0.0f,0.0f,1.0f));
	//static_cast<CShape*>(cube0)->getMaterial()->setShininess(128);
	//static_cast<CShape*>(cube0)->getMaterial()->setTexture(0, "Data/wall.bmp");
	//static_cast<CShape*>(cube0)->getMaterial()->setShader("data/default.vsh","data/default.psh");
	////CTexture* tex = m_scene->addRenderTargetTexture(1024,768);
	////static_cast<CShape*>(cube0)->getMaterial()->setTexture(0,tex);
	//const std::string cubeFaces[6] = {	"data/cubemap/right.tga",
	//									"data/cubemap/left.tga",
	//									"data/cubemap/up.tga",
	//									"data/cubemap/down.tga",
	//									"data/cubemap/backward.tga",
	//									"data/cubemap/forward.tga" };

	//static_cast<CShape*>(cube0)->getMaterial()->setTexture(0,cubeFaces);
	/*CShader* shader0 = new CShader();
	shader0->setName("shader0");
	shader0->loadShader("data/simple.vsh","data/simple.psh");
	static_cast<CShape*>(cube0)->getMaterial()->setShader(shader0);
	static_cast<CShape*>(cube0)->getMaterial()->getShader()->setEnable(true);
	uint texId0 = static_cast<CShape*>(cube0)->getMaterial()->getTexture(0)->getTextureIndex();
	static_cast<CShape*>(cube0)->getMaterial()->getShader()->setUniformInt("texture0",texId0);*/
	

	/*CNode* cube1 = m_scene->addCube(0,Vector3(0,0,-3.0),1);
	cube1->setName("cube1");
	cube1->setScale(Vector3(1,1,1));
	static_cast<CShape*>(cube1)->getMaterial()->setDiffuseColor(Vector4(0.0,1.0,0.0,1));
	static_cast<CShape*>(cube1)->getMaterial()->setSpecularColor(Vector4(1));
	static_cast<CShape*>(cube1)->getMaterial()->setShininess(128);
	static_cast<CShape*>(cube1)->getMaterial()->setTexture(0, "Data/wall.bmp");*/
	//static_cast<CShape*>(cube1)->getMaterial()->setEnableLight(false);

	//CNode* cube2 = m_scene->addCube(0,Vector3(0,0,0),1);
	//cube2->setName("cube2");
	//cube2->setScale(Vector3(1,1,1));
	//static_cast<CShape*>(cube2)->getMaterial()->setDiffuseColor(Vector4(0.0,1.0,0.0,1));
	//static_cast<CShape*>(cube2)->getMaterial()->setSpecularColor(Vector4(1));
	//static_cast<CShape*>(cube2)->getMaterial()->setShininess(128);
	//static_cast<CShape*>(cube2)->getMaterial()->setTexture(0,m_scene->createTexture2D("Data/wall.bmp"));
	////	
	////	
	//CNode* torus0 = m_scene->addTorus(0,Vector3(-0.8f,0.2f,-9.0f));
	//torus0->setScale(Vector3(5.0f,5.0f,5.0f));
	//static_cast<CShape*>(torus0)->getMaterial()->setSpecularColor(Vector4(1.0f));
	//static_cast<CShape*>(torus0)->getMaterial()->setDiffuseColor(Vector4(1.0f,0.0f,0.0f,1.0f));
	//static_cast<CShape*>(torus0)->getMaterial()->setShininess(128);
	////static_cast<CShape*>(shpere0)->getMaterial()->setEnableLight(false);
	/*const std::string cubeFaces[6] = {	"data/cubemap/right.tga",
										"data/cubemap/left.tga",
										"data/cubemap/up.tga",
										"data/cubemap/down.tga",
										"data/cubemap/backward.tga",
										"data/cubemap/forward.tga" };*/
	//static_cast<CShape*>(torus0)->getMaterial()->setTexture(0,m_scene->createTextureCubeMap(szCubeFaces));
	//static_cast<CShape*>(torus0)->getMaterial()->getTexture(0)->setScale(Vector3(6.0f));
	////static_cast<CShape*>(torus0)->getMaterial()->getTexture(0)->setEnvParam(TP_RAPLACE);


	/*CNode* sphere0 = m_scene->addSphere(0,Vector3(-6,0,-1),2);
	sphere0->setName("sphere0");
	static_cast<CShape*>(sphere0)->getMaterial()->setDiffuseColor(Vector4(0.0,0.0,1.0,1));
	static_cast<CShape*>(sphere0)->getMaterial()->setSpecularColor(Vector4(1));
	static_cast<CShape*>(sphere0)->getMaterial()->setShininess(128);
	static_cast<CShape*>(sphere0)->getMaterial()->setTexture(0,m_scene->createTexture2D("Data/ground.jpg"));
	static_cast<CShape*>(sphere0)->getMaterial()->setShader(shader0);*/
	
	/*CNode* cylinder0 = m_scene->addCylinder(0,Vector3(0,0,-15));
	cylinder0->setName("cylinder0");
	cylinder0->setScale(Vector3(1.0f,1.0f,5.0f));
	cylinder0->setRotation(Vector3(90,0,0));
	static_cast<CShape*>(cylinder0)->getMaterial()->setDiffuseColor(Vector4(0.0,1.0,0.0,1));
	static_cast<CShape*>(cylinder0)->getMaterial()->setSpecularColor(Vector4(1.0f));
	static_cast<CShape*>(cylinder0)->getMaterial()->setShininess(128);
	CTexture* texture3 = new CTexture2D();
	texture3->loadImage("Data/wall.bmp");
	static_cast<CShape*>(cylinder0)->getMaterial()->setTexture(0,texture3);*/

	/*CNode* disk0 = m_scene->addDisk(0,Vector3(0,0,-4));
	disk0->setName("disk0");
	static_cast<CShape*>(disk0)->getMaterial()->setDiffuseColor(Vector4(0.0,0.0,1.0,1));
	static_cast<CShape*>(disk0)->getMaterial()->setSpecularColor(Vector4(1));
	static_cast<CShape*>(disk0)->getMaterial()->setShininess(128);
	CTexture* texture2 = new CTexture2D();
	texture2->loadImage("Data/wall.bmp");
	static_cast<CShape*>(disk0)->getMaterial()->setTexture(0,texture2);*/


	
	/*CNode* plane0 = m_scene->addPlane(0,Vector3(0,0,-4));
	plane0->setName("plane0");
	static_cast<CShape*>(plane0)->getMaterial()->setDiffuseColor(Vector4(1.0,0.0,0.0,1));
	static_cast<CShape*>(plane0)->getMaterial()->setSpecularColor(Vector4(1));
	static_cast<CShape*>(plane0)->getMaterial()->setShininess(128);*/
	/*CTexture* texture2 = new CTexture2D();
	texture2->loadImage("Data/wall.bmp");
	static_cast<CShape*>(plane0)->getMaterial()->setTexture(0,texture2);*/
	
	//Camera
	CNode* Camera0 = m_scene->addFPSCamera(0,Vector3(0,1,0),Vector3(0,0,-3));
	Camera0->setName("camera0");

	//CNode* Camera1 = m_scene->addCamera(0,Vector3(0,1,6),Vector3(0,0,-1));
	//Camera1->setName("camera1");
	

	//Light
	
	

	//Fog
	/*CObject* fog = m_scene->addFog(Vector4(0.5,0.50,0.50,1),0,10);
	static_cast<CFog*>(fog)->setEnabled(false);*/
		
	//CNode* model0 = m_scene->addModel("data/teapot.f3d", NULL, Vector3(0,0,-5));
	//model0->setName("cube0");
	/*static_cast<CModel*>(model0)->getMesh(0)->getMaterial()->setSpecularColor(Vector4(1));
	static_cast<CModel*>(model0)->getMesh(0)->getMaterial()->setDiffuseColor(Vector4(1,0,0,1));
	static_cast<CModel*>(model0)->getMesh(0)->getMaterial()->setShininess(128);*/
	
	/*CShader* shader0 = new CShader();
	shader0->setName("shader0");
	shader0->loadShader("data/simple.vsh","data/simple.psh");
	static_cast<CModel*>(model0)->getMesh(0)->getMaterial()->setShader(shader0);
	static_cast<CModel*>(model0)->getMesh(0)->getMaterial()->getShader()->setEnable(true);
	static_cast<CModel*>(model0)->getMesh(0)->getMaterial()->setTexture(0,m_scene->createTexture2D("Data/wall.bmp"));
	static_cast<CModel*>(model0)->getMesh(0)->getMaterial()->getShader()->setUniformInt("texture0",0);*/
	
	/*CTexture* texture6 = new CTexture2D();
	texture6->loadImage("Data/Sand.jpg");
	static_cast<CModel*>(model0)->getMesh(0)->getMaterial()->setTexture(0,texture6);
	static_cast<CModel*>(model0)->getMesh(0)->getMaterial()->getTexture(0)->setScale(Vector3(2.0f));*/

	/*static_cast<CModel*>(model0)->getMesh(1)->getMaterial()->setSpecularColor(Vector4(1));
	static_cast<CModel*>(model0)->getMesh(1)->getMaterial()->setDiffuseColor(Vector4(0,1,0,1));
	static_cast<CModel*>(model0)->getMesh(1)->getMaterial()->setShininess(128);
	CTexture* texture7 = new CTexture2D();
	texture6->loadImage("Data/sand.jpg");
	static_cast<CModel*>(model0)->getMesh(1)->getMaterial()->setTexture(0,texture6);*/
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