#pragma once
#include "RefferenceResolution.h"
#include <string>
#include <Windows.h>
namespace mylml::windows {
	/// <summary>
	/// Windowsのウィンドウを管理する
	/// </summary>
	class Window
	{
	public:
		Window(const std::wstring* name, LONG width, LONG height);
		void setVisible(bool visible);
		static LRESULT CALLBACK messageRouter(HWND, UINT, WPARAM, LPARAM) noexcept;
		LRESULT eventHandler(HWND, UINT, WPARAM, LPARAM) noexcept;
	protected:
	private:
		HWND window_handle;
	};
}

