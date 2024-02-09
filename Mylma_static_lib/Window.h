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
		Window(const std::wstring& name, LONG width, LONG height);
		void setVisible(bool visible);
		static LRESULT CALLBACK messageRouter(HWND, UINT, WPARAM, LPARAM) noexcept;
		virtual LRESULT eventHandler(HWND, UINT, WPARAM, LPARAM) noexcept;
		LONG getWidth() const;
		LONG getHeight() const;
		HWND getHandle() const;
	protected:
	private:
		HWND window_handle;
		LONG width;
		LONG height;
	};
}

