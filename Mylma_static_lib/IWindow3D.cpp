#include "IWindow3D.h"


void Mylma::GUI::IWindow3D::paint() {
	Mylma::Graphics3D::IRenderer3DPtr renderer = graphics->getRenderer(*this);
	if (renderer == nullptr || content_ptr == nullptr) return;
	renderer->reset();
	content_ptr->update(*renderer);
	renderer->execute();
}

void Mylma::GUI::IWindow3D::setContent(Mylma::GUI::IWindow3DContentPtr ptr) {
	content_ptr = ptr;
}