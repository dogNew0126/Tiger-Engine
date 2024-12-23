#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../../../Defs.h"
#include "../../../utils/Logger.h"

namespace tiger {
	namespace opengl {

		class Framebuffer {
		public:
			Framebuffer(int width, int height);
			~Framebuffer();

			void createFramebuffer();
			Framebuffer& addColorAttachment(bool multisampledBuffer);
			Framebuffer& addDepthStencilRBO(bool multisampledBuffer);

			void bind();
			void unbind();

			inline unsigned int getFramebuffer() const { return m_FBO; }
			inline unsigned int getColourBufferTexture() const { return m_ColourTexture; }
			inline unsigned int getDepthStencilBufferTexture() const { return m_DepthStencilRBO; }

		private:
			unsigned int m_FBO, m_ColourTexture, m_DepthStencilRBO;

			bool m_Created;

			unsigned int m_Width, m_Height;
		};

	}
}