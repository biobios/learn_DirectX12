#include "DX12Renderer3D.h"
Mylma::Graphics3D::DX12Renderer3D::DX12Renderer3D(
	Mylma::Graphics3D::DirectX12_3D* dx12,
	Mylma::GUI::DX12Window3DPtr ptr,
	ID3D12CommandAllocator* calloc,
	IDXGISwapChain4* swapchain,
	ID3D12GraphicsCommandList* commandList,
	ID3D12CommandQueue* commandQue,
	ID3D12DescriptorHeap* rtvHeaps,
	ID3D12Device* device
) {
	this->dx12 = dx12;
	this->window_ptr = ptr;
	this->calloc = calloc;
	this->swapchain = swapchain;
	this->commandList = commandList;
	this->commandQue = commandQue;
	this->rtvHeaps = rtvHeaps;
	this->device = device;

	device->CreateFence(fenceVal, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&fence));

	calloc->Reset();

	UINT bbIdx = swapchain->GetCurrentBackBufferIndex();

	current_rtv_Handle = rtvHeaps->GetCPUDescriptorHandleForHeapStart();

	current_rtv_Handle.ptr += bbIdx * device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);

	commandList->OMSetRenderTargets(1, &current_rtv_Handle, true, nullptr);

	current_status = Status::READY;
}

void Mylma::Graphics3D::DX12Renderer3D::clear() {
	commandList->ClearRenderTargetView(current_rtv_Handle, background_color, 0, nullptr);
}

void Mylma::Graphics3D::DX12Renderer3D::execute() {
	commandList->Close();
	ID3D12CommandList* cmdlists[] = { commandList };
	commandQue->ExecuteCommandLists(1, cmdlists);
	swapchain->Present(1, 0);
	current_status = Status::EXECUTING;
}

void Mylma::Graphics3D::DX12Renderer3D::reset() {
	if (current_status == Status::EXECUTING) {
		commandQue->Signal(fence, ++fenceVal);
		if (fence->GetCompletedValue() != fenceVal) {
			auto e = CreateEvent(nullptr, false, false, nullptr);
			fence->SetEventOnCompletion(fenceVal, e);
			WaitForSingleObject(e, INFINITE);
			CloseHandle(e);
		}
		current_status = Status::NOT_READY;
	}
	if (current_status == Status::NOT_READY) {
		calloc->Reset();
		commandList->Reset(calloc, nullptr);

		UINT bbIdx = swapchain->GetCurrentBackBufferIndex();

		current_rtv_Handle = rtvHeaps->GetCPUDescriptorHandleForHeapStart();

		current_rtv_Handle.ptr += bbIdx * device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);

		commandList->OMSetRenderTargets(1, &current_rtv_Handle, true, nullptr);

		current_status = Status::READY;
	}
}

void Mylma::Graphics3D::DX12Renderer3D::setBackground(Mylma::Graphics::ColorRef c) {
	auto clr = c.getValue();
	for (int i = 0; i < 4; i++) {
		background_color[i] = clr[i];
	}
}

void Mylma::Graphics3D::DX12Renderer3D::setColor(Mylma::Graphics::ColorRef clr) {
	auto c = clr.getValue();
	for (int i = 0; i < 4; i++) {
		this->color[i] = c[i];
	}
}

bool Mylma::Graphics3D::DX12Renderer3D::isPair(Mylma::GUI::IWindow3DPtr ptr) {
	return window_ptr == ptr;
}