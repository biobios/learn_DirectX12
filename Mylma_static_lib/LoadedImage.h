#pragma once
#include "RefferenceResolution.h"
#include "Image.h"

namespace Mylma::Graphics {
    /// <summary>
    /// メモリ上に配置された書き換え可能なイメージクラスです。
    /// </summary>
    class LoadedImage : public Image {
	public:
		LoadedImage(uint32_t width, uint32_t height, PixelFormat format, ColorSpace colorSpace);
		PixelFormat getPixelFormat() override;
		ColorSpace getColorSpace() override;
		uint32_t getWidth() override;
		uint32_t getHeight() override;
		uint32_t getPixelByteSize() override;
		PixelPtr getPixel(uint32_t x, uint32_t y) override;
		PixelPtr* getData() override;
		void writeRow(PixelPtr data,uint32_t row_index);
		~LoadedImage() override;
	private:
		PixelFormat format;
		ColorSpace colorSpace;
		uint32_t bytes_per_pixel;
		PixelPtr data;
		PixelPtr* dataPtr_row;
		uint32_t pixels_per_horizontal;
		uint32_t pixels_per_vertical;
    };
}
