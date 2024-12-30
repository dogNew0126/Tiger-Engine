#pragma once

#include "DynamicLight.h"

namespace tiger {

		struct DirectionalLight : public DynamicLight {

			DirectionalLight();
			DirectionalLight(const glm::vec3& lightColour, const glm::vec3& dir);

			virtual void setupUniforms(Shader& shader, int currentLightIndex) override;
			glm::vec3 direction;
		};

}