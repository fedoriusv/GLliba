#ifndef _CFPSCAMERA_H_
#define _CFPSCAMERA_H_

#include "CCamera.h"

namespace glliba
{

	///////////////////////////////////////////////////////////////////////////////////////////////////////////

	class CReciever;

	class CFPSCamera : public CCamera
	{
	protected:

		Vector3		m_max;
		Vector3		m_min;

		bool		isPointOut( const Vector3& _point );

		void		rotate( float _angle, float _x, float _y,float _z );
		void		move( const Vector3& _direction );
		void		rotateByMouse();

	public:

		CFPSCamera( CNode* _parent = nullptr);
		virtual		~CFPSCamera();

		void		update( double _dDeltaTime ) override;
		void		render() override;

	};

	///////////////////////////////////////////////////////////////////////////////////////////////////////////

} //glliba

#endif
