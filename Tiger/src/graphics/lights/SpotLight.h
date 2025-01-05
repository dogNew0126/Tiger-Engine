#pragma once

#include "Light.h"

namespace tiger {

	class DynamicLightManager;

	class SpotLight : public Light {
		friend class DynamicLightManager;

	public:
		SpotLight(const glm::vec3& lightColour, const glm::vec3& pos, const glm::vec3& dir, float cutOffAngle, float outerCutOffAngle);

		virtual void setupUniforms(Shader* shader, int currentLightIndex) override;

	private:
		glm::vec3 m_Position, m_Direction;
		float m_CutOff, m_OuterCutOff;
	};

}