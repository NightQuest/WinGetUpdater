#include "preCompiled.h"

Window::Window()
	: windowHandle(0), windowClass(0), hInstance(GetModuleHandle(NULL))
{
}

Window::~Window()
{
	if( windowClass )
	{
		// Free up the class, so it can be used again.
		::UnregisterClass(MAKEINTATOM(windowClass), hInstance);
		windowClass = 0;
	}
}

// Handle the messages, passing them off to our 'onEvent' functions
LRESULT Window::windowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch( msg )
	{
	case WM_CREATE:
		return onCreate(reinterpret_cast<LPCREATESTRUCT>(lParam));

	case WM_DESTROY:
		return onDestroy();

	case WM_CLOSE:
		return onClose();

	case WM_SHOWWINDOW:
		return onShow(static_cast<BOOL>(wParam), static_cast<UINT>(lParam));
	}

	return DefWindowProc(hwnd, msg, wParam, lParam);
}

// Forward our WindowProc to the correct class when/if we can
LRESULT CALLBACK Window::handleWindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	Window* window;
	if( msg == WM_NCCREATE ) // we're initializing the window
	{
		// Grab the window pointer from CreateParams, and store it in the user data for the window
		CREATESTRUCT* cs = reinterpret_cast<CREATESTRUCT*>(lParam);
		window = reinterpret_cast<Window*>(cs->lpCreateParams);
		::SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(window));
	}
	else // Grab the stored user data as a Window pointer
		window = reinterpret_cast<Window*>(::GetWindowLongPtr(hwnd, GWLP_USERDATA));

	// if no Window is present, just process normally
	if( !window )
		return ::DefWindowProc(hwnd, msg, wParam, lParam);

	// Otherwise, let the window class process everything
	return window->windowProc(hwnd, msg, wParam, lParam);
}