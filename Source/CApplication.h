#ifndef _CAPPLICATION_H_
#define _CAPPLICATION_H_

#include "CRender.h"
#include "CSceneManager.h"
#include "CReciever.h"

#ifdef _OPENGL
#	include "CRenderGL.h"
#endif

using namespace glliba;

class CApplication : public CSingleton<CApplication> 
{
private:

	CReciever*				m_reciever;
	CSceneManager*			m_scene;
	CRender*				m_render;

public:

	CApplication();
	virtual					~CApplication();

	void					init();
	void					run();
	bool					isExecute();

	void					updateReciever( double _dDeltaTime );
	CReciever*				getReciever();
	
};

#endif
