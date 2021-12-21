#include "LoadedImage.h"
#include <cstdlib>
#include <cstdint>
#include <cstring>

Mylma::Graphics::LoadedImage::LoadedImage(uint32_t width, uint32_t height, PixelFormat _format, ColorSpace _colorSpace) {
	format = _format;
	colorSpace = _colorSpace;
	bytes_per_pixel = Mylma::Graphics::Pixel::getByteSize(_format);
	pixels_per_horizontal = width;
	pixels_per_vertical = height;

	data = std::malloc(pixels_per_horizontal * pixels_per_vertical * bytes_per_pixel);
	dataPtr_row = reinterpret_cast<PixelPtr*>(std::malloc(sizeof(PixelPtr) * pixels_per_vertical));
	
	dataPtr_row[0] = data;
	for (int i = 1; i < pixels_per_vertical; i++) {
		std::intptr_t ptr = reinterpret_cast<std::intptr_t>(dataPtr_row[i - 1]);
		dataPtr_row[i] = reinterpret_cast<PixelPtr>(ptr + pixels_per_horizontal * bytes_per_pixel);
	}
}

Mylma::Graphics::PixelFormat Mylma::Graphics::LoadedImage::getPixelFormat() {
	return format;
}

Mylma::Graphics::ColorSpace Mylma::Graphics::LoadedImage::getColorSpace() {
	return colorSpace;
}

uint32_t Mylma::Graphics::LoadedImage::getWidth() {
	return pixels_per_horizontal;
}

uint32_t Mylma::Graphics::LoadedImage::getHeight() {
	return pixels_per_vertical;
}

uint32_t Mylma::Graphics::LoadedImage::getPixelByteSize() {
	return bytes_per_pixel;
}

Mylma::Graphics::PixelPtr Mylma::Graphics::LoadedImage::getPixel(uint32_t x, uint32_t y) {
	if (x >= pixels_per_horizontal || y >= pixels_per_vertical) {
		//throw
	}

	std::intptr_t ptr = reinterpret_cast<std::intptr_t>(data);
	return reinterpret_cast<PixelPtr>(ptr + (y * pixels_per_vertical + x) * bytes_per_pixel);
}

Mylma::Graphics::PixelPtr* Mylma::Graphics::LoadedImage::getData() {
	return dataPtr_row;
}

void Mylma::Graphics::LoadedImage::writeRow(PixelPtr data, uint32_t row_index) {
	PixelPtr toPtr = getPixel(0, row_index);
	std::memcpy(toPtr, data, row_index * pixels_per_horizontal * bytes_per_pixel);
}

Mylma::Graphics::LoadedImage::~LoadedImage() {
	std::free(data);
	std::free(dataPtr_row);
}