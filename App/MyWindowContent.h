#pragma once
#include "DirectX12_3D.h"
#include "Window3DContent.h"
class MyWindowContent : public Mylma::GUI::Window3DContent<Mylma::Graphics3D::DirectX12_3D>
{
public:
	MyWindowContent();
	void update(Mylma::Graphics3D::DirectX12_3D::renderer_t& r) override;
};

