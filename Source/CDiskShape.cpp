#include "CDiskShape.h"
#include "CMaterial.h"
#include "CRender.h"

namespace glliba
{
	//////////////////////////////////////////////////////////////////////////////////////////////

	CDiskShape::CDiskShape( CNode* _parent )
		: CShape(_parent)
		, m_nSlices(15U)
		, m_nStacks(3U)
		, m_fInnerRadius(1.0f)
		, m_fOuterRadius(2.0f)
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

		RENDERER->updateTransform(m_worldMatrix, m_offset);
		RENDERER->drawSimple( DM_TRIANGLE_STRIP, m_vertices );
	}

	//////////////////////////////////////////////////////////////////////////////////////////////

	void CDiskShape::update( double _deltaTime )
	{
		if ( !m_bIsVisible )
		{
			return;
		}

		if ( m_bNeedUpdate )
		{
			CNode::updateTransform(_deltaTime);
			m_bNeedUpdate = false;
		}
	}

	//////////////////////////////////////////////////////////////////////////////////////////////

	void CDiskShape::init()
	{
		float fStepSizeRadial = m_fOuterRadius - m_fInnerRadius;
		if(fStepSizeRadial < 0.0f)
		{
			fStepSizeRadial *= -1.0f;
		}

		fStepSizeRadial /= float(m_nStacks);
	
		float fStepSizeSlice = ((float)M_PI * 2.0f) / float(m_nSlices);
	
		m_vertices.malloc( m_nSlices * m_nStacks * 4 );
			
		float fRadialScale = 1.0f / m_fOuterRadius;
	
		int index = -1;
		for( uint i = 0; i < m_nStacks; ++i )			// Stacks
		{
			float theyta;
			float theytaNext;
			for( uint j = 0; j < m_nSlices; ++j )     // Slices
			{
				float inner = m_fInnerRadius + (float(i)) * fStepSizeRadial;
				float outer = m_fInnerRadius + (float(i+1)) * fStepSizeRadial;
			
				theyta = fStepSizeSlice * float(j);
				if(j == (m_nSlices - 1))
					theytaNext = 0.0f;
				else
					theytaNext = fStepSizeSlice * (float(j+1));
				
				// Inner First
				++index;
				m_vertices.Vertex.vertices[index].setX(cos(theyta) * inner);
				m_vertices.Vertex.vertices[index].setY(sin(theyta) * inner);
				m_vertices.Vertex.vertices[index].setZ(0.0f);
				m_vertices.Normal.vertices[index].setX(0.0f);
				m_vertices.Normal.vertices[index].setY(0.0f);
				m_vertices.Normal.vertices[index].setZ(1.0f);
				m_vertices.TexCoord.at(0).vertices[index].setX( (((cos(theyta) * inner) * fRadialScale) + 1.0f) * 0.5f );
				m_vertices.TexCoord.at(0).vertices[index].setY( (((sin(theyta) * inner) * fRadialScale) + 1.0f) * 0.5f );

			
				// Outer First
				++index;
				m_vertices.Vertex.vertices[index].setX(cos(theyta) * outer);
				m_vertices.Vertex.vertices[index].setY(sin(theyta) * outer);
				m_vertices.Vertex.vertices[index].setZ(0.0f);
				m_vertices.Normal.vertices[index].setX(0.0f);
				m_vertices.Normal.vertices[index].setY(0.0f);
				m_vertices.Normal.vertices[index].setZ(1.0f);
				m_vertices.TexCoord.at(0).vertices[index].setX( (((cos(theyta) * outer) * fRadialScale) + 1.0f) * 0.5f );
				m_vertices.TexCoord.at(0).vertices[index].setY( (((sin(theyta) * outer) * fRadialScale) + 1.0f) * 0.5f );
			
				// Inner Second
				++index;
				m_vertices.Vertex.vertices[index].setX(cos(theytaNext) * inner);
				m_vertices.Vertex.vertices[index].setY(sin(theytaNext) * inner);
				m_vertices.Vertex.vertices[index].setZ(0.0f);
				m_vertices.Normal.vertices[index].setX(0.0f);
				m_vertices.Normal.vertices[index].setY(0.0f);
				m_vertices.Normal.vertices[index].setZ(1.0f);
				m_vertices.TexCoord.at(0).vertices[index].setX( (((cos(theytaNext) * inner) * fRadialScale) + 1.0f) * 0.5f );
				m_vertices.TexCoord.at(0).vertices[index].setY( (((sin(theytaNext) * inner) * fRadialScale) + 1.0f) * 0.5f );
			
			
				// Outer Second
				++index;
				m_vertices.Vertex.vertices[index].setX(cos(theytaNext) * outer);
				m_vertices.Vertex.vertices[index].setY(sin(theytaNext) * outer);
				m_vertices.Vertex.vertices[index].setZ(0.0f);
				m_vertices.Normal.vertices[index].setX(0.0f);
				m_vertices.Normal.vertices[index].setY(0.0f);
				m_vertices.Normal.vertices[index].setZ(1.0f);
				m_vertices.TexCoord.at(0).vertices[index].setX( (((cos(theytaNext) * outer) * fRadialScale) + 1.0f) * 0.5f );
				m_vertices.TexCoord.at(0).vertices[index].setY( (((sin(theytaNext) * outer) * fRadialScale) + 1.0f) * 0.5f );
			
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

	void CDiskShape::setSlices( const uint _value )
	{
		m_nSlices = _value;
		CDiskShape::init();
	}

	//////////////////////////////////////////////////////////////////////////////////////////////

	void CDiskShape::setStacks( const uint _value )
	{
		m_nStacks = _value;
		CDiskShape::init();
	}

	//////////////////////////////////////////////////////////////////////////////////////////////

	void CDiskShape::setInnerRadius( const float _radius )
	{
		m_fInnerRadius = _radius;
		CDiskShape::init();
	}

	//////////////////////////////////////////////////////////////////////////////////////////////

	void CDiskShape::setOuterRadius( const float _radius )
	{
		m_fOuterRadius = _radius;
		CDiskShape::init();
	}

	//////////////////////////////////////////////////////////////////////////////////////////////

	uint CDiskShape::getSlices() const
	{
		return m_nSlices;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////

	uint CDiskShape::getStacks() const
	{
		return m_nStacks;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////

	float CDiskShape::getInnerRadius() const
	{
		return m_fInnerRadius;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////

	float CDiskShape::getOuterRadius() const
	{
		return m_fOuterRadius;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////

}