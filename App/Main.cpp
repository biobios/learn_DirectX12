#include <Windows.h>
#ifdef _DEBUG
#include <iostream>
#endif

#include "DirectX12_3D.h"

#include "MyWindowContent.h"
#include "Window3D.h"

#ifdef _DEBUG
int main() {
#else
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
#endif
	auto graphics = new Mylma::Graphics3D::DirectX12_3D();
	std::wstring window_name = std::wstring(L"DirectXƒeƒXƒg");
	auto window = new Mylma::GUI::Window3D<Mylma::Graphics3D::DirectX12_3D>(window_name, (LONG)800, (LONG)600, *graphics);
	window->setContent(new MyWindowContent());
	window->setVisible(true);
	window->paint();
	MSG msg = {};
	while (true) {
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		if (msg.message == WM_QUIT) {
			break;
		}
	}
	getchar();
	return 0;
}
