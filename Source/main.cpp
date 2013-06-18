#include "CApplication.h"

extern "C" int Main(int argc, char** argv)
{
	CApplication* app = CApplication::getInstance();
	app->init();
	app->run();

	return 0;
}