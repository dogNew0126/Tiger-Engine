#pragma once

#include "DynamicLight.h"

namespace tiger {
	namespace graphics {

		struct DirectionalLight : public DynamicLight {

			DirectionalLight(const glm::vec3& amb, const glm::vec3& diff, const glm::vec3& spec, const glm::vec3& dir);

			virtual void setupUniforms(Shader& shader, int currentLightIndex) override;
			glm::vec3 direction;
		};

	}
}