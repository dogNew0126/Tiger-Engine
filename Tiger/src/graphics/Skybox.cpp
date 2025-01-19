#include "pch.h"
#include "Skybox.h"
#include "utils/loaders/TextureLoader.h"
#include "utils/loaders/ShaderLoader.h"

namespace tiger {

	Skybox::Skybox(const std::vector<std::string>& filePaths) {

		m_SkyboxShader = ShaderLoader::loadShader("src/shaders/skybox.vert", "src/shaders/skybox.frag");
		CubemapSettings srgbCubemap;
		srgbCubemap.IsSRGB = true;
		m_SkyboxCubemap = TextureLoader::loadCubemapTexture(filePaths[0], filePaths[1], filePaths[2], filePaths[3], filePaths[4], filePaths[5], &srgbCubemap);

		m_GLCache = GLCache::getInstance();
	}

	void Skybox::Draw(ICamera* camera) {

		m_GLCache->switchShader(m_SkyboxShader);
		// Pass the texture to the shader
		m_SkyboxCubemap->bind(0);
		m_SkyboxShader->setUniform("skyboxCubemap", 0);

		m_SkyboxShader->setUniform("view", camera->getViewMatrix());
		m_SkyboxShader->setUniform("projection", camera->getProjectionMatrix());

		// Since the vertex shader is gonna make the depth value 1.0, and the default value in the depth buffer is 1.0 so this is needed to draw the skybox
		m_GLCache->setDepthTest(true);
		m_GLCache->setFaceCull(true);
		m_GLCache->setCullFace(GL_FRONT);
		m_GLCache->setDepthFunc(GL_LEQUAL);
		cube.draw();
		m_GLCache->setCullFace(GL_BACK);
		m_GLCache->setDepthFunc(GL_LESS);

		m_SkyboxCubemap->unbind();
	}

}