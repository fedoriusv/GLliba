#include "CMesh.h"

#include "CRender.h"

namespace glliba
{
	////////////////////////////////////////////////////////////////////////////////////////////////////////////

	CMesh::CMesh()
		: CObject()
	{
		m_eTypeObject = OT_MESH;
		m_pMaterial = new CMaterial();
	}
	
	////////////////////////////////////////////////////////////////////////////////////////////////////////////

	CMesh::~CMesh()
	{
		delete m_pMaterial;
		m_pMaterial = nullptr;

		m_vertices.clear();
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////

	CMaterial* CMesh::getMaterial() const
	{
		return m_pMaterial;
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////

	void CMesh::setMaterial( CMaterial* _pMaterial )
	{
		if (m_pMaterial)
		{
			destroyMaterial();
		}

		m_pMaterial = (CMaterial*)_pMaterial->getRef();
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////

	void CMesh::destroyMaterial()
	{
		if (m_pMaterial->releaseRef() == 0)
		{
			delete m_pMaterial;
			m_pMaterial = nullptr;
		}
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////

	void CMesh::update( double _dDeltaTime )
	{
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////

	void CMesh::render()
	{
		//m_pMaterial->bind();

		RENDERER->drawSimple( DM_TRIANGLES, m_vertices );
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////

	void CMesh::init()
	{
		RENDERER->initBufferObjects( m_vertices );
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////

} //glliba