#pragma once

#include "platform/OpenGL/Framebuffers/Framebuffer.h"

namespace tiger {

		enum RenderPassType {
			ShadowmapPassType,
			LightingPassType,
			PostProcessPassType,
			ProbePassType
		};

		struct ShadowmapPassOutput
		{
			glm::mat4 directionalLightViewProjMatrix;
			Framebuffer* shadowmapFramebuffer;
		};

		struct LightingPassOutput
		{
			Framebuffer* outputFramebuffer;
		};

}