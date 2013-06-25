#include "CModel.h"

#include "CRender.h"

namespace glliba
{
	////////////////////////////////////////////////////////////////////////////////////////////////////////////

	CModel::CModel( CNode* _pParent)
		: CNode(_pParent)
	{
		m_eTypeNode = TN_MODEL;
		LOG_CONSOLE( "Initialize node " << type_node[m_eTypeNode].c_str());
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////

	CModel::~CModel()
	{
		for ( std::vector<CMesh*>::iterator iter = m_pMesh.begin(); iter < m_pMesh.end(); ++iter )
		{
			CMesh* mesh = (*iter);
			m_pMesh.pop_back();

			delete mesh;
			mesh = nullptr;
		}

		m_pMesh.clear();
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////

	void CModel::addMesh( CMesh* _pMesh )
	{
		m_pMesh.push_back( _pMesh );
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////

	CMesh* CModel::getMesh( const uint _iID ) const
	{
		ASSERT( m_pMesh.size() > _iID || "Not Mesh initialize" );
		return m_pMesh.at(_iID);
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////

	int CModel::getMeshCount() const
	{
		return m_pMesh.size();
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////

	void CModel::update( double _dDeltaTime )
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

		for ( std::vector<CMesh*>::iterator iter = m_pMesh.begin(); iter < m_pMesh.end(); ++iter )
		{
			(*iter)->update( _dDeltaTime );
		}
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////

	void CModel::render()
	{
		if ( !m_bIsVisible )
		{
			return;
		}

		for ( std::vector<CMesh*>::iterator iter = m_pMesh.begin(); iter < m_pMesh.end(); ++iter )
		{
			//TODO: temporary need solution;
			(*iter)->getMaterial()->bind();
			RENDERER->updateTransform( m_worldMatrix, m_offset );
			(*iter)->render();
		}
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////

	bool CModel::compareByName( std::string _name )
	{
		if( m_modelNameFile.compare(_name) == 0 )
		{
			return true;
		}

		return false;
	}
}