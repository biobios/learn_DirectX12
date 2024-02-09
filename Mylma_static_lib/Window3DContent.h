#pragma once
#include "RefferenceResolution.h"

namespace Mylma::GUI {
	template <typename T>
	class Window3DContent {
	public:
		virtual void update(T::renderer_t& renderer) = 0;
		virtual ~Window3DContent() {};
	};
}