#include "DX12Renderer3D.h"
Mylma::Graphics3D::DX12Renderer3D::DX12Renderer3D(
	Mylma::Graphics3D::DirectX12_3D* dx12,
	IDXGISwapChain4* swapchain,
	ID3D12DescriptorHeap* rtvHeaps,
	std::array<ID3D12Resource*, 2> backBuffers,
	UINT RTVDescriptorSize
) {
	this->dx12 = dx12;
	this->cmdList = new DirectX12_3D::CommandList(dx12);
	this->swapchain = swapchain;
	this->rtvHeaps = rtvHeaps;
	this->sc_backBuffers = backBuffers;
	this->rtvDescriptorSize = RTVDescriptorSize;

	UINT bbIdx = swapchain->GetCurrentBackBufferIndex();

	current_rtv_Handle = rtvHeaps->GetCPUDescriptorHandleForHeapStart();

	current_rtv_Handle.ptr += bbIdx * RTVDescriptorSize;

	bb_resrc_barr.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
	bb_resrc_barr.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
	bb_resrc_barr.Transition.pResource = sc_backBuffers[bbIdx];
	bb_resrc_barr.Transition.Subresource = 0;
	bb_resrc_barr.Transition.StateBefore = D3D12_RESOURCE_STATE_PRESENT;
	bb_resrc_barr.Transition.StateAfter = D3D12_RESOURCE_STATE_RENDER_TARGET;

	cmdList->setResourceBarrier(1, &bb_resrc_barr);
	cmdList->OMSetRenderTargets(1, &current_rtv_Handle, true, nullptr);

	current_status = Status::READY;
}

void Mylma::Graphics3D::DX12Renderer3D::clear() {
	cmdList->ClearRenderTargetView(current_rtv_Handle, background_color, 0, nullptr);
}

void Mylma::Graphics3D::DX12Renderer3D::endFrame() {
	
	bb_resrc_barr.Transition.StateBefore = D3D12_RESOURCE_STATE_RENDER_TARGET;
	bb_resrc_barr.Transition.StateAfter = D3D12_RESOURCE_STATE_PRESENT;
	cmdList->setResourceBarrier(1, &bb_resrc_barr);
	
	cmdList->close();
	cmdList->execute(dx12);

	swapchain->Present(1, 0);
	current_status = Status::EXECUTING;
}

void Mylma::Graphics3D::DX12Renderer3D::startFrame() {
	
	cmdList->waitForCompletion(dx12);

	if (current_status == Status::NOT_READY) {
		
		cmdList->reset();

		UINT bbIdx = swapchain->GetCurrentBackBufferIndex();

		current_rtv_Handle = rtvHeaps->GetCPUDescriptorHandleForHeapStart();

		current_rtv_Handle.ptr += bbIdx * rtvDescriptorSize;

		bb_resrc_barr.Transition.pResource = sc_backBuffers[bbIdx];
		bb_resrc_barr.Transition.StateBefore = D3D12_RESOURCE_STATE_PRESENT;
		bb_resrc_barr.Transition.StateAfter = D3D12_RESOURCE_STATE_RENDER_TARGET;

		cmdList->setResourceBarrier(1, &bb_resrc_barr);
		cmdList->OMSetRenderTargets(1, &current_rtv_Handle, true, nullptr);

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