#pragma once
#include "RefferenceResolution.h"

#include <d3d12.h>
#include <dxgi1_6.h>
#include "IRenderer3D.h"
#include "DirectX12_3D.h"
#include "DX12Window3D.h"

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
			Mylma::GUI::DX12Window3DPtr ptr,
			ID3D12CommandAllocator* calloc,
			IDXGISwapChain4* swapchain,
			ID3D12GraphicsCommandList* commandList,
			ID3D12CommandQueue* commandQue,
			ID3D12DescriptorHeap* rtvHeaps,
			ID3D12Device* device
			);
		void clear() override;
		void execute() override;
		void reset() override;
		void setBackground(Mylma::Graphics::ColorRef color) override;
		void setColor(Mylma::Graphics::ColorRef color) override;

		bool isPair(Mylma::GUI::IWindow3DPtr ptr);
	private:
		float background_color[4] = {1.0F,1.0F,1.0F,1.0F};
		float color[4] = { 1.0F,1.0F,1.0F,1.0F };


		Status current_status;

		DirectX12_3D* dx12;
		Mylma::GUI::DX12Window3DPtr window_ptr;
		ID3D12CommandAllocator* calloc;
		IDXGISwapChain4* swapchain;
		ID3D12GraphicsCommandList* commandList;
		ID3D12CommandQueue* commandQue;
		ID3D12DescriptorHeap* rtvHeaps;
		ID3D12Device* device;
		D3D12_CPU_DESCRIPTOR_HANDLE current_rtv_Handle = {};
		ID3D12Fence* fence;
		UINT64 fenceVal = 0;
	};
}
