#include "MyWindowContent.h"
#include <iostream>

MyWindowContent::MyWindowContent() {

}

void MyWindowContent::update(Mylma::Graphics3D::DirectX12_3D::renderer_t& r)
{
	r.setBackground(*Mylma::Graphics::Color::GREEN);
	r.clear();
	std::printf("paint");
}