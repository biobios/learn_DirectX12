#pragma once
#include "RefferenceResolution.h"

#include <cstdint>
#include <Windows.h>
#include "Window.h"
#include "DirectX12_3D.h"
#include "Window3DContent.h"

namespace Mylma::GUI {
	template <class T>
	class Window3D;

	template <>
	class Window3D<Mylma::Graphics3D::DirectX12_3D> : public mylml::windows::Window {
		using graphics_t = Mylma::Graphics3D::DirectX12_3D;
		graphics_t::renderer_t* renderer;
		Window3DContent<graphics_t>* content = nullptr;
	public:
		Window3D(const std::wstring& title, LONG width, LONG height, graphics_t& g) : mylml::windows::Window(title, width, height)
		{
			renderer = new graphics_t::renderer_t(&g, getHandle(), width, height);
		}
		void paint();
		void setContent(Window3DContent<graphics_t>* content);
		virtual ~Window3D()
		{
			delete content;
		}
	};

	inline void Window3D<Mylma::Graphics3D::DirectX12_3D>::paint()
	{
		if(content == nullptr) return;
		renderer->startFrame();
		content->update(*renderer);
		renderer->endFrame();
	}

	inline void Window3D<Mylma::Graphics3D::DirectX12_3D>::setContent(Window3DContent<graphics_t>* content)
	{
		this->content = content;
	}
}