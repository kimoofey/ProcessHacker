
#include "stdafx.h"
#include "processInfo.h"
#include "MyForm.h"

using namespace System;
using namespace System::Windows::Forms;

//[STAThreadAttribute]
//int APIENTRY _tWinMain(HINSTANCE hInstance,
//	HINSTANCE hPrevInstance,
//	LPTSTR    lpCmdLine,
//	int       nCmdShow)
void Main() 
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	MBKS2::MyForm form;
	Application::Run(%form);
}