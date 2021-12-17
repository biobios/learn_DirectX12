#pragma once

#include <Windows.h>
#include "IGraphics3D.h"
#include "IRenderer3D.h"

namespace Mylma::GUI {
	class Window3D {
	public:
		Window3D(const TCHAR* window_name, LONG width, LONG height);
		//void setEventListener();
		LRESULT wndProc(HWND, UINT, WPARAM, LPARAM) noexcept;
		static LRESULT CALLBACK messageRouter(HWND, UINT, WPARAM, LPARAM) noexcept;
		void setVisible(bool);
		HWND getWindowHandle();
		LONG getWidth();
		LONG getHeight();
		void setIGraphics3D(Mylma::Graphics3D::IGraphics3DPtr g);
		virtual void paint(Mylma::Graphics3D::IRenderer3DRef a);
	private:
		HWND window_handle;
		LONG width;
		LONG height;
	};

	using Window3DPtr = Window3D*;
	using Window3DRef = Window3D&;
}
