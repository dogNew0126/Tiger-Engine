#pragma once

#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>
#include <iostream>
#include <vector>
#include "../../utils/Logger.h"

namespace tiger {
	namespace opengl {

		class Utility {
		public:
			static GLuint loadTextureFromFile(const char* path, bool containsTransparencyOnSides = false);

			static GLuint loadCubemapFromFiles(const std::vector<const char*>& vec);
		};

	}
}