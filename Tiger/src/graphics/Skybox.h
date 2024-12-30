#pragma once

#include "Shader.h"
#include "camera/FPSCamera.h"

#include "platform/OpenGL/VertexArray.h"
#include "platform/OpenGL/IndexBuffer.h"
#include "platform/OpenGL/Buffer.h"
#include "graphics/renderer/GLCache.h"
#include "graphics/texture/Cubemap.h"

namespace tiger {

	class Skybox {

	public:
		Skybox(const std::vector<std::string>& filePaths);
		void Draw(ICamera* camera);

		inline Cubemap* getSkyboxCubemap() { return m_SkyboxCubemap; }

	private:

		Shader* m_SkyboxShader;
		GLCache* m_GLCache;

		VertexArray m_SkyboxVAO;
		IndexBuffer m_SkyboxIBO;
		Buffer  m_SkyboxVBO;
		Cubemap* m_SkyboxCubemap; // Cubemap texture

	};

}