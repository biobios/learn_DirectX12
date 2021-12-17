#pragma once
#include "RefferenceResolution.h"

#include "IRenderer3D.h"

namespace Mylma::GUI {
	/// <summary>
	/// 3D�E�B���h�E�ɃR���e���c��`�悷��
	/// </summary>
	class IWindow3DContent {
	public:
		virtual void update(Mylma::Graphics3D::IRenderer3DRef r) = 0;
	};

}