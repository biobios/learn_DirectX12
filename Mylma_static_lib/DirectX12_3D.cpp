#include "DirectX12_3D.h"
#include <d3d12.h>
#include <dxgi1_6.h>

#include <iostream>


Mylma::Graphics3D::DirectX12_3D::DirectX12_3D() {
#ifdef _DEBUG
	ID3D12Debug* debugLayer = nullptr;
	auto _result = D3D12GetDebugInterface(IID_PPV_ARGS(&debugLayer));
	debugLayer->EnableDebugLayer();
	debugLayer->Release();
#endif
	
	D3D_FEATURE_LEVEL levels[] =
	{
		D3D_FEATURE_LEVEL_12_1,
		D3D_FEATURE_LEVEL_12_0,
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0,
	};

	D3D_FEATURE_LEVEL featureLevel;

	for (int i = 0; i < 4; i++) {
		if (D3D12CreateDevice(nullptr, levels[i], IID_PPV_ARGS(&device)) == S_OK) {
			featureLevel = levels[i];
			break;
		}
	}

	HRESULT result = device->CheckFeatureSupport(D3D12_FEATURE_ARCHITECTURE1, &architecture, sizeof(architecture));

#ifdef _DEBUG
	result = CreateDXGIFactory2(DXGI_CREATE_FACTORY_DEBUG, IID_PPV_ARGS(&dxgiFactory));
#else
	result = CreateDXGIFactory1(IID_PPV_ARGS(&dxgiFactory));
#endif

	//�R�}���h�L���[�̍쐬
	D3D12_COMMAND_QUEUE_DESC cmdQueueDesc = {};

	cmdQueueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE; //�^�C���A�E�g����
	cmdQueueDesc.NodeMask = 0; //�A�_�v�^����̎�
	cmdQueueDesc.Priority = D3D12_COMMAND_QUEUE_PRIORITY_NORMAL;
	cmdQueueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;//�R�}���h���X�g�Ɠ���

	result = device->CreateCommandQueue(&cmdQueueDesc, IID_PPV_ARGS(&cmdQueue));
	
	//�t�F���X�̍쐬
	result = device->CreateFence(fenceValue, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&fence));
	
	std::printf("initialized!\n");
}
/*
void Mylma::Graphics3D::DirectX12_3D::registerWindow(Mylma::GUI::Window3DRef window) {
	//�X���b�v�`�F�[���̍쐬
	DXGI_SWAP_CHAIN_DESC1 swapchainDesc = {};

	swapchainDesc.Width = window.getWidth();
	swapchainDesc.Height = window.getHeight();
	swapchainDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapchainDesc.Stereo = false; //3d�f�B�X�v���C�֌W
	swapchainDesc.SampleDesc.Count = 1;//�}���`�T���v���̎w��
	swapchainDesc.SampleDesc.Quality = 0;
	swapchainDesc.BufferUsage = DXGI_USAGE_BACK_BUFFER;
	swapchainDesc.BufferCount = 2; //�_�u���o�b�t�@�Ȃ�Q
	swapchainDesc.Scaling = DXGI_SCALING_STRETCH;//�o�b�N�o�b�t�@�A�L�k�\
	swapchainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;//�t���b�v�㑦�j��
	swapchainDesc.AlphaMode = DXGI_ALPHA_MODE_UNSPECIFIED;
	swapchainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;//�t���X�N���[���؂�ւ��\

	WindowRenderingStructure wrs = {};

	wrs.window = &window;

	HRESULT result = dxgiFactory->CreateSwapChainForHwnd(
		cmdQueue,
		window.getWindowHandle(),
		&swapchainDesc,
		nullptr,
		nullptr,
		(IDXGISwapChain1**)&wrs.swapchain
	);

	//�f�B�X�N���v�^�q�[�v���쐬����
	D3D12_DESCRIPTOR_HEAP_DESC heapDesc = {};

	heapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;//�����_�^�[�Q�b�g�r���[
	heapDesc.NodeMask = 0; //GPU�̎w��
	heapDesc.NumDescriptors = 2; // �\���̓��
	heapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;//�V�F�[�_������Q�Ƃ���K�v�����邩

	result = device->CreateDescriptorHeap(&heapDesc, IID_PPV_ARGS(&wrs.rtvHeaps));

	//�r���[���쐬���X���b�v�`�F�[���ƕR�Â���

	D3D12_CPU_DESCRIPTOR_HANDLE handle = wrs.rtvHeaps->GetCPUDescriptorHandleForHeapStart();

	for (int idx = 0; (UINT)idx < heapDesc.NumDescriptors; idx++)
	{
		result = wrs.swapchain->GetBuffer(idx, IID_PPV_ARGS(&wrs.sc_backBuffers[idx]));

		device->CreateRenderTargetView(wrs.sc_backBuffers[idx], nullptr, handle);

		handle.ptr += device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
	}

	renderers.insert(new Mylma::Graphics3D::DX12Renderer3D(this, &window, cmdAllocator, wrs.swapchain, cmdList, cmdQueue));
}
*/
/*
Mylma::GUI::IWindow3DRef Mylma::Graphics3D::DirectX12_3D::createWindow(const std::wstring* window_name, int32_t width, int32_t height) {
	DirectX12_3DRef g_ref = *this;
	Mylma::GUI::DX12Window3DRef window = *(new Mylma::GUI::DX12Window3D(window_name, width, height, g_ref));

	//�X���b�v�`�F�[���̍쐬
	DXGI_SWAP_CHAIN_DESC1 swapchainDesc = {};

	swapchainDesc.Width = static_cast<uint32_t>(window.getWidth());
	swapchainDesc.Height = static_cast<uint32_t>(window.getHeight());
	swapchainDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapchainDesc.Stereo = false; //3d�f�B�X�v���C�֌W
	swapchainDesc.SampleDesc.Count = 1;//�}���`�T���v���̎w��
	swapchainDesc.SampleDesc.Quality = 0;
	swapchainDesc.BufferUsage = DXGI_USAGE_BACK_BUFFER;
	swapchainDesc.BufferCount = 2; //�_�u���o�b�t�@�Ȃ�Q
	swapchainDesc.Scaling = DXGI_SCALING_STRETCH;//�o�b�N�o�b�t�@�A�L�k�\
	swapchainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;//�t���b�v�㑦�j��
	swapchainDesc.AlphaMode = DXGI_ALPHA_MODE_UNSPECIFIED;
	swapchainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;//�t���X�N���[���؂�ւ��\

	IDXGISwapChain4* swapchain = nullptr;
	ID3D12DescriptorHeap* rtvHeaps = nullptr;

	HRESULT result = dxgiFactory->CreateSwapChainForHwnd(
		cmdQueue,
		window.getWindowHandle(),
		&swapchainDesc,
		nullptr,
		nullptr,
		(IDXGISwapChain1**)&swapchain
	);

	//�f�B�X�N���v�^�q�[�v���쐬����
	D3D12_DESCRIPTOR_HEAP_DESC heapDesc = {};

	heapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;//�����_�^�[�Q�b�g�r���[
	heapDesc.NodeMask = 0; //GPU�̎w��
	heapDesc.NumDescriptors = 2; // �\���̓��
	heapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;//�V�F�[�_������Q�Ƃ���K�v�����邩

	result = device->CreateDescriptorHeap(&heapDesc, IID_PPV_ARGS(&rtvHeaps));

	//�r���[���쐬���X���b�v�`�F�[���ƕR�Â���

	D3D12_CPU_DESCRIPTOR_HANDLE handle = rtvHeaps->GetCPUDescriptorHandleForHeapStart();

	std::array<ID3D12Resource*, 2> sc_backBuffers = {nullptr,nullptr};

	for (uint32_t idx = 0; idx < heapDesc.NumDescriptors; idx++)
	{
		result = swapchain->GetBuffer(idx, IID_PPV_ARGS(&sc_backBuffers[idx]));

		device->CreateRenderTargetView(sc_backBuffers[idx], nullptr, handle);

		handle.ptr += device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
	}

	renderers.insert(new Mylma::Graphics3D::DX12Renderer3D(this, &window, cmdAllocator, swapchain, cmdList, cmdQueue, rtvHeaps, device, sc_backBuffers));
	return window;
}
*/
/*
Mylma::Graphics3D::DirectX12_3D::renderer_t* Mylma::Graphics3D::DirectX12_3D::createRendererForHwnd(HWND hwnd, LONG width, LONG height)
{
	DirectX12_3DRef g_ref = *this;

	//�X���b�v�`�F�[���̍쐬
	DXGI_SWAP_CHAIN_DESC1 swapchainDesc = {};

	swapchainDesc.Width = static_cast<uint32_t>(width);
	swapchainDesc.Height = static_cast<uint32_t>(height);
	swapchainDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapchainDesc.Stereo = false; //3d�f�B�X�v���C�֌W
	swapchainDesc.SampleDesc.Count = 1;//�}���`�T���v���̎w��
	swapchainDesc.SampleDesc.Quality = 0;
	swapchainDesc.BufferUsage = DXGI_USAGE_BACK_BUFFER;
	swapchainDesc.BufferCount = 2; //�_�u���o�b�t�@�Ȃ�Q
	swapchainDesc.Scaling = DXGI_SCALING_STRETCH;//�o�b�N�o�b�t�@�A�L�k�\
	swapchainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;//�t���b�v�㑦�j��
	swapchainDesc.AlphaMode = DXGI_ALPHA_MODE_UNSPECIFIED;
	swapchainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;//�t���X�N���[���؂�ւ��\

	IDXGISwapChain4* swapchain = nullptr;
	ID3D12DescriptorHeap* rtvHeaps = nullptr;

	HRESULT result = dxgiFactory->CreateSwapChainForHwnd(
		cmdQueue,
		hwnd,
		&swapchainDesc,
		nullptr,
		nullptr,
		(IDXGISwapChain1**)&swapchain
	);

	//�f�B�X�N���v�^�q�[�v���쐬����
	D3D12_DESCRIPTOR_HEAP_DESC heapDesc = {};

	heapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;//�����_�^�[�Q�b�g�r���[
	heapDesc.NodeMask = 0; //GPU�̎w��
	heapDesc.NumDescriptors = 2; // �\���̓��
	heapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;//�V�F�[�_������Q�Ƃ���K�v�����邩

	result = device->CreateDescriptorHeap(&heapDesc, IID_PPV_ARGS(&rtvHeaps));

	//�r���[���쐬���X���b�v�`�F�[���ƕR�Â���

	D3D12_CPU_DESCRIPTOR_HANDLE handle = rtvHeaps->GetCPUDescriptorHandleForHeapStart();

	std::array<ID3D12Resource*, 2> sc_backBuffers = { nullptr,nullptr };

	for (uint32_t idx = 0; idx < heapDesc.NumDescriptors; idx++)
	{
		result = swapchain->GetBuffer(idx, IID_PPV_ARGS(&sc_backBuffers[idx]));

		device->CreateRenderTargetView(sc_backBuffers[idx], nullptr, handle);

		handle.ptr += device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
	}

	return new Mylma::Graphics3D::DX12Renderer3D(this, swapchain, rtvHeaps, sc_backBuffers, device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV));
}
*/

