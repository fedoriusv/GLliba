#include "CCylinderShape.h"
#include "CMaterial.h"
#include "CRender.h"

namespace glliba
{
	//////////////////////////////////////////////////////////////////////////////////////////////

	CCylinderShape::CCylinderShape(CNode* _pParent)
		: CShape(_pParent)
		, m_fRadius(0.5f)
		, m_fHeight(1.0f)

	{
		m_eTypeShape = OST_CYLINDER;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////

	CCylinderShape::~CCylinderShape()
	{
		m_vertices.clear();
		CRender::getInstance()->deleteBufferObjects( m_vertices );
	}

	//////////////////////////////////////////////////////////////////////////////////////////////

	void CCylinderShape::render()
	{
		if ( !m_bIsVisible )
		{
			return;
		}

		m_pMaterial->bind();
		CRender::getInstance()->drawSimple( DM_TRIANGLE_STRIP,m_vertices,m_pMaterial->getTextureCount() );
	}

	//////////////////////////////////////////////////////////////////////////////////////////////

	void CCylinderShape::update( double _dDeltaTime )
	{
		if ( !m_bIsVisible )
		{
			return;
		}

		if ( m_bNeedUpdate )
		{
			CNode::updateTransform( _dDeltaTime );
			m_bNeedUpdate = false;
		}

		CRender::getInstance()->updateTransform(m_worldMatrix, m_offset);
	}

	//////////////////////////////////////////////////////////////////////////////////////////////

	void CCylinderShape::init()
	{
		m_pMaterial->init();

		uint numMajor = 20;
		uint numMinor = 20;
		double height = m_fHeight;
		double radius = m_fRadius;

		double majorStep = height / numMajor;
		double minorStep = 2.0 * M_PI / numMinor;

		int numCylinderVertices = numMajor * ( numMinor + 1 ) * 2;

		m_vertices.malloc(numCylinderVertices);
		
		int index = -1;
		for ( uint i = 0; i < numMajor; ++i ) 
		{
			float z0 = 0.5f * (float)height - i * (float)majorStep;
			float z1 = z0 - (float)majorStep;

			for ( uint j = 0; j <= numMinor; ++j )
			{
				double a = j * minorStep;
				float x = (float)(radius * cos(a));
				float y = (float)(radius * sin(a));

				++index;
				m_vertices.TexCoord.at(0).vertices[index].setX(j / (float)numMinor);
				m_vertices.TexCoord.at(0).vertices[index].setY(i / (float)numMajor);

				m_vertices.Normal.vertices[index].setX(x / (float)radius);
				m_vertices.Normal.vertices[index].setY(y / (float)radius);
				m_vertices.Normal.vertices[index].setZ(0.0f);

				m_vertices.Vertex.vertices[index].setX(x);
				m_vertices.Vertex.vertices[index].setY(y);
				m_vertices.Vertex.vertices[index].setZ(z0);

				++index;
				m_vertices.TexCoord.at(0).vertices[index].setX(j / (float)numMinor);
				m_vertices.TexCoord.at(0).vertices[index].setY((i + 1) / (float)numMajor);

				m_vertices.Normal.vertices[index].setX(x / (float)radius);
				m_vertices.Normal.vertices[index].setY(y / (float)radius);
				m_vertices.Normal.vertices[index].setZ(0.0f);

				m_vertices.Vertex.vertices[index].setX(x);
				m_vertices.Vertex.vertices[index].setY(y);
				m_vertices.Vertex.vertices[index].setZ(z1);
			}

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

	void CCylinderShape::setRadius( const float _fRadius )
	{
		m_fRadius = _fRadius;
		CCylinderShape::init();
	}

	//////////////////////////////////////////////////////////////////////////////////////////////

	void CCylinderShape::setHeight( const float _fHeight )
	{
		m_fHeight = _fHeight;
		CCylinderShape::init();
	}

	//////////////////////////////////////////////////////////////////////////////////////////////

	float CCylinderShape::getRadius() const
	{
		return m_fRadius;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////

	float CCylinderShape::getHeight() const
	{
		return m_fHeight;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////

} //glliba