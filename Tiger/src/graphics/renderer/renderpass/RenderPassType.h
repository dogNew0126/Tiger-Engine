#pragma once

#include "platform/OpenGL/Framebuffers/Framebuffer.h"

namespace tiger {

		enum RenderPassType {
			ShadowmapPassType,
			LightingPassType,
			PostProcessPassType
		};

		struct ShadowmapPassOutput
		{
			glm::mat4 directionalLightViewProjMatrix;
			unsigned int shadowmapTexture;
		};

		struct LightingPassOutput
		{
			Framebuffer* outputFramebuffer;
		};

}