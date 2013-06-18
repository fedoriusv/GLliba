#include "CReciever.h"

namespace glliba
{
	///////////////////////////////////////////////////////////////////////////////////////////////

	CReciever::CReciever()
	{
		CReciever::resetKeyPress();
	}

	///////////////////////////////////////////////////////////////////////////////////////////////

	CReciever::~CReciever()
	{
	}

	///////////////////////////////////////////////////////////////////////////////////////////////

	bool CReciever::isKeyDown(EKEY_CODE _keyCode) const
	{
		return m_bKeyIsDown[_keyCode];
	}

	///////////////////////////////////////////////////////////////////////////////////////////////

	bool CReciever::isMouseDown(EMOUSE_INPUT_EVENT _keyCode) const
	{
		return m_bMouseIsStates[_keyCode];
	}

	///////////////////////////////////////////////////////////////////////////////////////////////

	bool CReciever::isMouseDragging( EKEY_CODE _keyCode ) const
	{
		return   ( m_mouseState.m_bLeftButtonDown && _keyCode == KEY_LBUTTON )
			|| ( m_mouseState.m_bMiddleButtonDown && _keyCode == KEY_MBUTTON )
			|| ( m_mouseState.m_bRightButtonDown && _keyCode == KEY_RBUTTON );
	}

	///////////////////////////////////////////////////////////////////////////////////////////////

	size_t	CReciever::checkSuccessiveClicks( int _mouseX, int _mouseY, EMOUSE_INPUT_EVENT _inputEvent )
	{
		//Double click
		const int MAX_MOUSEMOVE = 3;

		time_t clickTime = time(NULL);

		/*if ( (clickTime - MouseMultiClicks.LastClickTime) < MouseMultiClicks.DoubleClickTime
			&& core::abs_(MouseMultiClicks.LastClick.X - mouseX ) <= MAX_MOUSEMOVE
			&& core::abs_(MouseMultiClicks.LastClick.Y - mouseY ) <= MAX_MOUSEMOVE
			&& MouseMultiClicks.CountSuccessiveClicks < 3
			&& MouseMultiClicks.LastMouseInputEvent == inputEvent
		   )
		{
			++MouseMultiClicks.CountSuccessiveClicks;
		}
		else
		{
			MouseMultiClicks.CountSuccessiveClicks = 1;
		}

		MouseMultiClicks.LastMouseInputEvent = inputEvent;
		MouseMultiClicks.LastClickTime = clickTime;
		MouseMultiClicks.LastClick.X = mouseX;
		MouseMultiClicks.LastClick.Y = mouseY;

		return MouseMultiClicks.CountSuccessiveClicks;*/
		return 0;
	}

	///////////////////////////////////////////////////////////////////////////////////////////////

	void CReciever::resetKeyPress()
	{
		for (int i = 0; i < KEY_KEY_CODES_COUNT; ++i )
		{
			m_bKeyIsDown[i] = false;
		}

		for (int i = 0; i < EMIE_COUNT; ++i )
		{
			m_bMouseIsStates[i] = false;
		}
	}

	///////////////////////////////////////////////////////////////////////////////////////////////

	bool CReciever::OnEvent( const SEvent& _event )
	{
		if (_event.EventType == ET_KEY_INPUT_EVENT)
		{
			m_bKeyIsDown[_event.KeyInput.Key] = _event.KeyInput.PressedDown;
		}

		if (_event.EventType == ET_MOUSE_INPUT_EVENT)
		{
			for( size_t i = 0; i < EMIE_COUNT; ++i )
			{
				m_bMouseIsStates[i] = i == _event.MouseInput.Event;
			}
			m_mouseState.m_bLeftButtonDown =  _event.MouseInput.isLeftPressed();
			m_mouseState.m_bRightButtonDown =  _event.MouseInput.isRightPressed();;
			m_mouseState.m_bMiddleButtonDown = _event.MouseInput.isMiddlePressed();
			m_mouseState.m_wheel = _event.MouseInput.Wheel;
		}

		if (m_bMouseIsStates[EMIE_MOUSE_MOVED])
		{
			m_mouseState.m_position.setX( (float)_event.MouseInput.X );
			m_mouseState.m_position.setY( (float)_event.MouseInput.Y );
		}

		if( m_bMouseIsStates[EMIE_LMOUSE_PRESSED_DOWN] || m_bMouseIsStates[EMIE_RMOUSE_PRESSED_DOWN] )
		{
			m_mouseState.m_pressedPosition.setX( (float)_event.MouseInput.X );
			m_mouseState.m_pressedPosition.setY( (float)_event.MouseInput.Y );
		}

		if ( m_mouseState.m_bLeftButtonDown || m_mouseState.m_bRightButtonDown )
		{
			if ( m_bMouseIsStates[EMIE_MOUSE_MOVED] )
			{
				m_mouseState.m_dragg.setX( m_mouseState.m_pressedPosition.getX() - (float)_event.MouseInput.X );
				m_mouseState.m_dragg.setY( m_mouseState.m_pressedPosition.getY() - (float)_event.MouseInput.Y );
			}
		}

		return false;
	}

	///////////////////////////////////////////////////////////////////////////////////////////////
}