Mylma::Graphics3D::DirectX12_3D::CommandList::CommandList(DirectX12_3D* dx12)
{
	HRESULT result = dx12->device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&cmdAllocator));
	result = dx12->device->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, cmdAllocator, nullptr, IID_PPV_ARGS(&cmdList));
	state = State::READY_TO_WRITE;
}

void Mylma::Graphics3D::DirectX12_3D::CommandList::reset()
{
	if (state == State::EXECUTING) throw std::runtime_error("CommandList is executing.");
	cmdAllocator->Reset();
	cmdList->Reset(cmdAllocator, nullptr);

	state = State::READY_TO_WRITE;
}

void Mylma::Graphics3D::DirectX12_3D::CommandList::close()
{
	if (state != State::READY_TO_WRITE) throw std::runtime_error("CommandList is not ready to write.");

	cmdList->Close();
	state = State::CLOSED;
}

void Mylma::Graphics3D::DirectX12_3D::CommandList::execute(DirectX12_3D* dx12)
{
	if (state != State::CLOSED) throw std::runtime_error("CommandList is not closed.");

	ID3D12CommandList* lists[] = { cmdList };
	dx12->cmdQueue->ExecuteCommandLists(1, lists);

	dx12->fenceValue++;
	fenceValue = dx12->fenceValue;
	dx12->cmdQueue->Signal(dx12->fence, fenceValue);

	state = State::EXECUTING;
}

