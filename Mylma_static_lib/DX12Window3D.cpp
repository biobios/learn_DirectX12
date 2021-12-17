#include "DX12Window3D.h"

Mylma::GUI::DX12Window3D::DX12Window3D(const std::wstring* name, LONG window_width, LONG window_height,
	Mylma::Graphics3D::DirectX12_3DRef direct_x) {

	width = window_width;
	height = window_height;

	WNDCLASSEX w = {};
	w.cbSize = sizeof(WNDCLASSEX);
	w.lpfnWndProc = (WNDPROC)messageRouter;
	w.lpszClassName = name->data();
	w.hInstance = GetModuleHandle(nullptr);
	
	RegisterClassEx(&w);
	RECT wrc = { 0,0,window_width, window_height };

	AdjustWindowRect(&wrc, WS_OVERLAPPEDWINDOW, false);

	window_handle = CreateWindow(w.lpszClassName,
		name->data(),
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
	IWindow3D::graphics = &direct_x;
}

void Mylma::GUI::DX12Window3D::setVisible(bool visible) {
	if (visible) ShowWindow(window_handle, SW_SHOW);
	else ShowWindow(window_handle, SW_HIDE);
}

LRESULT CALLBACK Mylma::GUI::DX12Window3D::messageRouter(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) noexcept {
	DX12Window3DPtr this_;
	if (msg == WM_CREATE) {
		this_ = reinterpret_cast<DX12Window3DPtr>(reinterpret_cast<LPCREATESTRUCT>(lparam)->lpCreateParams);
		SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this_));
	}
	else {
		this_ = reinterpret_cast<DX12Window3DPtr>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
	}
	return this_->wndProc(hwnd, msg, wparam, lparam);
}

LRESULT Mylma::GUI::DX12Window3D::wndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) noexcept {
	//ウィンドウが破棄されたら呼ばれる
	if (msg == WM_DESTROY)
	{
		::PostQuitMessage(0);//OSに対してこのアプリは終わると伝える
		return 0;
	}

	return ::DefWindowProc(hwnd, msg, wparam, lparam);//既定の処理
}

HWND Mylma::GUI::DX12Window3D::getWindowHandle() {
	return window_handle;
}

int32_t Mylma::GUI::DX12Window3D::getWidth() {
	return width;
}

int32_t Mylma::GUI::DX12Window3D::getHeight() {
	return height;
}
