#pragma once
#include "RefferenceResolution.h"

#include "IRenderer3D.h"

namespace Mylma::GUI {
	/// <summary>
	/// 3Dウィンドウにコンテンツを描画する
	/// </summary>
	class IWindow3DContent {
	public:
		virtual void update(Mylma::Graphics3D::IRenderer3DRef r) = 0;
	};

}