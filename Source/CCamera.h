#ifndef _CCAMERA_H_
#define _CCAMERA_H_

#include "CNode.h"

namespace glliba
{

	////////////////////////////////////////////////////////////////////////////////////////////////////////

	class CScene;

	class CCamera : public CNode
	{
	protected:

		friend						CSceneManager;

		Vector3						m_up;
		Vector3						m_target;

		bool						m_bIsActive;

	public:

		CCamera( CNode* _pParent = NULL );
		virtual						~CCamera();

		void						init();

		void						setTarget( const Vector3& _target );
		Vector3						getTarget() const;

		void						setUpVector( const Vector3& _up );
		Vector3						getUpVector() const;

		void						render();
		void						update( double _dDeltaTime );

		bool						isActive() const;
	};

	////////////////////////////////////////////////////////////////////////////////////////////////////////

} //glliba

#endif