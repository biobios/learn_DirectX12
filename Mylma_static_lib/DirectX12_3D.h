#pragma once
#include "RefferenceResolution.h"
#include "includingDirectX12.h"

#include "IGraphics3D.h"
#include "DX12Renderer3D.h"

#include <unordered_set>
#include <array>

namespace Mylma::Graphics3D {
	class DirectX12_3D : public IGraphics3D {
	public:
		static IGraphics3DPtr create();
		Mylma::Graphics3D::IRenderer3DPtr getRenderer(const Mylma::GUI::IWindow3DRef window) override;
		Mylma::GUI::IWindow3DRef createWindow(const std::wstring* window_name, int32_t width, int32_t height) override;
//		void registerWindow(Mylma::GUI::Window3DRef window) override;
//		void repaint(Mylma::GUI::Window3DRef window) override;
	private:
		DirectX12_3D();
		ID3D12Device* device = nullptr;
		IDXGIFactory6* dxgiFactory = nullptr;
		D3D12_FEATURE_DATA_ARCHITECTURE1 architecture = {};
		ID3D12CommandAllocator* cmdAllocator = nullptr;
		ID3D12GraphicsCommandList* cmdList = nullptr;
		ID3D12CommandQueue* cmdQueue = nullptr;
		std::unordered_set<DX12Renderer3D*> renderers = std::unordered_set<DX12Renderer3D*>();
	};

}