void Mylma::Graphics3D::DirectX12_3D::CommandList::waitForCompletion(DirectX12_3D* dx12)
{
	if (state != State::EXECUTING) return;

	if(dx12->fence->GetCompletedValue() < fenceValue)
	{
		auto event = CreateEvent(nullptr, false, false, nullptr);
		dx12->fence->SetEventOnCompletion(fenceValue, event);
		WaitForSingleObject(event, INFINITE);
		CloseHandle(event);
	}

	state = State::EXECUTED;

}

void Mylma::Graphics3D::DirectX12_3D::CommandList::setResourceBarrier(UINT barrierNum, const D3D12_RESOURCE_BARRIER* brs)
{
	cmdList->ResourceBarrier(barrierNum, brs);
}

void Mylma::Graphics3D::DirectX12_3D::CommandList::OMSetRenderTargets(UINT numRTVs, const D3D12_CPU_DESCRIPTOR_HANDLE* rtvs, BOOL RTsSingleHandleToDescriptorRange, const D3D12_CPU_DESCRIPTOR_HANDLE* dsv)
{
	cmdList->OMSetRenderTargets(numRTVs, rtvs, RTsSingleHandleToDescriptorRange, dsv);
}

void Mylma::Graphics3D::DirectX12_3D::CommandList::ClearRenderTargetView(const D3D12_CPU_DESCRIPTOR_HANDLE& rtv, const FLOAT colorRGBA[4], UINT numRects, const D3D12_RECT* rects)
{
	cmdList->ClearRenderTargetView(rtv, colorRGBA, numRects, rects);
}

