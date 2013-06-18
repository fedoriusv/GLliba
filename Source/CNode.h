#ifndef _CNODE_H_
#define _CNODE_H_

#include "CObject.h"
#include "Vertex.h"
#include "Param.h"

namespace glliba
{
	/////////////////////////////////////////////////////////////////////////////////////////////////////

	enum TYPE_NODE
	{
		TN_UNKNOWN = -1,
		TN_SHAPE,
		TN_MODEL,
		TN_CAMERA,
		TN_LIGHT,
		TN_FOG,
		TN_SKYBOX,

		TN_COUNT
	};

	/////////////////////////////////////////////////////////////////////////////////////////////////////

	extern const std::string type_node[TN_COUNT];

	static TYPE_NODE FromString(const char* _in)
	{
		for (int i = 0; i < TN_COUNT; ++i)
		{
			if (strcmp(_in, type_node[i].c_str()) == 0)
			{
				return(static_cast<TYPE_NODE>(i));
			}
		}
		return(TN_UNKNOWN);
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////////

	class CSceneManager;

	class CNode : public CObject
	{
	protected:

		friend						CSceneManager;

		uint						m_iIndexID;

		TYPE_NODE					m_eTypeNode;

		Vector3						m_position;
		Vector3						m_rotation;
		Vector3						m_scale;
		Vector3						m_pivot;
		Vector3						m_offset;

		Matrix4						m_transform;
		Matrix4						m_worldMatrix;//? to scene

		bool						m_bNeedUpdate;

		bool						m_bIsVisible;
		float						m_fPriority;

		CNode*						m_pParent;
		std::vector<CNode*>			m_children;

	public:

		CNode( CNode* _pParent = NULL );
		~CNode();

		void						setPosition	( const Vector3& _position );
		void						setRotation	( const Vector3& _rotation );
		void						setScale	( const Vector3& _scale );
		void						setPivot	( const Vector3& _pivot );
		void						setTransform( const Matrix4& _transform );

		Vector3						getPosition() const;
		Vector3						getRotation() const;
		Vector3						getScale() const;
		Vector3						getPivot() const;
		Matrix4						getTransform() const;

		TYPE_NODE					getNodeType() const;
		float						getPriority() const;

		void						setVisible( bool _bVisible );
		bool						isVisible() const;


		Matrix4						getMorldMatrix() const;//? to scene
		void						updateTransform( double _dDeltaTime );

		CNode*						getParent() const;
		virtual void				setParent( CNode* _pParent );
		void						addChild( CNode* _pObject );
		std::vector<CNode*>*		getChildrenList();

		virtual void				render() = 0;
		virtual void				update( double _dDeltaTime ) = 0;

		virtual void				init() = 0;
	};

	/////////////////////////////////////////////////////////////////////////////////////////////////////

} //glliba

#endif