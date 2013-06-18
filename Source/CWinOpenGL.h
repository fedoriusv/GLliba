#ifndef _CWINOPENGL_H_
#define _CWINOPENGL_H_

#include "../Project/WinProj/stdafx.h"
#include <windows.h>

#include "CSingleton.h"

using namespace glliba;

class CWinOpenGL : public CSingleton<CWinOpenGL>
{
private:
	static HINSTANCE	s_hInstance;
	static HWND			s_hWnd;
	static HDC			s_hDC;
	static HGLRC		s_hRC;

	int					m_iPixelFormat;
	bool				m_bExContext;

	bool				m_bFullScreen;
	int					m_iWidht;
	int					m_iHeight;

	bool				m_bIsActive;

	HWND				createWinWindow();
	bool				createContextOpenGL();
	bool				createExContextOpenGL();

public:

	CWinOpenGL();
	~CWinOpenGL();

	bool				createWindow( int _iWidth, int _iHeight, bool _bFullscreen = false );
	int					windowMainLoop();
	void				destroyWindow();

	void				setIsActive( bool _bIsActive ) { m_bIsActive = _bIsActive; }
};

LRESULT CALLBACK		WindowProc(HWND _hwnd, UINT _msg, WPARAM _wParam, LPARAM _lParam);

#endif