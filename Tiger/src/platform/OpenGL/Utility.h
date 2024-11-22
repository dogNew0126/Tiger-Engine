#pragma once

#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>
#include <iostream>

namespace tiger {
	namespace opengl {

		class Utility {
		public:
			static GLuint loadTextureFromFile(const char* path);
		};

	}
}