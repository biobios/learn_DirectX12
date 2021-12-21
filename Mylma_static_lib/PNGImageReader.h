#pragma once
#include "RefferenceResolution.h"

#include "IImageReader.h"
namespace Mylma::Graphics {
	class PNGImageReader : public IImageReader
	{
	public:
		LoadedImagePtr read(std::istream& input);
	};
}

