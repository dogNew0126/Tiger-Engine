#include "pch.h"
#include "SpotLight.h"

namespace tiger {

		SpotLight::SpotLight(const glm::vec3& lightColour, const glm::vec3& pos, const glm::vec3& dir, float cutOffAngle, float outerCutOffAngle)
			: Light(lightColour), m_Position(pos), m_Direction(dir), m_CutOff(cutOffAngle), m_OuterCutOff(outerCutOffAngle) {}

		void SpotLight::setupUniforms(Shader* shader, int currentLightIndex) {

			shader->setUniform3f("spotLight.position", m_Position);
			shader->setUniform3f("spotLight.direction", m_Direction);
			shader->setUniform3f("spotLight.lightColour", m_LightColour);
			shader->setUniform1f("spotLight.cutOff", m_CutOff);
			shader->setUniform1f("spotLight.outerCutOff", m_OuterCutOff);

		}

}