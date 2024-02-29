#pragma once
#include "RefferenceResolution.h"
#include "includingDirectX12.h"

#include "IRenderer3D.h"

#include <unordered_set>
#include <array>
#include <mutex>

namespace Mylma::Graphics3D {
	class DirectX12_3D {
	public:
		class CommandList {
		public:
			CommandList(DirectX12_3D* dx12);
			void reset();
			void close();
            void execute(DirectX12_3D* dx12);
			void waitForCompletion(DirectX12_3D* dx12);
			void setResourceBarrier(UINT barrierNum, const D3D12_RESOURCE_BARRIER* brs);
			void OMSetRenderTargets(UINT numRTVs, const D3D12_CPU_DESCRIPTOR_HANDLE* rtvs, BOOL RTsSingleHandleToDescriptorRange, const D3D12_CPU_DESCRIPTOR_HANDLE* dsv);
			void ClearRenderTargetView(const D3D12_CPU_DESCRIPTOR_HANDLE& rtv, const FLOAT colorRGBA[4], UINT numRects, const D3D12_RECT* rects);
			~CommandList();
		private:
			enum class State {
				READY_TO_WRITE,
				CLOSED,
				EXECUTING,
				EXECUTED,
			};
			ID3D12CommandAllocator* cmdAllocator = nullptr;
			ID3D12GraphicsCommandList* cmdList = nullptr;
			State state = State::READY_TO_WRITE;
			UINT64 fenceValue = 0;
		};
		class SwapChainRenderer : public IRenderer3D {
		public:
			SwapChainRenderer(DirectX12_3D* dx12, HWND hwnd, LONG width, LONG height);
			void clear() override;
			void startFrame() override;
			void endFrame() override;
			void setBackground(Mylma::Graphics::ColorRef color) override;
			void setColor(Mylma::Graphics::ColorRef color) override;
		private:
			DirectX12_3D* dx12;
			IDXGISwapChain4* swapChain;
			ID3D12DescriptorHeap* rtvHeaps;
			std::array<ID3D12Resource*, 2> sc_backBuffers;
			D3D12_CPU_DESCRIPTOR_HANDLE current_rtv_handle;
			D3D12_RESOURCE_BARRIER bb_resrc_barr;
			UINT rtvDescriptorSize;
			CommandList* cmdList;
			float background[4];
			float color[4];
		};
		template <typename ResourceType>
		class MappableResource {
		private:
			bool isMapped = false;
			std::mutex mtx;
			DirectX12_3D* dx12;
			size_t size;
			bool testAndSetMapped(bool value);
		public:
			class MappedResource {
			private:
				bool isMapped = true;
				std::mutex mtx;
				MappableResource* resource;
				ResourceType* mappedData;
			public:
				MappedResource(MappableResource* resource);
				MappedResource(const MappedRexource&) = delete;
				MappedResource& operator=(const MappedResource&) = delete;
				MappedResource(MappedResource&&);
				MappedResource& operator=(MappedResource&&);
				ResourceType& operator[](size_t index);
				ResourceType& at(size_t index);
				void unmap();
				bool isMapped();
				~MappedResource();
			};
			MappableResource(DirectX12_3D* dx12, size_t size);
			bool isMapped();
		};
		using renderer_t = SwapChainRenderer;
		DirectX12_3D();
	private:
		ID3D12Device* device = nullptr;
		IDXGIFactory6* dxgiFactory = nullptr;
		D3D12_FEATURE_DATA_ARCHITECTURE1 architecture = {};
		ID3D12CommandQueue* cmdQueue = nullptr;
		ID3D12Fence* fence = nullptr;
		UINT64 fenceValue = 0;
		std::unordered_set<DX12Renderer3D*> renderers = std::unordered_set<DX12Renderer3D*>();
	};

	// Implementation of the template class MappableResource

