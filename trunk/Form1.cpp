#include "stdafx.h"
#include "FormMainWindow.h"
#include <windows.h>

using namespace Exercise1;

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	System::Threading::Thread::CurrentThread->ApartmentState = System::Threading::ApartmentState::STA;
	Application::Run(new Form1());
	return 0;
}
