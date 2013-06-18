#include "CSphereShape.h"
#include "CMaterial.h"
#include "CRender.h"

namespace glliba
{
	//////////////////////////////////////////////////////////////////////////////////////////////

	CSphereShape::CSphereShape(CNode* _pParent)
		: CShape(_pParent)
		, m_polyCount(60)
	{
		m_eTypeShape = OST_SPHERE;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////
	
	CSphereShape::~CSphereShape()
	{
		m_vertices.clear();
		CRender::getInstance()->deleteBufferObjects( m_vertices );
	}

	//////////////////////////////////////////////////////////////////////////////////////////////

	void CSphereShape::render()
	{
		if ( !m_bIsVisible )
		{
			return;
		}

		m_pMaterial->bind();

		CRender::getInstance()->drawSimple( DM_TRIANGLE_STRIP, m_vertices, m_pMaterial->getTextureCount() );
	}

	//////////////////////////////////////////////////////////////////////////////////////////////

	void CSphereShape::update( double _dDeltaTime )
	{
		if ( !m_bIsVisible )
		{
			return;
		}

		if ( m_bNeedUpdate )
		{
			CNode::updateTransform(_dDeltaTime);
			m_bNeedUpdate = false;
		}

		CRender::getInstance()->updateTransform(m_worldMatrix, m_offset);
	}

	//////////////////////////////////////////////////////////////////////////////////////////////

	void CSphereShape::init()
	{
		m_pMaterial->init();

		const float TWOPI = 6.28318530717958f;

		float theta1 = 0.0;   
		float theta2 = 0.0;   
		float theta3 = 0.0;   

		float nx = 0.0f;   
		float ny = 0.0f;   
		float nz = 0.0f;   

		float vx = 0.0f;   
		float vy = 0.0f;   
		float vz = 0.0f;   

		float tu  = 0.0f;   
		float tv  = 0.0f;

		float scale = 0.5f;

		uint numSphereVertices = (m_polyCount / 2) * ( (m_polyCount + 1) * 2 );

		m_vertices.malloc( numSphereVertices );
		
		if( m_polyCount < 4 )
		{
			m_polyCount = 4;
		}

		int index = -1;   
		for( uint i = 0; i < m_polyCount/2; ++i )   
		{
			theta1 = i * TWOPI / m_polyCount - (float)M_PI_2;   
			theta2 = (i + 1) * TWOPI / m_polyCount - (float)M_PI_2;   

			for( uint j = 0; j <= m_polyCount; ++j )   
			{   
				theta3 = j * TWOPI / m_polyCount;   

				nx = cosf(theta2) * cosf(theta3);   
				ny = sinf(theta2);   
				nz = cosf(theta2) * sinf(theta3);   
				vx = scale * nx;   
				vy = scale * ny;   
				vz = scale * nz;   
				tu  = - (j / (float)m_polyCount);   
				tv  = 2 * (i + 1) / (float)m_polyCount;   
				++index;   

				m_vertices.TexCoord.at(0).vertices[ index ].setX( tu );
				m_vertices.TexCoord.at(0).vertices[ index ].setY( tv );

				m_vertices.Normal.vertices[ index ].setX( nx );
				m_vertices.Normal.vertices[ index ].setY( ny );
				m_vertices.Normal.vertices[ index ].setZ( nz );

				m_vertices.Vertex.vertices[ index ].setX( vx );
				m_vertices.Vertex.vertices[ index ].setY( vy );
				m_vertices.Vertex.vertices[ index ].setZ( vz );


				nx = cosf(theta1) * cosf(theta3);   
				ny = sinf(theta1);   
				nz = cosf(theta1) * sinf(theta3);   
				vx = scale * nx;   
				vy = scale * ny;   
				vz = scale * nz;   
				tu  = - (j / (float)m_polyCount);   
				tv  = 2 * i / (float)m_polyCount;   
				++index;   

				m_vertices.TexCoord.at(0).vertices[ index ].setX( tu );
				m_vertices.TexCoord.at(0).vertices[ index ].setY( tv );

				m_vertices.Normal.vertices[ index ].setX( nx );
				m_vertices.Normal.vertices[ index ].setY( ny );
				m_vertices.Normal.vertices[ index ].setZ( nz );

				m_vertices.Vertex.vertices[ index ].setX( vx );
				m_vertices.Vertex.vertices[ index ].setY( vy );
				m_vertices.Vertex.vertices[ index ].setZ( vz );
			}   
		}

		CRender::getInstance()->initBufferObjects( m_vertices );

#ifndef _DEBUG
		m_vertices.clear();
#endif
	}

	//////////////////////////////////////////////////////////////////////////////////////////////

} //glliba