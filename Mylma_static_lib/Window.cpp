#include "Window.h"
mylml::windows::Window::Window(const std::wstring& name, LONG window_width, LONG window_height) {

	width = window_width;
	height = window_height;

	WNDCLASSEX w = {};
	w.cbSize = sizeof(WNDCLASSEX);
	w.lpfnWndProc = (WNDPROC)messageRouter;
	w.lpszClassName = name.data();
	w.hInstance = GetModuleHandle(nullptr);

	RegisterClassEx(&w);
	RECT wrc = { 0,0,window_width, window_height };

	AdjustWindowRect(&wrc, WS_OVERLAPPEDWINDOW, false);

	window_handle = CreateWindow(w.lpszClassName,
		name.data(),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		wrc.right - wrc.left,
		wrc.bottom - wrc.top,
		nullptr,
		nullptr,
		w.hInstance,
		this);
}

void mylml::windows::Window::setVisible(bool visible) {
	if (visible) ShowWindow(window_handle, SW_SHOW);
	else ShowWindow(window_handle, SW_HIDE);
}

LRESULT CALLBACK mylml::windows::Window::messageRouter(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) noexcept {
	WindowPtr this_;
	if (msg == WM_CREATE) {
		this_ = reinterpret_cast<WindowPtr>(reinterpret_cast<LPCREATESTRUCT>(lparam)->lpCreateParams);
		SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this_));
	}
	else {
		this_ = reinterpret_cast<WindowPtr>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
	}

	if(this_ != nullptr)
		return this_->eventHandler(hwnd, msg, wparam, lparam);
	else
		return ::DefWindowProc(hwnd, msg, wparam, lparam);
}

LRESULT mylml::windows::Window::eventHandler(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) noexcept {
	//ウィンドウが破棄されたら呼ばれる
	if (msg == WM_DESTROY)
	{
		::PostQuitMessage(0);//OSに対してこのアプリは終わると伝える
		return 0;
	}

	return ::DefWindowProc(hwnd, msg, wparam, lparam);//既定の処理
}

LONG mylml::windows::Window::getWidth() const
{
	return width;
}

LONG mylml::windows::Window::getHeight() const
{
	return height;
}

HWND mylml::windows::Window::getHandle() const
{
	return window_handle;
}
