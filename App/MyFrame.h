#pragma once
#include "Window3D.h"

class MyFrame : public Mylma::GUI::Window3D {
public:
	MyFrame();
	void paint(Mylma::Graphics3D::IRenderer3DRef r) override;
};