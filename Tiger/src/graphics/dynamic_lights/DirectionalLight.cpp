#include "DirectionalLight.h"

namespace tiger {
	namespace graphics {

		DirectionalLight::DirectionalLight(const glm::vec3& amb, const glm::vec3& diff, const glm::vec3& spec, const glm::vec3& dir)
			: DynamicLight(amb, diff, spec), direction(dir) {}

		// TODO: Add in multiple directional light support
		// TODO: Assert that the shader is bound in debug
		void DirectionalLight::setupUniforms(Shader& shader, int currentLightIndex) {
			if (isActive) {
				shader.setUniform3f("dirLight.ambient", ambient);
				shader.setUniform3f("dirLight.diffuse", diffuse);
				shader.setUniform3f("dirLight.specular", specular);
				shader.setUniform3f("dirLight.direction", direction);
			}
		}

	}
}