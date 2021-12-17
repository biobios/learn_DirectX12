#pragma once
#include "RefferenceResolution.h"

namespace Mylma::Graphics {
	class Color
	{
	public:
		static const ColorPtr BLACK;
		static const ColorPtr RED;
		static const ColorPtr GREEN;
		static const ColorPtr BLUE;
		static const ColorPtr WHITE;
		Color(const float* color);
		Color(float r, float g, float b, float a);
		const float* getValue();
	private:
		float rgba[4];
	};

}
