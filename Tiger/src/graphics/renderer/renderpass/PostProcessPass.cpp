#include "pch.h"
#include "PostProcessPass.h"
#include "ui/DebugPane.h"
#include "utils/loaders/ShaderLoader.h"

namespace tiger
{

	PostProcessPass::PostProcessPass(Scene3D* scene) : RenderPass(scene), m_ScreenRenderTarget(Window::getWidth(), Window::getHeight(), false)
	{
		m_PostProcessShader = ShaderLoader::loadShader("src/shaders/postprocess.vert", "src/shaders/postprocess.frag");
		m_ScreenRenderTarget.addColorTexture(FloatingPoint16).addDepthStencilRBO(NormalizedDepthOnly).createFramebuffer();
		DebugPane::bindGammaCorrectionValue(&m_GammaCorrection);
	}

	PostProcessPass::~PostProcessPass() {}

	void PostProcessPass::executePostProcessPass(Framebuffer* framebufferToProcess) {
		glViewport(0, 0, Window::getWidth(), Window::getHeight());

		// If the input RenderTarget is multi-sampled. Resolve it by blitting it to a non-multi-sampled RenderTarget so we can post process it
		Framebuffer* target = framebufferToProcess;
		if (framebufferToProcess->isMultisampled()) {
			glBindFramebuffer(GL_READ_FRAMEBUFFER, framebufferToProcess->getFramebuffer());
			glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_ScreenRenderTarget.getFramebuffer());
			glBlitFramebuffer(0, 0, framebufferToProcess->getWidth(), framebufferToProcess->getHeight(), 0, 0, m_ScreenRenderTarget.getWidth(), m_ScreenRenderTarget.getHeight(), GL_COLOR_BUFFER_BIT, GL_NEAREST);
			target = &m_ScreenRenderTarget;
		}

#if DEBUG_ENABLED
		if (DebugPane::getWireframeMode())
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
#endif

		// Bind shader and its post processing settings, and also bind the screenspace texture
		target->unbind();
		GLCache::getInstance()->switchShader(m_PostProcessShader);
		m_PostProcessShader->setUniform1f("gamma_inverse", 1.0f / m_GammaCorrection);
		m_PostProcessShader->setUniform2f("read_offset", glm::vec2(1.0f / (float)target->getWidth(), 1.0f / (float)target->getHeight()));
		m_PostProcessShader->setUniform1i("blur_enabled", m_Blur);
		m_PostProcessShader->setUniform1i("screen_texture", 0);
		target->getColourTexture()->bind();

		Window::clear();
		ModelRenderer* modelRenderer = m_ActiveScene->getModelRenderer();
		modelRenderer->NDC_Plane.draw();
	}

}