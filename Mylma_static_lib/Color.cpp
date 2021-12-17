#include "Color.h"

const Mylma::Graphics::ColorPtr Mylma::Graphics::Color::BLACK = new Mylma::Graphics::Color(0, 0, 0, 1);
const Mylma::Graphics::ColorPtr Mylma::Graphics::Color::RED = new Mylma::Graphics::Color(1, 0, 0, 1);
const Mylma::Graphics::ColorPtr Mylma::Graphics::Color::GREEN = new Mylma::Graphics::Color(0, 1, 0, 1);
const Mylma::Graphics::ColorPtr Mylma::Graphics::Color::BLUE = new Mylma::Graphics::Color(0, 0, 1, 1);
const Mylma::Graphics::ColorPtr Mylma::Graphics::Color::WHITE = new Mylma::Graphics::Color(1, 1, 1, 1);

Mylma::Graphics::Color::Color(const float* color) {
	for (int i = 0; i < 4; i++) {
		rgba[i] = color[i];
	}
}

Mylma::Graphics::Color::Color(float r, float g, float b, float a) {
	rgba[0] = r;
	rgba[1] = g;
	rgba[2] = b;
	rgba[3] = a;
}

const float* Mylma::Graphics::Color::getValue() {
	return rgba;
}
