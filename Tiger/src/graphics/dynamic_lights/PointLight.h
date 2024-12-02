#pragma once

#include "DynamicLight.h"

#include <string>

namespace tiger {
	namespace graphics {

		struct PointLight : public DynamicLight {

		public:
			PointLight(const glm::vec3& amb, const glm::vec3& diff, const glm::vec3& spec, const glm::vec3& pos, float cons, float lin, float quad);

			virtual void setupUniforms(Shader& shader, int currentLightIndex) override;
			glm::vec3 position;
			float constant, linear, quadratic;
		};
	}
}