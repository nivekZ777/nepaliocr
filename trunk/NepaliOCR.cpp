#include "formMain.h"
#include "stdafx.h"
 
#include <windows.h>

using namespace NepaliOCR;

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	System::Threading::Thread::CurrentThread->ApartmentState = System::Threading::ApartmentState::STA;
	Application::Run(new formMain());
	return 0;
}
