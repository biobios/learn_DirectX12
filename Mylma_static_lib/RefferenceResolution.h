#pragma once

namespace Mylma {
	namespace GUI {
		template <typename T>
		class Window3D;
		template <typename T>
		using Window3DPtr = Window3D<T>*;
		template <typename T>
		using Window3DRef = Window3D<T>&;

		template <typename T>
		class Window3DContent;
		template <typename T>
		using Window3DContentPtr = Window3DContent<T>*;
		template <typename T>
		using Window3DContentRef = Window3DContent<T>&;

		class DX12Window3D;
		using DX12Window3DPtr = DX12Window3D*;
		using DX12Window3DRef = DX12Window3D&;
	}
	namespace Graphics {
		class Color;
		using ColorPtr = Color*;
		using ColorRef = Color&;

		using PixelPtr = void*;

		class Image;
		using ImagePtr = Image*;
		using ImageRef = Image&;

		class LoadedImage;
		using LoadedImagePtr = LoadedImage*;
		using LoadedImageRef = LoadedImage&;

		class IImageReader;
		using IImageReaderPtr = IImageReader*;
		using IImageReaderRef = IImageReader&;

		class CVImageReader;
		using CVImageReaderPtr = CVImageReader*;
		using CVImageReaderRef = CVImageReader&;
	}
	namespace Graphics3D {
		class DirectX12_3D;
		using DirectX12_3DPtr = DirectX12_3D*;
		using DirectX12_3DRef = DirectX12_3D&;

		class DX12Renderer3D;
		using DX12Renderer3DPtr = DX12Renderer3D*;
		using DX12Renderer3DRef = DX12Renderer3D&;

		class IGraphics3D;
		using IGraphics3DPtr = IGraphics3D*;
		using IGraphics3DRef = IGraphics3D&;

		class IRenderer3D;
		using IRenderer3DPtr = IRenderer3D*;
		using IRenderer3DRef = IRenderer3D&;

	}
}

namespace mylml {
	namespace windows {
		class Window;
		using WindowPtr = Window*;
		using WindowRef = Window&;
	}
}