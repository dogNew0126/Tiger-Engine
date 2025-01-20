#pragma once

#include "Light.h"

namespace tiger {

	class DynamicLightManager;

	class PointLight : public Light {
		friend DynamicLightManager;

	public:
		PointLight(float lightIntensity, const glm::vec3& lightColour, float attenuationRadius, const glm::vec3& pos);

		virtual void setupUniforms(Shader* shader, int currentLightIndex) override;

	private:
		float m_AttenuationRadius;
		glm::vec3 m_Position;
	};

}