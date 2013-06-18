#ifndef _CHEIGHTMAP_H_
#define _CHEIGHTMAP_H_

#include "CNode.h"

namespace glliba
{
	class CHeightMap : public CNode
	{
	protected:

		uint			m_iIndexID;
		SVertexData		m_vertices;

		void			init();

	public:

		CHeightMap( CNode* _parent = NULL );
		virtual			~CHeightMap();

		void			render();
		void			update();
	};
}

#endif