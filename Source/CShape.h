#ifndef _CSHAPE_H_
#define _CSHAPE_H_

#include "CNode.h"

namespace glliba
{

	////////////////////////////////////////////////////////////////////////////////////////////////////////////

	enum OBJECT_SHAPE_TYPE
	{
		OST_UNKNOWN,
		OST_CUBE,
		OST_SPHERE,
		OST_CYLINDER,
		OST_TORUS,
		OST_PLANE,
		OST_DISK,

		OST_COUNT
	};

	////////////////////////////////////////////////////////////////////////////////////////////////////////////

	class CMaterial;

	class CShape : public CNode
	{
	protected:

		OBJECT_SHAPE_TYPE	m_eTypeShape;
		CMaterial*			m_pMaterial;

		SVertexData			m_vertices;

	public:

		CShape( CNode* _parent = nullptr );
		virtual				~CShape();

		CMaterial*			setMaterial( CMaterial* _material );
		CMaterial*			getMaterial() const;
	};

	////////////////////////////////////////////////////////////////////////////////////////////////////////////

} //glliba

#endif