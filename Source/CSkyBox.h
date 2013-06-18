#ifndef _CSKYBOX_H_
#define _CSKYBOX_H_

#include "CNode.h"
#include "CCubeShape.h"

namespace glliba
{
	/////////////////////////////////////////////////////////////////////////////////////////////////////////

	class CTexture;

	class CSkyBox : public CNode
	{
	protected:
		CTexture*			m_pSkyBoxTexture[6U];
		bool				m_bIsLoad;

		SVertexData			m_vertices;
		void				init();
	public:
		CSkyBox();
		virtual ~CSkyBox();

		bool				isValid();
		void				loadSkyBox( const std::string* _fileName[6] );

		void				render();
		void				update();

		void				destroySkyBox();


	};

	/////////////////////////////////////////////////////////////////////////////////////////////////////////
}

#endif