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
#include "graphics/Model.h"
#include "terrain/Terrain.h"
#include "Scene3D.h"
#include "platform/OpenGL/Framebuffers/Framebuffer.h"
#include "graphics/MeshFactory.h"

#include <ft2build.h>
#include FT_FREETYPE_H
#include <freetype-gl.h>

int main() {
	// Prepare the game
	tiger::graphics::Camera camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f);
	tiger::graphics::Window window("Tiger Engine", WINDOW_X_RESOLUTION, WINDOW_Y_RESOLUTION);
	tiger::Scene3D scene(&camera, &window);

	// Construct framebuffers
	tiger::opengl::Framebuffer framebuffer(window.getWidth(), window.getHeight());
	framebuffer.addColorAttachment(true).addDepthStencilRBO(true).createFramebuffer();

	tiger::opengl::Framebuffer blitFramebuffer(window.getWidth(), window.getHeight());
	blitFramebuffer.addColorAttachment(false).addDepthStencilRBO(false).createFramebuffer();

	// Instantiate the shaders and mesh factories
	tiger::graphics::Shader framebufferShader("src/shaders/framebuffer.vert", "src/shaders/framebuffer.frag");
	tiger::graphics::MeshFactory meshFactory;
	tiger::graphics::Mesh* colourBufferMesh = meshFactory.CreateScreenQuad(blitFramebuffer.getColourBufferTexture());

	tiger::Timer fpsTimer;
	int frames = 0;

	framebufferShader.enable();
	framebufferShader.setUniform2f("readOffset", glm::vec2(1.0f / window.getWidth(), 1.0f / window.getHeight()));

	tiger::Time deltaTime;

	bool firstMove = true;

	GLfloat lastX = window.getMouseX();
	GLfloat lastY = window.getMouseY();

	while (!window.closed()) {
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		window.clear();
		deltaTime.update();

		// Check to see if the mouse hasn't been moved yet
		if (firstMove && (lastX != window.getMouseX() || lastY != window.getMouseY())) {
			lastX = window.getMouseX();
			lastY = window.getMouseY();
			firstMove = false;
		}

		// Camera Update
		camera.processMouseMovement(window.getMouseX() - lastX, lastY - window.getMouseY(), true);
		lastX = window.getMouseX();
		lastY = window.getMouseY();

		if (window.isKeyPressed(GLFW_KEY_W))
			camera.processKeyboard(tiger::graphics::FORWARD, deltaTime.getDeltaTime());
		if (window.isKeyPressed(GLFW_KEY_S))
			camera.processKeyboard(tiger::graphics::BACKWARD, deltaTime.getDeltaTime());
		if (window.isKeyPressed(GLFW_KEY_A))
			camera.processKeyboard(tiger::graphics::LEFT, deltaTime.getDeltaTime());
		if (window.isKeyPressed(GLFW_KEY_D))
			camera.processKeyboard(tiger::graphics::RIGHT, deltaTime.getDeltaTime());
		if (window.isKeyPressed(GLFW_KEY_SPACE))
			camera.processKeyboard(tiger::graphics::UPWARDS, deltaTime.getDeltaTime());
		if (window.isKeyPressed(GLFW_KEY_LEFT_CONTROL))
			camera.processKeyboard(tiger::graphics::DOWNWARDS, deltaTime.getDeltaTime());

		camera.processMouseScroll(window.getScrollY() * 6);
		window.resetScroll();

		// Draw the scene to our custom multisampled framebuffer
		framebuffer.bind();
		window.clear();

		scene.onUpdate(deltaTime.getDeltaTime());
		scene.onRender();

		// Blit the multisampled framebuffer over to a non-multisampled buffer
		glBindFramebuffer(GL_READ_FRAMEBUFFER, framebuffer.getFramebuffer());
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, blitFramebuffer.getFramebuffer());
		glBlitFramebuffer(0, 0, window.getWidth(), window.getHeight(), 0, 0, window.getWidth(), window.getHeight(), GL_COLOR_BUFFER_BIT, GL_NEAREST);

		// Draw to the default scene buffer
		framebuffer.unbind();
		window.clear();
		framebufferShader.enable();
		colourBufferMesh->Draw(framebufferShader);
		framebufferShader.disable();

		window.update();
		if (fpsTimer.elapsed() >= 1) {
			std::cout << "FPS: " << frames << "\n";
			std::cout << "AVG Frame Time: " << (1.0 / frames) * 1000.0 << "ms \n";
			frames = 0;
			fpsTimer.reset();
		}
		else {
			frames++;
		}
	}

	return 0;
}
