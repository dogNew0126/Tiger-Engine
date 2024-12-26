#include "SpotLight.h"

namespace tiger {
	namespace graphics {

		SpotLight::SpotLight(const glm::vec3& lightColour, const glm::vec3& pos, const glm::vec3& dir, float cutOffAngle, float outerCutOffAngle)
			: DynamicLight(lightColour), position(pos), direction(dir), cutOff(cutOffAngle), outerCutOff(outerCutOffAngle) {}

		// TODO: Add in multiple spotlight support
		// TODO: Assert that the shader is bound in debug
		void SpotLight::setupUniforms(Shader& shader, int currentLightIndex) {
			if (isActive) {
				shader.setUniform3f("spotLight.lightColour", lightColour);
				shader.setUniform3f("spotLight.position", position);
				shader.setUniform3f("spotLight.direction", direction);
				shader.setUniform1f("spotLight.cutOff", cutOff);
				shader.setUniform1f("spotLight.outerCutOff", outerCutOff);
			}
		}

	}
}