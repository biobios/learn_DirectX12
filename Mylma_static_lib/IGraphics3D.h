#pragma once
#include "RefferenceResolution.h"
#include <string>
#include "IWindow3D.h"
namespace Mylma::Graphics3D {
	/// <summary>
	/// 3Dグラフィックスリソースを管理します
	/// </summary>
	class IGraphics3D {
	public:
		virtual IRenderer3DPtr getRenderer(const Mylma::GUI::IWindow3DRef window) = 0;
//		virtual void registerWindow(Mylma::GUI::Window3DRef window) = 0;
		virtual Mylma::GUI::IWindow3DRef createWindow(const std::wstring* window_name, int32_t width, int32_t height) = 0;
//		virtual void repaint(Mylma::GUI::Window3DRef window) = 0;
		virtual ~IGraphics3D() = 0 {}
	};

}
