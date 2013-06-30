#include "CNode.h"

namespace glliba
{
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	const std::string type_node[TN_COUNT] =
	{
		"shape",
		"model",
		"camera",
		"light",
		"fog",
		"skybox",
		"font",
	};

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	CNode::CNode( CNode* _parent )
		: CObject()
		, m_position(0.0f,0.0f,0.0f)
		, m_rotation(0.0f,0.0f,0.0f)
		, m_scale(1.0f,1.0f,1.0f)
		, m_pivot(0.0f)
		, m_offset(0.0f)

		, m_eTypeNode(TN_UNKNOWN)
		, m_bIsVisible(true)
		, m_fPriority(0.0f)
		, m_transform(Matrix4::identity())
		, m_worldMatrix(Matrix4::identity())
		, m_bNeedUpdate(false)

		, m_pParent(_parent)
		, m_children(NULL)

		, m_iIndexID(0)

	{
		m_eTypeObject = OT_NODE;

		m_eDrawParam._iCullFaceMode  = FM_BACK;
		m_eDrawParam._iDepthFuncMode = DF_LESS;

		if (m_pParent != nullptr)
		{
			CNode::setParent(_parent);
		}
	}

	
	CNode::~CNode()
	{
		m_pParent = NULL;
	}

	
	void CNode::updateTransform( double _deltaTime )
	{
		m_transform = Matrix4::translation(m_position) * Matrix4::rotationDegreesZYX(m_rotation) * Matrix4::scale(m_scale);
		m_worldMatrix = Vectormath::transpose(m_transform * getMorldMatrix());

		//TODO: Not complete!
		m_offset = m_pivot;

		for ( std::vector<CNode*>::iterator iter = m_children.begin(); iter < m_children.end(); ++iter )
		{
			CNode* item = static_cast<CNode*>((*iter));
			//item->m_pivot = (m_worldMatrix.getCol3() - (item->m_transform * m_worldMatrix).getCol3());
			item->updateTransform( _deltaTime );
			item->m_bNeedUpdate = true;
		}
	}

	
	void CNode::setPosition( const Vector3& _pos )
	{
		m_position = _pos;
		CNode::updateTransform(0);
		m_bNeedUpdate = true;
	}

	
	void CNode::setRotation( const Vector3& _rot )
	{
		m_rotation = _rot;
		CNode::updateTransform(0);
		m_bNeedUpdate = true;
	}

	
	void CNode::setScale( const Vector3& _scl )
	{
		m_scale = _scl;
		CNode::updateTransform(0);
		m_bNeedUpdate = true;
	}

	
	void CNode::setPivot( const Vector3& _pivot )
	{
		m_pivot = _pivot;
		CNode::updateTransform(0);
		m_bNeedUpdate = true;
	}

	
	Vector3 CNode::getPivot() const
	{
		ASSERT(this && "Invalid Object");
		return m_pivot;
	}

	
	Vector3 CNode::getPosition() const
	{
		ASSERT(this && "Invalid Object");
		return m_position;
	}

	
	Vector3 CNode::getRotation() const
	{
		ASSERT(this && "Invalid Object");
		return m_rotation;
	}

	
	Vector3 CNode::getScale() const
	{
		ASSERT(this && "Invalid Object");
		return m_scale;
	}

	
	TYPE_NODE CNode::getNodeType() const
	{
		return m_eTypeNode;
	}

	
	void CNode::setVisible( bool _visible )
	{
		m_bIsVisible = _visible;
	}

	
	bool CNode::isVisible() const
	{
		return m_bIsVisible;
	}

	
	float CNode::getPriority() const
	{
		return m_fPriority;
	}

	
	Matrix4 CNode::getMorldMatrix() const
	{
		if (m_pParent != NULL)
		{
			return static_cast<CNode*>(m_pParent)->m_worldMatrix;
		}

		return Matrix4::identity();
	}

	
	void CNode::setTransform( const Matrix4& _transform )
	{
		m_transform = _transform;
	}

	
	Matrix4 CNode::getTransform() const
	{
		ASSERT(this && "Invalid Object");
		return m_transform;
	}

	
	CNode* CNode::getParent() const
	{
		return m_pParent;
	}

	
	void CNode::setParent( CNode* _parent )
	{
		if (_parent != NULL )
		{
			m_pParent = _parent;
			m_pParent->addChild(this);
		}
	}

	
	void CNode::addChild( CNode* _object )
	{
		_object->m_pParent = this;
		m_children.push_back(_object);
	}

	
	std::vector<CNode*>* CNode::getChildrenList()
	{
		return &m_children;
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////////

}

