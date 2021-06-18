#pragma once

class Window
{
public:
	Window();
	virtual ~Window();

	// Utility
	const HWND getHandle() const { return windowHandle; }

	// easy-access to API
	BOOL Show(int nShowCmd) { return ::ShowWindow(windowHandle, nShowCmd); }
	BOOL Update() { return ::UpdateWindow(windowHandle); }
	bool registerClass(const WNDCLASS& wc) { return ((windowClass = ::RegisterClass(&wc)) != 0); }
	bool registerClassEx(const WNDCLASSEX& wc) { return ((windowClass = ::RegisterClassEx(&wc)) != 0); }

	// Events - for most of them, return FALSE if we process them
	virtual LRESULT onCreate(LPCREATESTRUCT lpCreate) { UNREFERENCED_PARAMETER(lpCreate); return TRUE; }
	virtual LRESULT onDestroy() { return TRUE; }
	virtual LRESULT onClose() { return TRUE; }
	virtual LRESULT onShow(BOOL beingShown, UINT status) { UNREFERENCED_PARAMETER(beingShown); UNREFERENCED_PARAMETER(status); return TRUE; }

	// Pure virtuals
	virtual bool create(const std::wstring& title, uint32_t width, uint32_t height) = 0;

	// Event procs
	virtual LRESULT windowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK handleWindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

protected:
	HINSTANCE hInstance;
	ATOM windowClass;
	HWND windowHandle;
};
