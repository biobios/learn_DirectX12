#include "PNGImageReader.h"
#include "includingLibpng.h"
#include <iostream>

namespace {
	void __cdecl read_func(png_structp png, png_bytep data, size_t size) noexcept {
		std::istream& isp = *reinterpret_cast<std::istream*>(png_get_io_ptr(png));
		isp.read(reinterpret_cast<char*>(data), size);
	}
}

Mylma::Graphics::LoadedImagePtr Mylma::Graphics::PNGImageReader::read(std::istream& input) {
	constexpr uint32_t SIGNATURE_SIZE = 8;
	png_structp png = nullptr;
	png_infop info = nullptr;
	png_byte signature[8];

	uint32_t readSize;

	uint32_t width;
	uint32_t height;

	int bit_depth;
	int color_type;
	int interlace_type;

	readSize = input.readsome(reinterpret_cast<char*>(signature), SIGNATURE_SIZE);

	if (png_sig_cmp(signature, 0, 8) != 0) {//失敗なら
		//これはpngファイルじゃない
	}

	png = png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);

	if (png == nullptr) {
		//エラー
	}

	info = png_create_info_struct(png);

	if (info == nullptr) {
		//エラー
		png_destroy_read_struct(&png, nullptr, nullptr);
	}

	png_set_read_fn(png, &input, &read_func);

	png_set_sig_bytes(png, readSize);

	png_read_info(png, info);
	png_get_IHDR(png, info, &width, &height, &bit_depth, &color_type, &interlace_type, nullptr, nullptr);

	if (bit_depth == 16)
		png_set_strip_16(png);
	else if (bit_depth < 8)
		png_set_packing(png);

	if (color_type == PNG_COLOR_TYPE_PALETTE)
		png_set_palette_to_rgb(png);

	if (png_get_valid(png, info, PNG_INFO_tRNS) != 0)
		png_set_tRNS_to_alpha(png);

	if (color_type == PNG_COLOR_TYPE_RGB || color_type == PNG_COLOR_TYPE_GRAY)
		png_set_add_alpha(png, 0xffffffff,PNG_FILLER_AFTER);

	if (color_type == PNG_COLOR_TYPE_GRAY || color_type == PNG_COLOR_TYPE_GRAY_ALPHA)
		png_set_gray_to_rgb(png);

	double gamma;
	if (png_get_gAMA(png, info, &gamma))
		png_set_gamma(png, 1.0, gamma);

	png_read_update_info(png, info);

	LoadedImagePtr ret_image = new LoadedImage(width, height, PixelFormat::RGBA_UINT8, ColorSpace::linear);
	
	PixelPtr pixels_row = std::malloc(png_get_rowbytes(png, info));

	for (int y = 0; y < height; y++) {
		png_read_row(png, reinterpret_cast<png_bytep>(pixels_row), nullptr);
	}

	std::free(pixels_row);

	png_read_end(png, info);
	png_destroy_read_struct(&png, &info, nullptr);

	return ret_image;
}