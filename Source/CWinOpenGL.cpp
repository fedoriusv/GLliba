#include "CWinOpenGL.h"
#include "CApplication.h"
#include "CRenderGL.h"

#define RECIEVER	CApplication::getInstance()->getReciever()
#define WINDOW		CWinOpenGL::getInstance()

HINSTANCE CWinOpenGL::s_hInstance = NULL;
HWND      CWinOpenGL::s_hWnd      = NULL;
HDC       CWinOpenGL::s_hDC       = NULL;
HGLRC     CWinOpenGL::s_hRC       = NULL;

CWinOpenGL::CWinOpenGL()
	: m_iPixelFormat(0)
	, m_bExContext(false)

	, m_bFullScreen(false)
	, m_iWidht(0)
	, m_iHeight(0)
	
	, m_bIsActive(true)
{	  
}

CWinOpenGL::~CWinOpenGL()
{
	destroyWindow();
}

bool CWinOpenGL::createWindow( int _iWidth, int _iHeight, bool _bFullscreen )
{
	m_iWidht		= _iWidth;
	m_iHeight		= _iHeight;
	m_bFullScreen	= _bFullscreen;

	if (!createContextOpenGL())
	{
		ASSERT( FALSE && "Couldn't initialize Context!");
		return FALSE;
	}

	if (!createExContextOpenGL())
	{
		ASSERT( FALSE && "Couldn't initialize ExContext!");
		return FALSE;
	}
	LOG_CONSOLE("Windows created");

	CRenderGL::getInstance()->init(s_hWnd);

	return TRUE;
}

