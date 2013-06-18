#include "CWinOpenGL.h"

extern "C" int Main(int argc, char** argv);

int _tmain(int argc, _TCHAR* argv[])
{
	int param = 0;

	CWinOpenGL::getInstance()->createWindow(1024, 768, false);
	
	param = Main(argc,argv);

	CWinOpenGL::getInstance()->windowMainLoop();
	CWinOpenGL::freeInstance();
	
	return param;	
}