Mylma::Graphics3D::DirectX12_3D::CommandList::~CommandList()
{
}

Mylma::Graphics3D::DirectX12_3D::SwapChainRenderer::SwapChainRenderer(DirectX12_3D* dx12, HWND hwnd, LONG width, LONG height)
{
	DirectX12_3DRef g_ref = *dx12;

	//�X���b�v�`�F�[���̍쐬
	DXGI_SWAP_CHAIN_DESC1 swapchainDesc = {};

	swapchainDesc.Width = static_cast<uint32_t>(width);
	swapchainDesc.Height = static_cast<uint32_t>(height);
	swapchainDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapchainDesc.Stereo = false; //3d�f�B�X�v���C�֌W
	swapchainDesc.SampleDesc.Count = 1;//�}���`�T���v���̎w��
	swapchainDesc.SampleDesc.Quality = 0;
	swapchainDesc.BufferUsage = DXGI_USAGE_BACK_BUFFER;
	swapchainDesc.BufferCount = 2; //�_�u���o�b�t�@�Ȃ�Q
	swapchainDesc.Scaling = DXGI_SCALING_STRETCH;//�o�b�N�o�b�t�@�A�L�k�\
	swapchainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;//�t���b�v�㑦�j��
	swapchainDesc.AlphaMode = DXGI_ALPHA_MODE_UNSPECIFIED;
	swapchainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;//�t���X�N���[���؂�ւ��\

	IDXGISwapChain4* swapchain = nullptr;
	ID3D12DescriptorHeap* rtvHeaps = nullptr;

	HRESULT result = dx12->dxgiFactory->CreateSwapChainForHwnd(
		dx12->cmdQueue,
		hwnd,
		&swapchainDesc,
		nullptr,
		nullptr,
		(IDXGISwapChain1**)&swapchain
	);

	//�f�B�X�N���v�^�q�[�v���쐬����
	D3D12_DESCRIPTOR_HEAP_DESC heapDesc = {};

	heapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;//�����_�^�[�Q�b�g�r���[
	heapDesc.NodeMask = 0; //GPU�̎w��
	heapDesc.NumDescriptors = 2; // �\���̓��
	heapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;//�V�F�[�_������Q�Ƃ���K�v�����邩

	result = dx12->device->CreateDescriptorHeap(&heapDesc, IID_PPV_ARGS(&rtvHeaps));

	//�r���[���쐬���X���b�v�`�F�[���ƕR�Â���

	D3D12_CPU_DESCRIPTOR_HANDLE handle = rtvHeaps->GetCPUDescriptorHandleForHeapStart();

	std::array<ID3D12Resource*, 2> sc_backBuffers = { nullptr,nullptr };

	for (uint32_t idx = 0; idx < heapDesc.NumDescriptors; idx++)
	{
		result = swapchain->GetBuffer(idx, IID_PPV_ARGS(&sc_backBuffers[idx]));

		dx12->device->CreateRenderTargetView(sc_backBuffers[idx], nullptr, handle);

		handle.ptr += dx12->device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
	}

	this->dx12 = dx12;
	this->swapChain = swapchain;
	this->rtvHeaps = rtvHeaps;
	this->sc_backBuffers = sc_backBuffers;
	this->cmdList = new CommandList(dx12);
	this->rtvDescriptorSize = dx12->device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);

	UINT bbIdx = swapChain->GetCurrentBackBufferIndex();

	current_rtv_handle = rtvHeaps->GetCPUDescriptorHandleForHeapStart();

	current_rtv_handle.ptr += bbIdx * rtvDescriptorSize;

	bb_resrc_barr.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
	bb_resrc_barr.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
	bb_resrc_barr.Transition.pResource = sc_backBuffers[bbIdx];
	bb_resrc_barr.Transition.Subresource = 0;
	bb_resrc_barr.Transition.StateBefore = D3D12_RESOURCE_STATE_PRESENT;
	bb_resrc_barr.Transition.StateAfter = D3D12_RESOURCE_STATE_RENDER_TARGET;

	cmdList->setResourceBarrier(1, &bb_resrc_barr);
	cmdList->OMSetRenderTargets(1, &current_rtv_handle, true, nullptr);

}

