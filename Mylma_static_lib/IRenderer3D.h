#pragma once
#include "Color.h"
namespace Mylma::Graphics3D {
	/// <summary>
	/// �E�B���h�E��3D�����_�����O���s���܂�
	/// </summary>
	class IRenderer3D {
	public:
		virtual void clear() = 0;
		virtual void execute() = 0;
		virtual void reset() = 0;
		virtual void setBackground(Mylma::Graphics::ColorRef color) = 0;
		virtual void setColor(Mylma::Graphics::ColorRef color) = 0;
	};

	using IRenderer3DPtr = IRenderer3D*;
	using IRenderer3DRef = IRenderer3D&;
}