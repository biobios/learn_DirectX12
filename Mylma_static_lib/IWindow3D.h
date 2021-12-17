#pragma once
#include "RefferenceResolution.h"

#include <cstdint>
#include "IWindow3DContent.h"
#include "IGraphics3D.h"
#include "IRenderer3D.h"


namespace Mylma::GUI {
	/// <summary>
	/// �E�B���h�E���Ǘ�����
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
		/// �K���T�u�N���X�ő�����Ă�������
		/// </summary>
		Mylma::Graphics3D::IGraphics3DPtr graphics = nullptr;
	private:
		Mylma::GUI::IWindow3DContentPtr content_ptr = nullptr;
	};

}