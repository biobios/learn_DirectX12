#pragma once
#include "RefferenceResolution.h"
#include <DirectXMath.h>

namespace Mylma::Graphics {

	enum class ColorSpace {
		sRGB,
		linear,
	};

	enum class PixelFormat {
		RGBA_UINT16,
		RGBA_UINT32,
	};

	namespace PixelFormat {
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
	}

	/// <summary>
	/// 画像データを保持し、あるピクセル形式(RGB,BGR等)でアクセス可能にします。
	/// また画像のメタデータへのアクセスを提供します。
	/// </summary>
	class Image {
		virtual uint32_t getWidth() = 0;
		virtual uint32_t getHeight() = 0;
		virtual PixelPtr getPixcel() = 0;
		virtual PixelPtr* getData() = 0;
	};
}