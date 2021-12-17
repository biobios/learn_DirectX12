#pragma once
#include "RefferenceResolution.h"

#include <cstdint>
#include "IWindow3DContent.h"
#include "IGraphics3D.h"
#include "IRenderer3D.h"


namespace Mylma::GUI {
	/// <summary>
	/// ウィンドウを管理する
	/// </summary>
	class IWindow3D {
	public:
		virtual void setVisible(bool) = 0;
		virtual int32_t getWidth() = 0;
		virtual int32_t getHeight() = 0;
		void paint();
		void setContent(Mylma::GUI::IWindow3DContentPtr ptr);
	protected:
		/// <summary>
		/// 必ずサブクラスで代入してください
		/// </summary>
		Mylma::Graphics3D::IGraphics3DPtr graphics = nullptr;
	private:
		Mylma::GUI::IWindow3DContentPtr content_ptr = nullptr;
	};

}