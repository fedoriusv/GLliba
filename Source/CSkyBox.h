#ifndef _CSKYBOX_H_
#define _CSKYBOX_H_

#include "CNode.h"
#include "CCubeShape.h"

namespace glliba
{
	/////////////////////////////////////////////////////////////////////////////////////////////////////////

	class CTexture;
	class CShader;

	class CSkyBox : public CNode
	{
	protected:
		CTexture*		m_pSkyBoxTexture[6U];
		CShader*		m_pShader;

		bool			m_bIsLoad;

		SVertexData		m_vertices;
		void			init();
	public:
		CSkyBox();
		virtual			~CSkyBox();

		bool			isValid();
		void			loadSkyBox( const std::string* _fileNames );

		void			render();
		void			update( double _deltaTime );

		void			setShader( CShader* _shader );

	};

	/////////////////////////////////////////////////////////////////////////////////////////////////////////
}

#endif