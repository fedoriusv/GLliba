#include "CPlaneShape.h"
#include "CMaterial.h"
#include "CRender.h"

namespace glliba
{
	//////////////////////////////////////////////////////////////////////////////////////////////

	CPlaneShape::CPlaneShape( CNode* _parent )
		: CShape(_parent)
		, m_fExtent(2.0f)
	{
		m_eTypeShape = OST_PLANE;

		CPlaneShape::init();
	}

	//////////////////////////////////////////////////////////////////////////////////////////////

	CPlaneShape::~CPlaneShape()
	{
		m_vertices.clear();
		CRender::getInstance()->deleteBufferObjects( m_vertices );
	}

	//////////////////////////////////////////////////////////////////////////////////////////////

	void CPlaneShape::render()
	{
		if ( !m_bIsVisible )
		{
			return;
		}

		m_pMaterial->bind();

		glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
		//CRender::getInstance()->drawSimple(DM_TRIANGLE_STRIP,m_vertices,m_transform,m_offset,m_pMaterial->getTextureCount());
		
	}

	//////////////////////////////////////////////////////////////////////////////////////////////

	void CPlaneShape::update( double _dDeltaTime )
	{
		if ( m_bNeedUpdate )
		{
			CNode::updateTransform(_dDeltaTime);
			m_bNeedUpdate = false;
		}
	}

	//////////////////////////////////////////////////////////////////////////////////////////////

	void CPlaneShape::init()
	{

		float fStep = 1.0f;
		float y = 0.0f;

		float s = 0.0f;
		float t = 0.0f;
		float texStep = 1.0f / (m_fExtent * .075f);

		int numPlaneVertices = (int)(2 * (2 * m_fExtent + 1) * (2 * m_fExtent + 1));

		m_vertices.malloc(numPlaneVertices);


		int index = -1; 
		for(float fStrip = -m_fExtent; fStrip <= m_fExtent; fStrip += fStep)
		{
			t = 0.0f;
			for(float fRun = m_fExtent; fRun >= -m_fExtent; fRun -= fStep)
			{
				++index;
				m_vertices.TexCoord.at(0).vertices[index].setX(s);
				m_vertices.TexCoord.at(0).vertices[index].setY(t);

				m_vertices.Normal.vertices[index].setX(0.0f);
				m_vertices.Normal.vertices[index].setY(1.0f);
				m_vertices.Normal.vertices[index].setZ(0.0f);

				m_vertices.Vertex.vertices[index].setX(fStrip);
				m_vertices.Vertex.vertices[index].setY(y);
				m_vertices.Vertex.vertices[index].setZ(fRun);


				++index;
				m_vertices.TexCoord.at(0).vertices[index].setX(s + texStep);
				m_vertices.TexCoord.at(0).vertices[index].setY(t);

				m_vertices.Normal.vertices[index].setX(0.0f);
				m_vertices.Normal.vertices[index].setY(1.0f);
				m_vertices.Normal.vertices[index].setZ(0.0f);

				m_vertices.Vertex.vertices[index].setX(fStrip + fStep);
				m_vertices.Vertex.vertices[index].setY(y);
				m_vertices.Vertex.vertices[index].setZ(fRun);

				t += texStep;
			}
			s += texStep;
		}

		CRender::getInstance()->initBufferObjects( m_vertices );

#ifndef _DEBUG
		m_vertices.clear();
#endif

	}

	//////////////////////////////////////////////////////////////////////////////////////////////

} //gllib