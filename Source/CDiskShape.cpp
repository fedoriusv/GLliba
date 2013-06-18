#include "CDiskShape.h"
#include "CMaterial.h"
#include "CRender.h"

namespace glliba
{
	//////////////////////////////////////////////////////////////////////////////////////////////

	CDiskShape::CDiskShape( CNode* _parent )
		: CShape(_parent)
		, m_iSegmentsCount(20)
		, m_fRadius(0.5f)
	{
		m_eTypeShape = OST_DISK;

		CDiskShape::init();
	}

	//////////////////////////////////////////////////////////////////////////////////////////////

	CDiskShape::~CDiskShape()
	{
		m_vertices.clear();
		CRender::getInstance()->deleteBufferObjects( m_vertices );
	}

	//////////////////////////////////////////////////////////////////////////////////////////////

	void CDiskShape::render()
	{
		if ( !m_bIsVisible )
		{
			return;
		}

		m_pMaterial->bind();
		CRender::getInstance()->drawSimple( DM_TRIANGLE_FAN, m_vertices, m_pMaterial->getTextureCount() );
	}

	//////////////////////////////////////////////////////////////////////////////////////////////

	void CDiskShape::update( double _dDeltaTime )
	{
		if ( m_bNeedUpdate )
		{
			CNode::updateTransform(_dDeltaTime);
			m_bNeedUpdate = false;
		}
	}

	//////////////////////////////////////////////////////////////////////////////////////////////

	void CDiskShape::init()
	{
		float ox = 0;
		float oy = 0;
		float r = m_fRadius;
		int segments = m_iSegmentsCount;

		double n = 360.0 / (double)segments;
		double a = n * M_PI / 180.0;

		m_vertices.malloc( segments + 2 );

		m_vertices.Vertex.vertices[0].setX(ox);
		m_vertices.Vertex.vertices[0].setY(oy);
		m_vertices.Vertex.vertices[0].setZ(0.0f);

		m_vertices.Normal.vertices[0].setX(0.0f);
		m_vertices.Normal.vertices[0].setY(0.0f);
		m_vertices.Normal.vertices[0].setZ(1.0f);

		m_vertices.TexCoord.at(0).vertices[0].setX(0.5f);
		m_vertices.TexCoord.at(0).vertices[0].setY(0.5f);


		for (int i = 0; i <= segments; i++)
		{
			float u = (float(cos((i-1)*a)) + 1.0f) / 2.0f;
			float v = (float(sin((i-1)*a)) + 1.0f) / 2.0f;
			float cx = float(cos((i-1)*a)) * r;
			float cy = float(sin((i-1)*a))* r;

			m_vertices.Vertex.vertices[i + 1].setX(cx + ox);
			m_vertices.Vertex.vertices[i + 1].setY(cy + oy);
			m_vertices.Vertex.vertices[i + 1].setZ(0.0f);

			m_vertices.Normal.vertices[i + 1].setX(0.0f);
			m_vertices.Normal.vertices[i + 1].setY(0.0f);
			m_vertices.Normal.vertices[i + 1].setZ(1.0f);

			m_vertices.TexCoord.at(0).vertices[i + 1].setX(u);
			m_vertices.TexCoord.at(0).vertices[i + 1].setY(v);

		}

		if (m_vertices.Vertex.iVerticesID == 0)
		{
			CRender::getInstance()->initBufferObjects( m_vertices );
		}
		else
		{
			CRender::getInstance()->updateBufferObject( m_vertices );
		}

#ifndef _DEBUG
		m_vertices.clear();
#endif
	}

	//////////////////////////////////////////////////////////////////////////////////////////////

	void CDiskShape::setRadius( const float& _radius )
	{
		m_fRadius = _radius;
		CDiskShape::init();
	}

	//////////////////////////////////////////////////////////////////////////////////////////////

	float CDiskShape::getRadius() const
	{
		return m_fRadius;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////

	void CDiskShape::setSegmentsCount( const uint& _count )
	{
		m_iSegmentsCount = _count;
		CDiskShape::init();
	}

	//////////////////////////////////////////////////////////////////////////////////////////////

} //glliba