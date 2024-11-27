#pragma once

#include <vector>
#include "Mesh.h"
#include "../platform/OpenGL/Utility.h"

namespace tiger {
	namespace graphics {

		class MeshFactory {
		public:
			Mesh* CreateQuad(const char* path, bool shouldHaveSpec = false);

			// Should be used to draw the framebuffer's colour buffer
			Mesh* CreateScreenQuad(int colourBufferId);
		};

	}
}