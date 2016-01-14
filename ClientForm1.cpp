// main.cpp : main project file.

//David Lass & Chris Ebright
//114976970 & 11414871
//CS351
//Dr Hong

#include "ClientForm1.h"

using namespace Client6;

[STAThreadAttribute]
int main(array<System::String ^> ^args)
{
	// Enabling Windows XP visual effects before any controls are created
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false); 

	// Create the main window and run it
	Application::Run(gcnew Form1((args->Length>0)?args[0]:L"localhost")); //if ip is specified use that, otherwise local host
	return 0;
}