#include "CSphereShape.h"
#include "CMaterial.h"
#include "CRender.h"

namespace glliba
{
	//////////////////////////////////////////////////////////////////////////////////////////////

	CSphereShape::CSphereShape(CNode* _pParent)
		: CShape(_pParent)
		, m_iSlices(30)
		, m_iStacks(30)
		, m_fRadius(1.0f)
	{
		m_eTypeShape = OST_SPHERE;
		CSphereShape::init();
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

		RENDERER->updateTransform( m_worldMatrix, m_offset );
		RENDERER->drawSimple( DM_TRIANGLE_STRIP, m_vertices );
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
	}

	//////////////////////////////////////////////////////////////////////////////////////////////

	void CSphereShape::init()
	{
		float drho = (float)M_PI / (float) m_iStacks;
		float dtheta = 2.0f * (float)M_PI / (float) m_iSlices;
		float ds = 1.0f / (float) m_iSlices;
		float dt = 1.0f / (float) m_iStacks;
		float t = 1.0f;	
		float s = 0.0f;
    
		m_vertices.malloc( m_iSlices * m_iStacks * 4 );
		
		int index = -1;
		for ( uint i = 0; i < m_iStacks; ++i ) 
		{
			float rho = (float)i * drho;
			float srho = (float)(sin(rho));
			float crho = (float)(cos(rho));
			float srhodrho = (float)(sinf(rho + drho));
			float crhodrho = (float)(cosf(rho + drho));
		
			s = 0.0f;
			for ( uint j = 0; j < m_iSlices; j++) 
			{
				float theta = (j == m_iSlices) ? 0.0f : j * dtheta;
				float stheta = (float)(-sin(theta));
				float ctheta = (float)(cos(theta));
			
				float x = stheta * srho;
				float y = ctheta * srho;
				float z = crho;
        
				++index;
				m_vertices.TexCoord.at(0).vertices[ index ].setX( s );
				m_vertices.TexCoord.at(0).vertices[ index ].setY( t );
				m_vertices.Normal.vertices[ index ].setX( x );
				m_vertices.Normal.vertices[ index ].setY( y );
				m_vertices.Normal.vertices[ index ].setZ( z );
				m_vertices.Vertex.vertices[ index ].setX( x * m_fRadius );
				m_vertices.Vertex.vertices[ index ].setY( y * m_fRadius );
				m_vertices.Vertex.vertices[ index ].setZ( z * m_fRadius );

				x = stheta * srhodrho;
				y = ctheta * srhodrho;
				z = crhodrho;

 				++index;
				m_vertices.TexCoord.at(0).vertices[ index ].setX( s );
				m_vertices.TexCoord.at(0).vertices[ index ].setY( t - dt );
				m_vertices.Normal.vertices[ index ].setX( x );
				m_vertices.Normal.vertices[ index ].setY( y );
				m_vertices.Normal.vertices[ index ].setZ( z );
				m_vertices.Vertex.vertices[ index ].setX( x * m_fRadius );
				m_vertices.Vertex.vertices[ index ].setY( y * m_fRadius );
				m_vertices.Vertex.vertices[ index ].setZ( z * m_fRadius );
			
				theta = ((j+1) == m_iSlices) ? 0.0f : (j+1) * dtheta;
				stheta = (float)(-sin(theta));
				ctheta = (float)(cos(theta));
			
				x = stheta * srho;
				y = ctheta * srho;
				z = crho;
        
				s += ds;
				++index;
				m_vertices.TexCoord.at(0).vertices[ index ].setX( s );
				m_vertices.TexCoord.at(0).vertices[ index ].setY( t );
				m_vertices.Normal.vertices[ index ].setX( x );
				m_vertices.Normal.vertices[ index ].setY( y );
				m_vertices.Normal.vertices[ index ].setZ( z );
				m_vertices.Vertex.vertices[ index ].setX( x * m_fRadius );
				m_vertices.Vertex.vertices[ index ].setY( y * m_fRadius );
				m_vertices.Vertex.vertices[ index ].setZ( z * m_fRadius );

				x = stheta * srhodrho;
				y = ctheta * srhodrho;
				z = crhodrho;

 				++index;
				m_vertices.TexCoord.at(0).vertices[ index ].setX( s );
				m_vertices.TexCoord.at(0).vertices[ index ].setY( t - dt );
				m_vertices.Normal.vertices[ index ].setX( x );
				m_vertices.Normal.vertices[ index ].setY( y );
				m_vertices.Normal.vertices[ index ].setZ( z );
				m_vertices.Vertex.vertices[ index ].setX( x * m_fRadius );
				m_vertices.Vertex.vertices[ index ].setY( y * m_fRadius );
				m_vertices.Vertex.vertices[ index ].setZ( z * m_fRadius );
			}
			t -= dt;
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

	void CSphereShape::setSlices( const uint _iValue )
	{
		m_iSlices = _iValue;
		CSphereShape::init();
	}

	//////////////////////////////////////////////////////////////////////////////////////////////

	void CSphereShape::setStacks( const uint _iValue )
	{
		m_iStacks = _iValue;
		CSphereShape::init();
	}

	//////////////////////////////////////////////////////////////////////////////////////////////

	void CSphereShape::setRadius( const float _iRadius )
	{
		m_fRadius = _iRadius;
		CSphereShape::init();
	}

	//////////////////////////////////////////////////////////////////////////////////////////////

	uint CSphereShape::getSlices() const
	{
		return m_iSlices;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////

	uint CSphereShape::getStacks() const
	{
		return m_iStacks;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////

	float CSphereShape::getRadius() const
	{
		return m_fRadius;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////
}