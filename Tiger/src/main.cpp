#include <iostream>
#include "graphics/Window.h"
#include "utils/Timer.h"
#include "graphics/Shader.h"
#include <stb_image.h>
#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "utils/Time.h"
#include "graphics/camera/Camera.h"
#include "utils/Logger.h"
#include "graphics/mesh/Model.h"
#include "terrain/Terrain.h"
#include "Scene3D.h"
#include "platform/OpenGL/Framebuffers/Framebuffer.h"
#include "graphics/mesh/common/Quad.h"
#include "graphics/renderer/GLCache.h"

#include <ft2build.h>
#include FT_FREETYPE_H
#include <freetype-gl.h>

int main() {
	// Prepare the game
	tiger::graphics::Camera camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f);
	tiger::graphics::Window window("Tiger Engine", WINDOW_X_RESOLUTION, WINDOW_Y_RESOLUTION);
	tiger::Scene3D scene(&camera);
	tiger::graphics::GLCache* glCache = tiger::graphics::GLCache::getInstance();
	tiger::utils::TextureLoader::initializeDefaultTextures();

	// Construct framebuffers
	tiger::opengl::Framebuffer framebuffer(window.getWidth(), window.getHeight());
	framebuffer.addColorAttachment(true).addDepthStencilRBO(true).createFramebuffer();

	tiger::opengl::Framebuffer blitFramebuffer(window.getWidth(), window.getHeight());
	blitFramebuffer.addColorAttachment(false).addDepthStencilRBO(false).createFramebuffer();

	// Instantiate the shaders and a screenspace quad
	tiger::graphics::Shader framebufferShader("src/shaders/postprocess.vert", "src/shaders/postprocess.frag");
	tiger::graphics::Quad screenQuad;
	screenQuad.getMaterial().setDiffuseMap(blitFramebuffer.getColourBufferTexture());
	// Setup post processing information
	glCache->switchShader(framebufferShader.getShaderID());
	framebufferShader.setUniform2f("readOffset", glm::vec2(1.0f / (float)window.getWidth(), 1.0f / (float)window.getHeight()));

	bool wireframeMode = false;

	// Debug timers
#if DEBUG_ENABLED
	tiger::Timer timer;
	float postProcessTime = 0.0f;
#endif

	tiger::Time deltaTime;

	while (!window.closed()) {

		deltaTime.update();

#if DEBUG_ENABLED
		if (wireframeMode)
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		else
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
#endif

		window.clear();

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		// Camera Update
		camera.processInput(deltaTime.getDeltaTime());

		// Draw the scene to our custom multisampled framebuffer
		framebuffer.bind();
		window.clear();

		scene.onUpdate(deltaTime.getDeltaTime());
		scene.onRender();

		// Blit the multisampled framebuffer over to a non-multisampled buffer and perform a post process pass on the default framebuffer
#if DEBUG_ENABLED
		glFinish();
		timer.reset();
#endif
		glBindFramebuffer(GL_READ_FRAMEBUFFER, framebuffer.getFramebuffer());
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, blitFramebuffer.getFramebuffer());
		glBlitFramebuffer(0, 0, window.getWidth(), window.getHeight(), 0, 0, window.getWidth(), window.getHeight(), GL_COLOR_BUFFER_BIT, GL_NEAREST);


#if DEBUG_ENABLED
		if (wireframeMode)
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
#endif

		framebuffer.unbind();
		window.clear();
		framebufferShader.enable();

		glCache->switchShader(framebufferShader.getShaderID());
		screenQuad.getMaterial().BindMaterialInformation(framebufferShader);
		screenQuad.draw();

#if DEBUG_ENABLED
		glFinish();
		postProcessTime = timer.elapsed();
#endif

		// Create an ImGui analytics window
		{
			ImGui::Begin("Runtime Analytics");
			ImGui::Text("Frametime: %.3f ms (FPS %.1f)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
#if DEBUG_ENABLED
			ImGui::Text("Post Process: %.6f ms", 1000.0f * postProcessTime);
#endif
			ImGui::End();

#if DEBUG_ENABLED
			ImGui::Begin("Debug Controls");
			ImGui::Text("Hit \"P\" to show/hide the cursor");
			ImGui::Checkbox("Wireframe Mode", &wireframeMode);
			ImGui::End();
#endif
		}
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		window.resetScroll();
		window.update();
	}

	return 0;
}
