#include "MyWindowContent.h"
#include <iostream>

MyWindowContent::MyWindowContent() {

}

void MyWindowContent::update(Mylma::Graphics3D::IRenderer3DRef r) {
	r.setBackground(*Mylma::Graphics::Color::WHITE);
	r.clear();
	std::printf("paint");
}