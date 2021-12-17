#include <Windows.h>
#ifdef _DEBUG
#include <iostream>
#endif

#include "needInclude.h"

#include "IWindow3D.h"
#include "DirectX12_3D.h"

#include "MyWindowContent.h"

#ifdef _DEBUG
int main() {
#else
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
#endif
	Mylma::Graphics3D::IGraphics3DPtr graphics = Mylma::Graphics3D::DirectX12_3D::create();
	std::wstring window_name = std::wstring(L"DirectXƒeƒXƒg");
	Mylma::GUI::IWindow3DRef window = graphics->createWindow(&window_name, 100, 100);
	window.setContent(new MyWindowContent());
	window.setVisible(true);
	window.paint();
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
