#include "CFPSCamera.h"

#include "CRender.h"

namespace glliba
{
	///////////////////////////////////////////////////////////////////////////////////////////////////////////

	CFPSCamera::CFPSCamera( CNode* _parent )
		: CCamera(_parent)
		, m_min(-100000.0f,-100000.0f,-100000.0f)
		, m_max(100000.0f,100000.0f,100000.0f)
	{
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////

	CFPSCamera::~CFPSCamera()
	{
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////

	void CFPSCamera::move( Vector3 _direction )
	{
		Vector3 oPos		= m_position;
		Vector3 oView		= m_target;
		Vector3 move_dir	= m_target - m_position;
		Vector3 strafe		= cross( move_dir, m_up);

		normalize(move_dir);
		normalize(strafe);

		m_position[0]	+= (move_dir[0] * -_direction[2]);
		m_position[1]	+= (move_dir[1] * -_direction[2]);
		m_position[2]	+= (move_dir[2] * -_direction[2]);

		m_target[0]		+= (move_dir[0] * -_direction[2]);
		m_target[1]		+= (move_dir[1] * -_direction[2]);
		m_target[2]		+= (move_dir[2] * -_direction[2]);

		m_position[0]	+= (strafe[0]	* _direction[0]);
		m_position[1]	+= (strafe[1]	* _direction[0]);
		m_position[2]	+= (strafe[2]	* _direction[0]);

		m_target[0]		+= (strafe[0]	* _direction[0]);
		m_target[1]		+= (strafe[1]	* _direction[0]);
		m_target[2]		+= (strafe[2]	* _direction[0]);


		m_position[1]	+= _direction[1];
		m_target[1]		+= _direction[1];

	
		if(isPointOut(m_position))
		{
			m_position	= oPos;
			m_target	= oView;
		}
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////

	bool CFPSCamera::isPointOut( Vector3 _point )
	{
		if( (_point[0] <= m_min[0]) || (_point[1] <= m_min[1]) || (_point[2] <=m_min[2]) ||
			(_point[0] >= m_max[0]) || (_point[1] >= m_max[1]) || (_point[2] >=m_max[2]) )
		{
				return true;
		}

		return false;
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////

	void CFPSCamera::rotate( float _angle, float _x, float _y,float _z )
	{
		Vector3 new_view;
		Vector3 old_view;

		old_view = m_target - m_position;

		float cosTheta = (float)cos(_angle);
		float sinTheta = (float)sin(_angle);
 
		new_view[0] = (cosTheta + (1 - cosTheta) * _x * _x) * old_view.getX();
		new_view[0] = new_view.getX() + ((1 - cosTheta) * _x * _y - _z * sinTheta)	* old_view.getY();
		new_view[0] = new_view.getX() + ((1 - cosTheta) * _x * _z + _y * sinTheta)	* old_view.getZ();

		new_view[1] = ((1 - cosTheta) * _x * _y + _z * sinTheta) * old_view.getX();
		new_view[1] = new_view.getY() + (cosTheta + (1 - cosTheta) * _y * _y) * old_view.getY();
		new_view[1] = new_view.getY() + ((1 - cosTheta) * _y * _z - _x * sinTheta) * old_view.getZ();
 
		new_view[2] = ((1 - cosTheta) * _x * _z - _y * sinTheta) * old_view.getX();
		new_view[2] = new_view.getZ() + ((1 - cosTheta) * _y * _z + _x * sinTheta)	* old_view.getY();
		new_view[2] = new_view.getZ() + (cosTheta + (1 - cosTheta) * _z * _z) * old_view.getZ();
 
		m_target = m_position + new_view;
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////

	void CFPSCamera::rotateByMouse()
	{
		POINT mousePos;
		int middleX = CRender::getInstance()->getWidth() / 2;
		int middleY = CRender::getInstance()->getHeight() / 2;
		float angleY = 0.0f;
		float angleZ = 0.0f;	
		static float currentRotX = 0.0f;
		ShowCursor(0);
		GetCursorPos(&mousePos);
		if( (mousePos.x == middleX) && (mousePos.y == middleY) )
		{
			return;
		}
		SetCursorPos( middleX, middleY );

		angleY = (float)((middleX - mousePos.x)) / 1000.0f;
		angleZ = (float)((middleY - mousePos.y)) / 1000.0f;

		static float lastRotX = 0.0f;
		lastRotX = -currentRotX;	

		Vector3 vAxis = cross(Vector3(m_target - m_position), m_up);
		normalize(vAxis);

		if(currentRotX > 1.0f)
		{
			currentRotX = 1.0f;

			if(lastRotX != 1.0f)
			{		
				rotate(1.0f - lastRotX, vAxis[0], vAxis[1], vAxis[2]);
			}
		}
		else if(currentRotX < -1.0f)
		{
			currentRotX = -1.0f;
			if(lastRotX != -1.0f)
			{
				rotate( -1.0f - lastRotX, vAxis[0], vAxis[1], vAxis[2]);
			}
		}
		else
		{
			rotate(angleZ, vAxis[0], vAxis[1], vAxis[2]);
		}

		rotate(angleY, 0, 1, 0);
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////

	void CFPSCamera::update( double _dDeltaTime )
	{
		if ( !m_bIsVisible )
		{
			return;
		}

		if (m_bIsActive)
		{
			float s = 0.001f * (float)_dDeltaTime;
			if (CReciever::getInstance()->isKeyDown(KEY_KEY_W)) CFPSCamera::move(Vector3(0,0,-s)); //W
			if (CReciever::getInstance()->isKeyDown(KEY_KEY_S)) CFPSCamera::move(Vector3(0,0,s));  //S
			if (CReciever::getInstance()->isKeyDown(KEY_KEY_A)) CFPSCamera::move(Vector3(-s,0,0)); //A
			if (CReciever::getInstance()->isKeyDown(KEY_KEY_D)) CFPSCamera::move(Vector3(s,0,0));  //D
			CFPSCamera::rotateByMouse();

			CRender::getInstance()->udateCamera( m_position, m_target, m_up );
		}
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////

} //glliba