#include "Window3D.h"

Mylma::GUI::Window3D::Window3D(const TCHAR* window_name, LONG window_width, LONG window_height) {
	width = window_width;
	height = window_height;

	WNDCLASSEX w = {};
	w.cbSize = sizeof(WNDCLASSEX);
	w.lpfnWndProc = (WNDPROC)messageRouter;
	w.lpszClassName = window_name;
	w.hInstance = GetModuleHandle(nullptr);
	
	RegisterClassEx(&w);
	RECT wrc = { 0,0,window_width, window_height };

	AdjustWindowRect(&wrc, WS_OVERLAPPEDWINDOW, false);

	window_handle = CreateWindow(w.lpszClassName,
		window_name,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		wrc.right - wrc.left,
		wrc.bottom - wrc.top,
		nullptr,
		nullptr,
		w.hInstance,
		nullptr);

	UnregisterClass(w.lpszClassName, w.hInstance);
}

void Mylma::GUI::Window3D::setVisible(bool visible) {
	if (visible) ShowWindow(window_handle, SW_SHOW);
	else ShowWindow(window_handle, SW_HIDE);
}

LRESULT CALLBACK Mylma::GUI::Window3D::messageRouter(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) noexcept {
	Window3D* this_;
	if (msg == WM_CREATE) {
		this_ = reinterpret_cast<Window3D*>(reinterpret_cast<LPCREATESTRUCT>(lparam)->lpCreateParams);
		SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this_));
	}
	else {
		this_ = reinterpret_cast<Window3D*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
	}
	return this_->wndProc(hwnd, msg, wparam, lparam);
}

LRESULT Mylma::GUI::Window3D::wndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) noexcept {
	//ウィンドウが破棄されたら呼ばれる
	if (msg == WM_DESTROY)
	{
		::PostQuitMessage(0);//OSに対してこのアプリは終わると伝える
		return 0;
	}

	return ::DefWindowProc(hwnd, msg, wparam, lparam);//既定の処理
}

HWND Mylma::GUI::Window3D::getWindowHandle() {
	return window_handle;
}

LONG Mylma::GUI::Window3D::getWidth() {
	return width;
}

LONG Mylma::GUI::Window3D::getHeight() {
	return height;
}

void Mylma::GUI::Window3D::paint(Mylma::Graphics3D::IRenderer3DRef r) {
	//r.setBackground(color);
	//r.clear();
}