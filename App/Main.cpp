#include <Windows.h>
#ifdef _DEBUG
#include <iostream>
#endif

#include "Window3D.h"
#include "DirectX12_3D.h"
#include "MyFrame.h"

#ifdef _DEBUG
int main() {
#else
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
#endif
	Mylma::GUI::Window3D* window = new MyFrame();
	Mylma::Graphics3D::IGraphics3DPtr graphics = Mylma::Graphics3D::DirectX12_3D::create();
	graphics->registerWindow(*window);
	window->setVisible(true);
	graphics->repaint(*window);
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
