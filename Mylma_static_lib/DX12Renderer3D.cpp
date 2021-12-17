#include "DX12Renderer3D.h"
Mylma::Graphics3D::DX12Renderer3D::DX12Renderer3D(
	Mylma::Graphics3D::DirectX12_3D* dx12,
	Mylma::GUI::Window3DPtr ptr,
	ID3D12CommandAllocator* calloc,
	IDXGISwapChain4* swapchain,
	ID3D12GraphicsCommandList* commandList,
	ID3D12CommandQueue* commandQue,
	ID3D12DescriptorHeap* rtvHeaps
) {
	this->dx12 = dx12;
	this->window_ptr = ptr;
	this->calloc = calloc;
	this->swapchain = swapchain;
	this->commandList = commandList;
	this->commandQue = commandQue;
	this->rtvHeaps = rtvHeaps;
}

void Mylma::Graphics3D::DX12Renderer3D::execute() {
	commandList->Close();
	ID3D12CommandList* cmdlists[] = { commandList };
	commandQue->ExecuteCommandLists(1, cmdlists);
	swapchain->Present(1, 0);
}

void Mylma::Graphics3D::DX12Renderer3D::reset() {
	if (current_status == Status::NOT_READY) {
		calloc->Reset();
		commandList->Reset(calloc, nullptr);

		UINT bbIdx = swapchain->GetCurrentBackBufferIndex();

		auto rtvH = rtvHeaps->GetCPUDescriptorHandleForHeapStart();

		rtvH.ptr += bbIdx * 

		current_status = Status::READY;
	}
}

void Mylma::Graphics3D::DX12Renderer3D::setBackground(Mylma::Graphics::ColorRef color) {
	auto c = color.getValue();
	for (int i = 0; i < 4; i++) {
		background_color[i] = c[i];
	}
}

void Mylma::Graphics3D::DX12Renderer3D::setColor(Mylma::Graphics::ColorRef color) {
	auto c = color.getValue();
	for (int i = 0; i < 4; i++) {
		this->color[i] = c[i];
	}
}

bool Mylma::Graphics3D::DX12Renderer3D::isPair(Mylma::GUI::Window3DPtr ptr) {
	return window_ptr == ptr;
}