HWND CWinOpenGL::createWinWindow()
{
	DWORD		dwExStyle;										// Window Extended Style
	DWORD		dwStyle;										// Window Style

	WNDCLASS wc;
	wc.style			= CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc		= (WNDPROC) WindowProc;
	wc.cbClsExtra		= 0;
	wc.cbWndExtra		= 0;
	wc.hInstance		= GetModuleHandle(NULL);
	wc.hIcon			= LoadIcon(NULL, IDI_WINLOGO);
	wc.hCursor			= LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground	= NULL;
	wc.lpszMenuName		= NULL;
	wc.lpszClassName	= "MainWin";

	if (!RegisterClass(&wc))										
	{
		MessageBox(NULL,"Failed To Register The Window Class.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;												
	}

	if (m_bFullScreen)												
	{
		DEVMODE dmScreenSettings;									// Device Mode
		memset(&dmScreenSettings,0,sizeof(dmScreenSettings));		// Makes Sure Memory's Cleared
		dmScreenSettings.dmSize=sizeof(dmScreenSettings);			// Size Of The Devmode Structure
		dmScreenSettings.dmPelsWidth	= m_iWidht;					// Selected Screen Width
		dmScreenSettings.dmPelsHeight	= m_iHeight;				// Selected Screen Height
		dmScreenSettings.dmBitsPerPel	= 32;						// Selected Bits Per Pixel
		dmScreenSettings.dmFields= DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		// Try To Set Selected Mode And Get Results.  NOTE: CDS_FULLSCREEN Gets Rid Of Start Bar.
		if (ChangeDisplaySettings(&dmScreenSettings,CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
		{
			// If The Mode Fails, Offer Two Options.  Quit Or Use Windowed Mode.
			if (MessageBox(NULL,"The Requested Fullscreen Mode Is Not Supported By\nYour Video Card. Use Windowed Mode Instead?","NeHe GL",MB_YESNO|MB_ICONEXCLAMATION)==IDYES)
			{
				m_bFullScreen = FALSE;							
			}
			else
			{
				MessageBox(NULL,"Program Will Now Close.","ERROR",MB_OK|MB_ICONSTOP);
				return FALSE;									
			}
		}
	}

	if (m_bFullScreen)											
	{
		dwExStyle	= WS_EX_APPWINDOW;								// Window Extended Style
		dwStyle		= WS_POPUP;										// Windows Style
		ShowCursor(FALSE);											// Hide Mouse Pointer
	}
	else
	{
		dwExStyle	= WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;			// Window Extended Style
		dwStyle		= WS_OVERLAPPEDWINDOW;							// Windows Style
	}

	int posX = (GetSystemMetrics(SM_CXSCREEN) - m_iWidht ) / 2;
	int posY = (GetSystemMetrics(SM_CYSCREEN) - m_iHeight) / 2;
	RECT wRect;
	wRect.left		= posX;
	wRect.right		= posX + (long)m_iWidht;
	wRect.top		= posY;
	wRect.bottom	= posY + (long)m_iHeight;

	AdjustWindowRectEx(&wRect, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU, FALSE, WS_EX_APPWINDOW | WS_EX_WINDOWEDGE);
	//AdjustWindowRectEx(&wRect, dwStyle, FALSE, dwExStyle);		// Adjust Window To True Requested Size

	//WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU,		- not sizeble
	//dwStyle |	WS_CLIPSIBLINGS | WS_CLIPCHILDREN,	- sizeble
	HWND hwnd = CreateWindowEx(
		dwExStyle,													// Extended Style For The Window
		"MainWin",													// Class Name
		"GLLib by Fred",											// Window Title
		//dwStyle |													// Defined Window Style
		WS_OVERLAPPED |	WS_CAPTION | WS_SYSMENU,
		0, 0,														// Window Position
		wRect.right - wRect.left,									// Calculate Window Width
		wRect.bottom - wRect.top,									// Calculate Window Height
		NULL,														// No Parent Window
		NULL,														// No Menu
		GetModuleHandle(NULL),										// Instance
		NULL);														// Dont Pass Anything To WM_CREATE

	return hwnd;
}

void CWinOpenGL::destroyWindow()										
{
	if (m_bFullScreen)											
	{
		ChangeDisplaySettings(NULL, 0);								// If So Switch Back To The Desktop
		ShowCursor(TRUE);											// Show Mouse Pointer
	}

	if (s_hRC)														
	{
		if (!wglMakeCurrent(NULL, NULL))							
		{
			ASSERT( FALSE || "Release Of DC And RC Failed.");
		}

		if (!wglDeleteContext(s_hRC))								
		{
			ASSERT( FALSE || "Release Rendering Context Failed.");
		}
		s_hRC = NULL;												
	}

	if (s_hDC && !ReleaseDC(s_hWnd, s_hDC))						
	{
		ASSERT(NULL || "Release Device Context Failed.");
		s_hDC = NULL;											
	}

	if (s_hWnd && !DestroyWindow(s_hWnd))						
	{
		ASSERT(NULL || "Could Not Release hWnd.");
		s_hWnd = NULL;											
	}

	if (!UnregisterClass("MainWin",GetModuleHandle(NULL)))		
	{
		ASSERT(NULL || "Could Not Unregister Class.");
		s_hInstance = NULL;										
	}
}

bool CWinOpenGL::createContextOpenGL()
{
	PIXELFORMATDESCRIPTOR pfd =									// pfd Tells Windows How We Want Things To Be
	{
		sizeof(PIXELFORMATDESCRIPTOR),							// Size Of This Pixel Format Descriptor
		1,														// Version Number
		PFD_DRAW_TO_WINDOW|PFD_SUPPORT_OPENGL|PFD_DOUBLEBUFFER,	// Format Support Window and OpenGL
		PFD_TYPE_RGBA,											// Request An RGBA Format
		32,														// Select Our Color Depth
		0, 0, 0, 0, 0, 0,										// Color Bits Ignored
		0,														// No Alpha Buffer
		0,														// Shift Bit Ignored
		0,														// No Accumulation Buffer
		0, 0, 0, 0,												// Accumulation Bits Ignored
		24,														// 16Bit Z-Buffer (Depth Buffer)  
		0,														// No Stencil Buffer
		0,														// No Auxiliary Buffer
		PFD_MAIN_PLANE,											// Main Drawing Layer
		0,														// Reserved
		0, 0, 0													// Layer Masks Ignored
	};

	if (!(s_hWnd = createWinWindow()))
	{
		ASSERT( FALSE && "Can't Create Win Windows." );
		return FALSE;		
	}
		
	if (!(s_hDC = GetDC(s_hWnd)))										
	{
		ASSERT( FALSE && "Can't Create A GL Device Context." );
		return FALSE;									
	}

	if (!m_iPixelFormat)
	{
		m_iPixelFormat = ChoosePixelFormat(s_hDC, &pfd);
	}

	if (!m_iPixelFormat || !SetPixelFormat(s_hDC, m_iPixelFormat, &pfd)) 
	{
		ASSERT( FALSE && "Can't Set The PixelFormat" );
		return FALSE;								
	}

	if (m_bExContext)
	{
		int attribs[] =
		{
			WGL_CONTEXT_MAJOR_VERSION_ARB, 3,
			WGL_CONTEXT_MINOR_VERSION_ARB, 3,
			WGL_CONTEXT_FLAGS_ARB,         WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,
			WGL_CONTEXT_PROFILE_MASK_ARB,  WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
			0
		};

		s_hRC = wglCreateContextAttribsARB(s_hDC, 0, attribs);
	}
	else
	{
		s_hRC = wglCreateContext(s_hDC);
	}

	if (!s_hRC || !wglMakeCurrent(s_hDC, s_hRC))						
	{
		ASSERT( FALSE && "Can't Create GL Rendering Context." );
		return FALSE;								
	}

	return TRUE;
}

bool CWinOpenGL::createExContextOpenGL()
{
	GLuint	numFormats;

	GLfloat	fAttributes[] = {0,0};
	GLint	iAttributes[] =
	{
		WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,
		WGL_SUPPORT_OPENGL_ARB, GL_TRUE,
		WGL_ACCELERATION_ARB,	WGL_FULL_ACCELERATION_ARB,
		WGL_COLOR_BITS_ARB,		24,
		WGL_ALPHA_BITS_ARB,		8,
		WGL_DEPTH_BITS_ARB,		24,
		WGL_STENCIL_BITS_ARB,	0,
		WGL_DOUBLE_BUFFER_ARB,	GL_TRUE,
		WGL_SAMPLE_BUFFERS_ARB,	GL_TRUE,
		WGL_SAMPLES_ARB,		8,
		0,0
	};

	GLenum err = glewInit();
	if (err !=  GLEW_OK )
	{
		LOG_CONSOLE( glewGetErrorString(err) );
		ASSERT( FALSE && "Couldn't initialize GLEW!");
	}
	LOG_CONSOLE( "Initialize GLEW lib");

	if( !wglewIsSupported("WGL_ARB_create_context")||
		!wglewIsSupported("WGL_ARB_pixel_format"  )|| 
		!wglewIsSupported("WGL_ARB_multisample"   ) )
	{
		ASSERT(FALSE && "Error Supported GLEW Lib");
		return FALSE;	
	}

	if ( !wglChoosePixelFormatARB( s_hDC, iAttributes, fAttributes, 1, &m_iPixelFormat, &numFormats) )
	{
		ASSERT(FALSE && "Can't Find A Suitable ExPixelFormat.");
		return FALSE;								
	}

	m_bExContext = true;
	destroyWindow();

	if (!createContextOpenGL())
	{
		return FALSE;
	}

	ShowWindow(s_hWnd, SW_SHOW);						
	SetForegroundWindow(s_hWnd);						
	SetFocus(s_hWnd);			

	return TRUE;
}

int	CWinOpenGL::windowMainLoop()
{
	bool done = FALSE;

	MSG msg;
	ZeroMemory(&msg, sizeof(msg));

	while (msg.message != WM_QUIT /*|| !done*/)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		CApplication::getInstance()->run();
		SwapBuffers( s_hDC );

		if (m_bIsActive)											
		{
			if (RECIEVER->isKeyDown(KEY_ESCAPE))				
			{
				done = TRUE;
				destroyWindow();						
				exit(0);
			}
		}

		if (RECIEVER->isKeyDown(KEY_F1))						
		{
			RECIEVER->resetKeyPress();
			destroyWindow();							
			m_bFullScreen =! m_bFullScreen;						
															
			if (!createContextOpenGL())
			{
				return 0;										
			}
		}
	}

	return 0;
}


LRESULT CALLBACK WindowProc(HWND _hwnd, UINT _msg, WPARAM _wParam, LPARAM _lParam)
{

#ifndef WM_MOUSEWHEEL
#	define WM_MOUSEWHEEL 0x020A
#endif
#ifndef WHEEL_DELTA
#	define WHEEL_DELTA 120
#endif

	SEvent event;

	static size_t ClickCount = 0;
	if (GetCapture() != _hwnd && ClickCount > 0)
	{
		ClickCount = 0;
	}


	switch (_msg)
	{
	case WM_ACTIVATE:									// Watch For Window Activate Message
		{
			if (!HIWORD(_wParam))						// Check Minimization State
			{
				WINDOW->setIsActive(TRUE);				// Program Is Active
			}
			else
			{
				WINDOW->setIsActive(FALSE);				// Program Is No Longer Active
			}

			return 0;									// Return To The Message Loop
		}

	case WM_CLOSE:
		{
			PostQuitMessage(0);
			return 0;
		}
	
	case WM_SYSKEYDOWN:
	case WM_SYSKEYUP:
	case WM_KEYUP:		
	case WM_KEYDOWN:									// Is A Key Being Held Down?
		{
			BYTE allKeys[256];

			event.EventType = ET_KEY_INPUT_EVENT;
			event.KeyInput.Key = (EKEY_CODE)_wParam;
			event.KeyInput.PressedDown = ( _msg == WM_KEYDOWN || _msg == WM_SYSKEYDOWN );
			
			const UINT MY_MAPVK_VSC_TO_VK_EX = 3; // MAPVK_VSC_TO_VK_EX should be in SDK according to MSDN, but isn't in mine.
			if ( event.KeyInput.Key == KEY_SHIFT )
			{
				// this will fail on systems before windows NT/2000/XP, not sure _what_ will return there instead.
				event.KeyInput.Key = (EKEY_CODE)MapVirtualKey( ((_lParam>>16) & 255), MY_MAPVK_VSC_TO_VK_EX );
			}

			if ( event.KeyInput.Key == KEY_CONTROL )
			{
				event.KeyInput.Key = (EKEY_CODE)MapVirtualKey( ((_lParam>>16) & 255), MY_MAPVK_VSC_TO_VK_EX );
				// some keyboards will just return LEFT for both - left and right keys. So also check extend bit.
				if (_lParam & 0x1000000)
				{
					event.KeyInput.Key = KEY_RCONTROL;
				}
			}

			GetKeyboardState(allKeys);

			event.KeyInput.Shift = ((allKeys[VK_SHIFT] & 0x80)!=0);
			event.KeyInput.Control = ((allKeys[VK_CONTROL] & 0x80)!=0);

			RECIEVER->OnEvent(event);

			if ( _msg == WM_SYSKEYDOWN || _msg == WM_SYSKEYUP )
				return DefWindowProc( _hwnd, _msg, _wParam, _lParam );
			else
				return 0;
		}

	case WM_LBUTTONDOWN:
	case WM_LBUTTONUP:
	case WM_RBUTTONDOWN:
	case WM_RBUTTONUP:
	case WM_MBUTTONDOWN:
	case WM_MBUTTONUP:
	case WM_MOUSEMOVE:
	case WM_MOUSEWHEEL:
		{
			if (_msg == WM_LBUTTONDOWN || _msg == WM_RBUTTONDOWN || _msg == WM_MBUTTONDOWN )
			{
				ClickCount++;
				SetCapture(_hwnd);
			}
			else
			if ( _msg == WM_LBUTTONUP || _msg == WM_RBUTTONUP || _msg == WM_MBUTTONUP )
			{
				ClickCount--;
				if ( ClickCount < 1 )
				{
					ClickCount = 0;
					ReleaseCapture();
				}
			}

			EMOUSE_INPUT_EVENT mouseEvent = EMIE_LMOUSE_PRESSED_DOWN;

			switch (_msg)
			{
				case WM_LBUTTONDOWN:	mouseEvent = EMIE_LMOUSE_PRESSED_DOWN;	break;
				case WM_LBUTTONUP:		mouseEvent = EMIE_LMOUSE_LEFT_UP;		break;
				case WM_RBUTTONDOWN:	mouseEvent = EMIE_RMOUSE_PRESSED_DOWN;	break;
				case WM_RBUTTONUP:		mouseEvent = EMIE_RMOUSE_LEFT_UP;		break;
				case WM_MBUTTONDOWN:	mouseEvent = EMIE_MMOUSE_PRESSED_DOWN;	break;
				case WM_MBUTTONUP:		mouseEvent = EMIE_MMOUSE_LEFT_UP;		break;
				case WM_MOUSEMOVE:		mouseEvent = EMIE_MOUSE_MOVED;			break;
				case WM_MOUSEWHEEL:		mouseEvent = EMIE_MOUSE_WHEEL;			break;
			};

			event.EventType = ET_MOUSE_INPUT_EVENT;
			event.MouseInput.Event = (EMOUSE_INPUT_EVENT) mouseEvent;
			event.MouseInput.X = (short)LOWORD(_lParam);
			event.MouseInput.Y = (short)HIWORD(_lParam);
			event.MouseInput.Shift = ((LOWORD(_wParam) & MK_SHIFT) != 0);
			event.MouseInput.Control = ((LOWORD(_wParam) & MK_CONTROL) != 0);
			// left and right mouse buttons
			event.MouseInput.ButtonStates = _wParam & ( MK_LBUTTON | MK_RBUTTON);
			// middle button
			if (_wParam & MK_MBUTTON)
			{
				event.MouseInput.ButtonStates |= VK_MBUTTON;
			}
			event.MouseInput.Wheel = 0.f;
			// wheel
			if ( _msg == WM_MOUSEWHEEL )
			{
				POINT p; // fixed by jox
				p.x = 0; p.y = 0;
				ClientToScreen(_hwnd, &p);
				event.MouseInput.X -= p.x;
				event.MouseInput.Y -= p.y;
				event.MouseInput.Wheel = ((float)((short)HIWORD(_wParam))) / (float)WHEEL_DELTA;
			}

			RECIEVER->OnEvent(event);
			/*if ( event.MouseInput.Event >= EMIE_LMOUSE_PRESSED_DOWN && event.MouseInput.Event <= EMIE_MMOUSE_PRESSED_DOWN )
			{
				size_t clicks = dev->checkSuccessiveClicks(event.MouseInput.X, event.MouseInput.Y, event.MouseInput.Event);
				if ( clicks == 2 )
				{
					event.MouseInput.Event = (irr::EMOUSE_INPUT_EVENT)(irr::EMIE_LMOUSE_DOUBLE_CLICK + event.MouseInput.Event-irr::EMIE_LMOUSE_PRESSED_DOWN);
					dev->postEventFromUser(event);
				}
				else if ( clicks == 3 )
				{
					event.MouseInput.Event = (irr::EMOUSE_INPUT_EVENT)(irr::EMIE_LMOUSE_TRIPLE_CLICK + event.MouseInput.Event-irr::EMIE_LMOUSE_PRESSED_DOWN);
					dev->postEventFromUser(event);
				}
			}
			*/
			return 0;
		}
		
	case WM_SIZE:												// Resize The OpenGL Window
		{
			RENDERER->reshape(LOWORD(_lParam),HIWORD(_lParam));	// LoWord=Width, HiWord=Height
			return 0;											// Jump Back
		}

		RECIEVER->OnEvent(event);
	}

	return DefWindowProc(_hwnd, _msg, _wParam, _lParam);
}