#pragma once
#include "RefferenceResolution.h"
#include "includingDirectX12.h"

#include "DX12Renderer3D.h"

#include <unordered_set>
#include <array>

namespace Mylma::Graphics3D {
	class DirectX12_3D {
	public:
		using renderer_t = DX12Renderer3D;
		DirectX12_3D();
		renderer_t* createRendererForHwnd(HWND hwnd, LONG width, LONG height);
	private:
		ID3D12Device* device = nullptr;
		IDXGIFactory6* dxgiFactory = nullptr;
		D3D12_FEATURE_DATA_ARCHITECTURE1 architecture = {};
		ID3D12CommandAllocator* cmdAllocator = nullptr;
		ID3D12GraphicsCommandList* cmdList = nullptr;
		ID3D12CommandQueue* cmdQueue = nullptr;
		std::unordered_set<DX12Renderer3D*> renderers = std::unordered_set<DX12Renderer3D*>();
	};

}
