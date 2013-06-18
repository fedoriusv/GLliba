#include "CShape.h"
#include "CMaterial.h"

namespace glliba
{
	////////////////////////////////////////////////////////////////////////////////////////////////////////////

	CShape::CShape( CNode* _pParent)
		: CNode(_pParent)
		, m_eTypeShape(OST_UNKNOWN)
	{
		m_eTypeNode = TN_SHAPE;
		LOG_CONSOLE( "Initialize node " << type_node[m_eTypeNode].c_str());

		m_pMaterial = new CMaterial();
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////

	CShape::~CShape()
	{
		delete m_pMaterial;
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////

	CMaterial* CShape::setMaterial( CMaterial* _pMaterial )
	{
		CMaterial* oldMaterial = m_pMaterial;
		m_pMaterial = _pMaterial;

		return oldMaterial;
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////

	CMaterial* CShape::getMaterial() const
	{
		return m_pMaterial;
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////

} //glliba