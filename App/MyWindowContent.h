#pragma once
#include "IWindow3DContent.h"
class MyWindowContent : public Mylma::GUI::IWindow3DContent
{
public:
	MyWindowContent();
	void update(Mylma::Graphics3D::IRenderer3DRef r) override;
};

