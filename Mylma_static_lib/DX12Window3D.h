#pragma once
#include "RefferenceResolution.h"

#include <string>
#include <Windows.h>
#include "IWindow3D.h"
#include "IGraphics3D.h"
#include "IRenderer3D.h"
#include "DirectX12_3D.h"

namespace Mylma::GUI {
	class DX12Window3D : public IWindow3D {
	public:
		DX12Window3D(const std::wstring* name, LONG width, LONG height, Mylma::Graphics3D::DirectX12_3DRef direct_x);
		//void setEventListener();
		LRESULT wndProc(HWND, UINT, WPARAM, LPARAM) noexcept;
		static LRESULT CALLBACK messageRouter(HWND, UINT, WPARAM, LPARAM) noexcept;
		void setVisible(bool) override;
		HWND getWindowHandle();
		int32_t getWidth() override;
		int32_t getHeight() override;
	private:
		HWND window_handle;
		LONG width;
		LONG height;
	};

}