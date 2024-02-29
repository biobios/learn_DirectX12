#pragma once
#include "RefferenceResolution.h"
#include "includingDirectX12.h"

#include <array>

#include "IRenderer3D.h"
#include "DirectX12_3D.h"

namespace {
	enum class Status {
		NOT_READY,
		READY,
		EXECUTING,
		EXECUTED,
	};
}

namespace Mylma::Graphics3D {

	class DX12Renderer3D : public IRenderer3D
	{
	public:
		DX12Renderer3D(
			DirectX12_3D* dx12,
			IDXGISwapChain4* swapchain,
			ID3D12DescriptorHeap* rtvHeaps,
			std::array<ID3D12Resource*, 2> sc_backBuffers,
			UINT rtvDescriptorSize
			);
		void clear() override;
		void startFrame() override;
		void endFrame() override;
		void setBackground(Mylma::Graphics::ColorRef color) override;
		void setColor(Mylma::Graphics::ColorRef color) override;

	private:
		float background_color[4] = {1.0F,1.0F,1.0F,1.0F};
		float color[4] = { 1.0F,1.0F,1.0F,1.0F };


		Status current_status;
		UINT rtvDescriptorSize;
		DirectX12_3D* dx12;
		DirectX12_3D::CommandList* cmdList;
		IDXGISwapChain4* swapchain;
		ID3D12DescriptorHeap* rtvHeaps;
		D3D12_CPU_DESCRIPTOR_HANDLE current_rtv_Handle = {};
		ID3D12Fence* fence;
		UINT64 fenceVal = 0;
		D3D12_RESOURCE_BARRIER bb_resrc_barr;
		std::array<ID3D12Resource*, 2> sc_backBuffers;
	};
}
