#pragma once

#include "graphics/texture/Cubemap.h"
#include "graphics/Shader.h"

namespace tiger {

	class EnvironmentProbe {

	public:
		EnvironmentProbe(glm::vec3& probePosition, glm::vec2& probeResolution, bool isStatic);

		void generate();

		// Assumes the shader is bound
		void bind(Shader& shader);

	private:
		Cubemap* m_IrradianceMap, * m_PrefilterMap, * m_BRDF_LUT;
		glm::vec3 m_Position;
		bool m_Generated;
		glm::vec2 m_ProbeResolution;
		bool m_IsStatic;
	};

}