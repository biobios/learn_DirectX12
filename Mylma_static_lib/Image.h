#pragma once
#include "RefferenceResolution.h"
#include <DirectXMath.h>

namespace Mylma::Graphics {

	enum class ColorSpace {
		sRGB,
		linear,
	};

	enum class PixelFormat {
		RGBA_UINT8,
		RGBA_UINT16,
		RGBA_UINT32,
	};

	namespace Pixel {

		struct RGBA_UINT8 {
			uint8_t r;
			uint8_t g;
			uint8_t b;
			uint8_t a;
		};

		struct RGBA_UINT16 {
			uint16_t r;
			uint16_t g;
			uint16_t b;
			uint16_t a;
		};

		struct RGBA_UINT32 {
			uint32_t r;
			uint32_t g;
			uint32_t b;
			uint32_t a;
		};

		constexpr uint32_t getByteSize(PixelFormat pf) {
			uint32_t ret_num = 0;
			switch (pf)
			{
			case Mylma::Graphics::PixelFormat::RGBA_UINT8:
				ret_num = sizeof(RGBA_UINT8);
				break;
			case Mylma::Graphics::PixelFormat::RGBA_UINT16:
				ret_num = sizeof(RGBA_UINT16);
				break;
			case Mylma::Graphics::PixelFormat::RGBA_UINT32:
				ret_num = sizeof(RGBA_UINT32);
				break;
			default:
				break;
			}
			return ret_num;
		}
	}

	/// <summary>
	/// 抽象クラス
	/// 画像データへのアクセスを保持し、あるピクセル形式(RGB,BGR等)でアクセス可能にします。
	/// また画像のメタデータへのアクセスを提供します。
	/// </summary>
	class Image {
	public:
		virtual PixelFormat getPixelFormat() = 0;
		virtual ColorSpace getColorSpace() = 0;
		virtual uint32_t getWidth() = 0;
		virtual uint32_t getHeight() = 0;
		virtual uint32_t getPixelByteSize() = 0;
		virtual PixelPtr getPixel(uint32_t x, uint32_t y) = 0;
		virtual PixelPtr* getData() = 0;
		virtual ~Image() = 0;
	};
}