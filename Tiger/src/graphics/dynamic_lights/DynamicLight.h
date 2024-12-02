#pragma once

#include <glm/common.hpp>

#include "../Shader.h"

namespace tiger {
	namespace graphics {

		// TODO: Add functionality so it can update with an entitie's position and orientation
		struct DynamicLight {

			DynamicLight(const glm::vec3& amb, const glm::vec3& diff, const glm::vec3& spec);
			virtual void setupUniforms(Shader& shader, int currentLightIndex) = 0;

			glm::vec3 ambient, diffuse, specular;
			bool isActive;
		};

	}
}