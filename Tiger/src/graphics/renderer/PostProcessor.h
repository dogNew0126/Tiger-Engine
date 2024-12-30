#pragma once

#include "graphics/mesh/common/Quad.h"
#include "MeshRenderer.h"
#include "graphics/Shader.h"
#include "platform/OpenGL/Framebuffers/Framebuffer.h"
#include "utils/Timer.h"

namespace tiger {

		class PostProcessor {
		public:
			PostProcessor(MeshRenderer* renderer);
			~PostProcessor();

			void preLightingPostProcess();
			// Assumes the input RenderTarget is bound, after function runs the default screen RenderTarget is bound
			void postLightingPostProcess(Framebuffer* input);

			// Might be useful to have if we want to have more custom post processing. Unity does it this way
			//void blit(Texture *texture, Framebuffer *source);

			inline void EnableBlur(bool choice) { m_Blur = choice; }
		private:

			float m_GammaCorrection = 2.2f;

			MeshRenderer* m_Renderer;
			Shader m_PostProcessShader;
			Quad m_NDC_Plane;
			Framebuffer m_ScreenRenderTarget;
			Timer m_Timer;

			bool m_Blur = false;
		};

}