#include "pch.h"
#include "PointLight.h"

namespace tiger {

	PointLight::PointLight(float lightIntensity, const glm::vec3& lightColour, float attenuationRadius, const glm::vec3& pos)
		: Light(lightIntensity, lightColour), m_AttenuationRadius(attenuationRadius), m_Position(pos) {}

	void PointLight::setupUniforms(Shader* shader, int currentLightIndex) {
		shader->setUniform(("pointLights[" + std::to_string(currentLightIndex) + "].lightColour").c_str(), m_LightColour);
		shader->setUniform(("pointLights[" + std::to_string(currentLightIndex) + "].position").c_str(), m_Position);
	}
}