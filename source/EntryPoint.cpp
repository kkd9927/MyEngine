#include <Windows.h>

#include "Engine/Runtime/Interface/IApplication.h"
#include "Engine/Runtime/Editor.h"

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	IApplication* app = new Editor;
	app->run();

	delete app;
	return 0;
}