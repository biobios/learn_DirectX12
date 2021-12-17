#include "MyFrame.h"

#include "Color.h"

MyFrame::MyFrame() : Mylma::GUI::Window3D(TEXT("DX12ƒeƒXƒg"), (LONG)300, (LONG)300) {

}

void MyFrame::paint(Mylma::Graphics3D::IRenderer3DRef r) {
	r.setBackground(*Mylma::Graphics::Color::RED);
	r.clear();
}