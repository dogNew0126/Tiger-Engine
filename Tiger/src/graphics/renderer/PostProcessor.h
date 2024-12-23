#pragma once

#include <GL/glew.h>

namespace tiger {
	namespace graphics {

		class PostProcessor {
		public:
			PostProcessor();
		public:
			unsigned int texture;
			// Post Processing Toggles
			bool blur = false;
		};

	}
}