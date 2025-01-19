#include "pch.h"
#include "PointLight.h"

namespace tiger {

		PointLight::PointLight(const glm::vec3& lightColour, const glm::vec3& pos)
			: Light(lightColour), m_Position(pos) {}

		// TODO: Assert that the shader is bound in debug
		void PointLight::setupUniforms(Shader* shader, int currentLightIndex) {
			shader->setUniform(("pointLights[" + std::to_string(currentLightIndex) + "].lightColour").c_str(), m_LightColour);
			shader->setUniform(("pointLights[" + std::to_string(currentLightIndex) + "].position").c_str(), m_Position);
		}
}