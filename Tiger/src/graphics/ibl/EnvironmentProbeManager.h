#pragma once

#include "graphics/Shader.h"
#include "graphics/Skybox.h"
#include "graphics/ibl/EnvironmentProbe.h"

namespace tiger {

	enum EnvironmentProbeBlendSetting
	{
		PROBES_DISABLED, // Ignores probes and uses the skybox
		PROBES_SIMPLE, // Disables blending between probes
		PROBES_BLEND // Blends adjacent probes
	};

	class EnvironmentProbeManager {
	public:
		EnvironmentProbeManager(EnvironmentProbeBlendSetting sceneProbeBlendSetting);
		~EnvironmentProbeManager();

		void init(Skybox* skybox);

		void addProbe(EnvironmentProbe* probe);

		// Assumes shader is bound
		void bindProbe(const glm::vec3& renderPosition, Shader* shader);
	private:
		EnvironmentProbeBlendSetting m_ProbeBlendSetting;
		std::vector<EnvironmentProbe*> m_Probes;

		Skybox* m_Skybox;
	};

}