	template <typename ResourceType>
	DirectX12_3D::MappableResource<ResourceType>::MappableResource(DirectX12_3D* dx12, size_t size) : dx12(dx12), size(size) 
	{
	
		D3D12_HEAP_PROPERTIES heapProp = {};
		heapProp.Type = D3D12_HEAP_TYPE_UPLOAD;
		heapProp.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
		heapProp.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
		heapProp.CreationNodeMask = 0;
		heapProp.VisibleNodeMask = 0;

		D3D12_RESOURCE_DESC resDesc = {};
		resDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
		resDesc.Alignment = 0;
		resDesc.Width = size * sizeof(ResourceType);
		resDesc.Height = 1;
		resDesc.DepthOrArraySize = 1;
		resDesc.MipLevels = 1;
		resDesc.Format = DXGI_FORMAT_UNKNOWN;
		resDesc.SampleDesc.Count = 1;
		resDesc.SampleDesc.Quality = 0;
		resDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
		resDesc.Flags = D3D12_RESOURCE_FLAG_NONE;

		ID3D12Resource* res = nullptr;
		HRESULT result = device->CreateCommittedResource(&heapProp, D3D12_HEAP_FLAG_NONE, &resDesc, D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&res));

		if (FAILED(result)) {
			throw std::runtime_error("Failed to create a committed resource for MappableResource");
		}
	}

	template <typename ResourceType>
	bool DirectX12_3D::MappableResource<ResourceType>::isMapped()
	{
		std::lock_guard<std::mutex> lock(mtx);
		return isMapped;
	}

	template <typename ResourceType>
	bool DirectX12_3D::MappableResource<ResourceType>::testAndSetMapped(bool value)
	{
		std::lock_guard<std::mutex> lock(mtx);
	
		bool oldValue = isMapped;
		isMapped = value;
		return oldValue;
	}
	// Implementation of the template class MappableResource::MappedResource

	template <typename ResourceType>
	DirectX12_3D::MappableResource<ResourceType>::MappedResource::MappedResource(MappableResource* resource) : resource(resource)
	{
		if (resource->testAndSetMapped(true)) {
			throw std::runtime_error("Resource is already mapped");
		}

		HRESULT result = resource->res->Map(0, nullptr, reinterpret_cast<void**>(&mappedData));
		
		if (FAILED(result)) {
			throw std::runtime_error("Failed to map the resource");
		}
	}

	template <typename ResourceType>
	DirectX12_3D::MappableResource<ResourceType>::MappedResource::MappedResource(MappableResource::MappedResource&& other) : resource(other.resource), mappedData(other.mappedData)
	{
		other.mappedData = nullptr;
		other.isMapped = false;
	}

	template <typename ResourceType>
	DirectX12_3D::MappableResource<ResourceType>::MappedResource& DirectX12_3D::MappableResource<ResourceType>::MappedResource::operator=(MappedResource&& other)
	{
		if (this != &other) {
			unmap();
			resource = other.resource;
			mappedData = other.mappedData;
			other.mappedData = nullptr;
			other.isMapped = false;
		}
		return *this;
	}

	template <typename ResourceType>
	ResourceType& DirectX12_3D::MappableResource<ResourceType>::MappedResource::operator[](size_t index)
	{
		return mappedData[index];
	}

	template <typename ResourceType>
	ResourceType& DirectX12_3D::MappableResource<ResourceType>::MappedResource::at(size_t index)
	{
		if (index >= resource->size) {
			throw std::out_of_range("Index out of range");
		}
		return mappedData[index];
	}

	template <typename ResourceType>
	void DirectX12_3D::MappableResource<ResourceType>::MappedResource::unmap()
	{
		bool oldIsMapped;
		{
			std::lock_guard<std::mutex> lock(mtx);
			oldIsMapped = isMapped;
			isMapped = false;
		}

		if (oldIsMapped) {
			resource->res->Unmap(0, nullptr);
			resource->testAndSetMapped(false);
		}
	}

	template <typename ResourceType>
	bool DirectX12_3D::MappableResource<ResourceType>::MappedResource::isMapped()
	{
		std::lock_guard<std::mutex> lock(mtx);
		return isMapped;
	}

	template <typename ResourceType>
	DirectX12_3D::MappableResource<ResourceType>::MappedResource::~MappedResource()
	{
		unmap();
	}
}
