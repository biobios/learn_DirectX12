#pragma once
#include "Window3D.h"
namespace Mylma::Graphics3D {
	class IGraphics3D {
	public:
		virtual IRenderer3DPtr getRenderer(const Mylma::GUI::Window3DRef window) = 0;
		virtual void registerWindow(Mylma::GUI::Window3DRef window) = 0;
		virtual void repaint(Mylma::GUI::Window3DRef window) = 0;
	};

	using IGraphics3DPtr = IGraphics3D*;
	using IGraphics3DRef = IGraphics3D&;
}
