#include "pch.h"
#include "SpotLight.h"

namespace tiger {

		SpotLight::SpotLight(const glm::vec3& lightColour, const glm::vec3& pos, const glm::vec3& dir, float cutOffAngle, float outerCutOffAngle)
			: Light(lightColour), m_Position(pos), m_Direction(dir), m_CutOff(cutOffAngle), m_OuterCutOff(outerCutOffAngle) {}

		void SpotLight::setupUniforms(Shader* shader, int currentLightIndex) {

			shader->setUniform3f(("spotLights[" + std::to_string(currentLightIndex) + "].position").c_str(), m_Position);
			shader->setUniform3f(("spotLights[" + std::to_string(currentLightIndex) + "].direction").c_str(), m_Direction);
			shader->setUniform3f(("spotLights[" + std::to_string(currentLightIndex) + "].lightColour").c_str(), m_LightColour);
			shader->setUniform1f(("spotLights[" + std::to_string(currentLightIndex) + "].cutOff").c_str(), m_CutOff);
			shader->setUniform1f(("spotLights[" + std::to_string(currentLightIndex) + "].outerCutOff").c_str(), m_OuterCutOff);

		}

}