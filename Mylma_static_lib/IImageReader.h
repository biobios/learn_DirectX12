#pragma once
#include "RefferenceResolution.h"

#include <iostream>
#include "LoadedImage.h"

namespace Mylma::Graphics {
	class IImageReader {
	public:
		virtual LoadedImagePtr read(std::istream& input);
		virtual ~IImageReader() = 0;
	};
}