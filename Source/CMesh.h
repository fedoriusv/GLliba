#ifndef _CMESH_H_
#define _CMESH_H_

#include "CObject.h"
#include "CMaterial.h"
#include "Vertex.h"

namespace glliba
{
	////////////////////////////////////////////////////////////////////////////////////////////////////////////

	class CModel3DS;
	class CModelF3D;

	class CMesh : public CObject
	{
	protected:

		friend				CModel3DS;
		friend				CModelF3D;

		SVertexData			m_vertices;

		CMaterial*			m_pMaterial;
		
		void				init();

	public:

		CMesh();
		virtual				~CMesh();

		void				setMaterial( CMaterial* _material );
		CMaterial*			getMaterial() const;

		void				destroyMaterial();

		void				update( double _dDeltaTime );
		void				render();
	};

	////////////////////////////////////////////////////////////////////////////////////////////////////////////

} //glliba

#endif