#include "MyForm.h"
#include "settings_dialog.h"
// robot_ui.cpp : main project file.

#include <stdio.h>
#include <windows.h>
#include <Winuser.h>

#pragma comment(lib, "user32.lib")
#pragma comment(lib, "hid.lib")
#pragma comment(lib, "winmm.lib")

using namespace opencv_winforms;

[STAThreadAttribute]
int main(array<System::String ^> ^args)
{
	AllocConsole();
	freopen("CON","wb",stdout);
	//FreeConsole();

	// Enabling Windows XP visual effects before any controls are created
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false); 

	// Create the main window and run it
	Application::Run(gcnew MyForm());
	return 0;
}

