#pragma once

#include "../Model.h"
#include "Renderable3D.h"
#include <deque>

namespace tiger {
	namespace graphics {

		class Renderer {
		public:
			void submit(Renderable3D* renderable);
			void flush(Shader& shader);

		private:

			std::deque<Renderable3D*> m_RenderQueue;

		};

	}
}