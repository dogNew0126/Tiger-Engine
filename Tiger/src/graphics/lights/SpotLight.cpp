#include "pch.h"
#include "SpotLight.h"

namespace tiger {

		SpotLight::SpotLight(float lightIntensity, const glm::vec3& lightColour, float attenuationRadius, const glm::vec3& pos, const glm::vec3& dir, float cutOffAngle, float outerCutOffAngle)
			: Light(lightIntensity, lightColour), m_AttenuationRadius(attenuationRadius), m_Position(pos), m_Direction(dir), m_CutOff(cutOffAngle), m_OuterCutOff(outerCutOffAngle) {}

		void SpotLight::setupUniforms(Shader* shader, int currentLightIndex) {

			shader->setUniform(("spotLights[" + std::to_string(currentLightIndex) + "].position").c_str(), m_Position);
			shader->setUniform(("spotLights[" + std::to_string(currentLightIndex) + "].direction").c_str(), m_Direction);
			shader->setUniform(("spotLights[" + std::to_string(currentLightIndex) + "].intensity").c_str(), m_Intensity);
			shader->setUniform(("spotLights[" + std::to_string(currentLightIndex) + "].lightColour").c_str(), m_LightColour);
			shader->setUniform(("spotLights[" + std::to_string(currentLightIndex) + "].attenuationRadius").c_str(), m_AttenuationRadius);
			shader->setUniform(("spotLights[" + std::to_string(currentLightIndex) + "].cutOff").c_str(), m_CutOff);
			shader->setUniform(("spotLights[" + std::to_string(currentLightIndex) + "].outerCutOff").c_str(), m_OuterCutOff);

		}

}