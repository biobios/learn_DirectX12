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
	/// �摜�f�[�^��ێ����A����s�N�Z���`��(RGB,BGR��)�ŃA�N�Z�X�\�ɂ��܂��B
	/// �܂��摜�̃��^�f�[�^�ւ̃A�N�Z�X��񋟂��܂��B
	/// </summary>
	class Image {
		virtual uint32_t getWidth() = 0;
		virtual uint32_t getHeight() = 0;
		virtual PixelPtr getPixcel() = 0;
		virtual PixelPtr* getData() = 0;
	};
}