#pragma once

#include "Light.h"

namespace tiger {

	class DynamicLightManager;

	class DirectionalLight : public Light {
		friend DynamicLightManager;

	public:
		DirectionalLight(float lightIntensity, const glm::vec3& lightColour, const glm::vec3& dir);

		virtual void setupUniforms(Shader* shader, int currentLightIndex) override;

	private:
		glm::vec3 m_Direction;
	};

}