void Mylma::Graphics3D::DirectX12_3D::SwapChainRenderer::clear()
{
	cmdList->ClearRenderTargetView(current_rtv_handle, color, 0, nullptr);
}

void Mylma::Graphics3D::DirectX12_3D::SwapChainRenderer::startFrame()
{
	cmdList->waitForCompletion(dx12);
	cmdList->reset();

	UINT bbIdx = swapChain->GetCurrentBackBufferIndex();

	current_rtv_handle = rtvHeaps->GetCPUDescriptorHandleForHeapStart();

	current_rtv_handle.ptr += bbIdx * rtvDescriptorSize;

	bb_resrc_barr.Transition.pResource = sc_backBuffers[bbIdx];
	bb_resrc_barr.Transition.StateBefore = D3D12_RESOURCE_STATE_PRESENT;
	bb_resrc_barr.Transition.StateAfter = D3D12_RESOURCE_STATE_RENDER_TARGET;

	cmdList->setResourceBarrier(1, &bb_resrc_barr);
	cmdList->OMSetRenderTargets(1, &current_rtv_handle, true, nullptr);


}

void Mylma::Graphics3D::DirectX12_3D::SwapChainRenderer::endFrame()
{
	bb_resrc_barr.Transition.StateBefore = D3D12_RESOURCE_STATE_RENDER_TARGET;
	bb_resrc_barr.Transition.StateAfter = D3D12_RESOURCE_STATE_PRESENT;

	cmdList->setResourceBarrier(1, &bb_resrc_barr);
	cmdList->close();
	cmdList->execute(dx12);

	swapChain->Present(1, 0);
}

void Mylma::Graphics3D::DirectX12_3D::SwapChainRenderer::setBackground(Mylma::Graphics::ColorRef color)
{
	auto c = color.getValue();

	for(int i = 0; i < 4; i++)
	{
		this->color[i] = c[i];
	}
}

void Mylma::Graphics3D::DirectX12_3D::SwapChainRenderer::setColor(Mylma::Graphics::ColorRef color)
{
	auto c = color.getValue();

	for (int i = 0; i < 4; i++)
	{
		this->color[i] = c[i];
	}
}
