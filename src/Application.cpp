#include "preCompiled.h"

// set our window width and height
const uint32_t windowWidth = 800;
const uint32_t windowHeight = 600;

int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nShowCmd)
{
	// Create our window
	mainWindow window(L"WinGetUpdaterApp");
	if( !window.create(L"WinGet Updater", windowWidth, windowHeight) )
	{
		MessageBox(NULL, L"Window Creation Failed!", L"Error!", MB_ICONERROR | MB_OK);
		return EXIT_FAILURE;
	}

	// Display our window
	window.Show(nShowCmd);
	window.Update();

	// Run our message loop
	MSG msg;
	BOOL bRet;
	while( (bRet = GetMessage(&msg, 0, 0, 0)) != 0 )
	{
		// hwnd is an invalid parameter - quit
		if( bRet == -1 )
			return EXIT_FAILURE;

		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return EXIT_SUCCESS;
}
