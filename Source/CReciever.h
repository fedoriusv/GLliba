#ifndef _CRECIEVER_H_
#define _CRECIEVER_H_

#include <time.h>

#include "CSingleton.h"

#include "KeyCodes.h"
#include "CObject.h"

namespace glliba
{
	///////////////////////////////////////////////////////////////////////////////////////////////

	enum EVENT_TYPE
	{
		ET_KEY_INPUT_EVENT,
		ET_MOUSE_INPUT_EVENT
	};


	struct SEvent
	{
		struct SMouseInput
		{
			//! X position of mouse cursor
			int X;

			//! Y position of mouse cursor
			int Y;

			//! mouse wheel delta, usually 1.0 or -1.0.
			/** Only valid if event was MIE_MOUSE_WHEEL */
			float Wheel;

			//! True if shift was also pressed
			bool Shift:1;

			//! True if ctrl was also pressed
			bool Control:1;

			//! A bitmap of button states. You can use isButtonPressed() to determine
			//! if a button is pressed or not.
			//! Currently only valid if the event was MIE_MOUSE_MOVED
			unsigned int ButtonStates;

			//! Is the left button pressed down?
			bool isLeftPressed() const { return 0 != ( ButtonStates & KEY_LBUTTON ); }

			//! Is the right button pressed down?
			bool isRightPressed() const { return 0 != ( ButtonStates & KEY_RBUTTON ); }

			//! Is the middle button pressed down?
			bool isMiddlePressed() const { return 0 != ( ButtonStates & KEY_MBUTTON ); }

			//! Type of mouse event
			EMOUSE_INPUT_EVENT Event;
		};

		//! Any kind of keyboard event.
		struct SKeyInput
		{
			//! Character corresponding to the key (0, if not a character)
			wchar_t Char;

			//! Key which has been pressed or released
			EKEY_CODE Key;

			//! If not true, then the key was left up
			bool PressedDown:1;

			//! True if shift was also pressed
			bool Shift:1;

			//! True if ctrl was also pressed
			bool Control:1;
		};

		EVENT_TYPE	EventType;
		union
		{
			struct SMouseInput MouseInput;
			struct SKeyInput KeyInput;
		};
	};

	/*struct SMouseMultiClicks
	{
		SMouseMultiClicks()
			: DoubleClickTime(500), CountSuccessiveClicks(0), LastClickTime(0), LastMouseInputEvent(EMIE_COUNT)
		{}

		u32 DoubleClickTime;
		u32 CountSuccessiveClicks;
		u32 LastClickTime;
		core::position2di LastClick;
		EMOUSE_INPUT_EVENT LastMouseInputEvent;
	};
	SMouseMultiClicks MouseMultiClicks;*/

	///////////////////////////////////////////////////////////////////////////////////////////////

	class CReciever : public CSingleton<CReciever>
	{
	public:

		CReciever();
		virtual			~CReciever();

		struct SMouseState
		{
			Vector2		m_position;
			Vector2		m_pressedPosition;
			Vector2		m_dragg;
			float		m_wheel;
			bool		m_bLeftButtonDown;
			bool		m_bRightButtonDown;
			bool		m_bMiddleButtonDown;
			SMouseState() 
				: m_dragg(0.0f,0.0f)
				, m_position(0.0f,0.0f)
				, m_pressedPosition(0.0f,0.0f)
				, m_bLeftButtonDown(false)
				, m_bRightButtonDown(false)
				, m_bMiddleButtonDown(false)
			{
			}
		};
		SMouseState			m_mouseState;

		virtual bool		OnEvent( const SEvent& _event );

		virtual bool		isMouseDown		( EMOUSE_INPUT_EVENT _keyCode ) const;
		virtual bool		isMouseDragging ( EKEY_CODE _keyCode ) const;
		virtual bool		isKeyDown		( EKEY_CODE _keyCode ) const;
		virtual void		resetKeyPress();

		virtual size_t		checkSuccessiveClicks( int _mouseX, int _mouseY, EMOUSE_INPUT_EVENT _inputEvent );


		bool				m_bKeyIsDown[ KEY_KEY_CODES_COUNT ];
		bool				m_bMouseIsStates[ EMIE_COUNT ];
	};

	///////////////////////////////////////////////////////////////////////////////////////////////

} //glliba

#endif