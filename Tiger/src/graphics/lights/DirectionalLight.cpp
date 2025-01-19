#include "pch.h"
#include "DirectionalLight.h"

namespace tiger {

		DirectionalLight::DirectionalLight(const glm::vec3& lightColour, const glm::vec3& dir)
			: Light(lightColour), m_Direction(dir) {}

		void DirectionalLight::setupUniforms(Shader* shader, int currentLightIndex) {
			shader->setUniform(("dirLights[" + std::to_string(currentLightIndex) + "].direction").c_str(), m_Direction);
			shader->setUniform(("dirLights[" + std::to_string(currentLightIndex) + "].lightColour").c_str(), m_LightColour);
		}

}