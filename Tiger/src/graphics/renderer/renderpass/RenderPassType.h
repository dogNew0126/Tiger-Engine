#pragma once

#include "platform/OpenGL/Framebuffers/Framebuffer.h"
#include "platform/OpenGL/Framebuffers/GBuffer.h"

namespace tiger {

		enum RenderPassType {
			MaterialRequired,
			NoMaterialRequired
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

		struct GeometryPassOutput {
			GBuffer* outputGBuffer;
		};

}