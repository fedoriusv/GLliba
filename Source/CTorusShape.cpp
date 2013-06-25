#include "CTorusShape.h"
#include "CMaterial.h"
#include "CRender.h"

namespace glliba
{
	//////////////////////////////////////////////////////////////////////////////////////////////

	CTorusShape::CTorusShape(CNode* _parent)
		: CShape(_parent)
		, m_fMajorRadius(1.0f)
		, m_fMinorRadius(0.5f)
	{
		m_eTypeShape = OST_TORUS;
		CTorusShape::init();
	}

	//////////////////////////////////////////////////////////////////////////////////////////////

	CTorusShape::~CTorusShape()
	{
		m_vertices.clear();
		RENDERER->deleteBufferObjects( m_vertices );
	}

	//////////////////////////////////////////////////////////////////////////////////////////////

	void CTorusShape::render()
	{
		if ( !m_bIsVisible )
		{
			return;
		}

		m_pMaterial->bind();

		RENDERER->updateTransform( m_worldMatrix, m_offset );
		RENDERER->drawSimple( DM_TRIANGLE_STRIP, m_vertices );
	}

	//////////////////////////////////////////////////////////////////////////////////////////////

	void CTorusShape::update( double _deltaTime )
	{
		if ( !m_bIsVisible )
		{
			return;
		}

		if ( m_bNeedUpdate )
		{
			CNode::updateTransform( _deltaTime );
			m_bNeedUpdate = false;
		}
	}

	//////////////////////////////////////////////////////////////////////////////////////////////

	void CTorusShape::setMinorRadius( const float _radius )
	{
		m_fMinorRadius = _radius;
		CTorusShape::init();
	}

	//////////////////////////////////////////////////////////////////////////////////////////////

	void CTorusShape::setMajorRadius( const float _radius )
	{
		m_fMajorRadius = _radius;
		CTorusShape::init();
	}

	//////////////////////////////////////////////////////////////////////////////////////////////

	float CTorusShape::getMinorRadius() const
	{
		return m_fMinorRadius;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////

	float CTorusShape::getMajorRadius() const
	{
		return m_fMajorRadius;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////

	void CTorusShape::init()
	{
		uint numMajor = 50;
		uint numMinor = 20;

		uint numTorusVertices = numMajor * (numMinor + 1) * 2;

		double majorStep = 2.0f * M_PI / numMajor;
		double minorStep = 2.0f * M_PI / numMinor;

		m_vertices.malloc( numTorusVertices );

		int index = -1;
		for (uint i = 0; i < numMajor; ++i ) 
		{
			double a0 = i * majorStep;
			double a1 = a0 + majorStep;
			float x0 = (float) cos(a0);
			float y0 = (float) sin(a0);
			float x1 = (float) cos(a1);
			float y1 = (float) sin(a1);

			for (uint j = 0; j <= numMinor; ++j )
			{
				double b = j * minorStep;
				float c = (float) cos(b);
				float r = m_fMinorRadius * c + m_fMajorRadius;
				float z = m_fMinorRadius * (float) sin(b);

				Vector3 vNormal(x0*c,y0*c,z/m_fMinorRadius);
				normalize(vNormal);
				++index;
				m_vertices.TexCoord.at(0).vertices[ index ].setX( (float)(i) / (float)(numMajor) );
				m_vertices.TexCoord.at(0).vertices[ index ].setY( (float)(j) / (float)(numMinor) );

				m_vertices.Normal.vertices[ index ].setX( vNormal.getX() ); 
				m_vertices.Normal.vertices[ index ].setY( vNormal.getY() );
				m_vertices.Normal.vertices[ index ].setZ( vNormal.getZ() );

				m_vertices.Vertex.vertices[ index ].setX( x0*r ); 
				m_vertices.Vertex.vertices[ index ].setY( y0*r );
				m_vertices.Vertex.vertices[ index ].setZ( z );
		
				vNormal = Vector3(x1*c,y1*c,z/m_fMinorRadius);
				normalize(vNormal);
				++index;
				m_vertices.TexCoord.at(0).vertices[ index ].setX( (float)(i+1) / (float)(numMajor) );
				m_vertices.TexCoord.at(0).vertices[ index ].setY( (float)(j) / (float)(numMinor) );

				m_vertices.Normal.vertices[ index ].setX( vNormal.getX() );
				m_vertices.Normal.vertices[ index ].setY( vNormal.getY() );
				m_vertices.Normal.vertices[ index ].setZ( vNormal.getZ() );

				m_vertices.Vertex.vertices[ index ].setX( x1*r ); 
				m_vertices.Vertex.vertices[ index ].setY( y1*r );
				m_vertices.Vertex.vertices[ index ].setZ( z );
			}
		}

		if (m_vertices.Vertex.iVerticesID == 0)
		{
			RENDERER->initBufferObjects( m_vertices );
		}
		else
		{
			RENDERER->updateBufferObject( m_vertices );
		}

#ifndef _DEBUG
		m_vertices.clear();
#endif
	}

	//////////////////////////////////////////////////////////////////////////////////////////////
}