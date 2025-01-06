#pragma once
#include "graphics/renderer/renderpass/RenderPass.h"
#include "graphics/Shader.h"
#include "scene/Scene3D.h"

namespace tiger
{

	class ForwardLightingPass : public RenderPass
	{
	public:
		ForwardLightingPass(Scene3D* scene, bool shouldMultisample);
		ForwardLightingPass(Scene3D* scene, Framebuffer* customFramebuffer);
		virtual ~ForwardLightingPass() override;

		LightingPassOutput executeRenderPass(ShadowmapPassOutput& shadowmapData, ICamera* camera, bool renderOnlyStatic, bool useIBL);
	private:
		void bindShadowmap(Shader* shader, ShadowmapPassOutput& shadowmapData);

	private:
		bool m_AllocatedFramebuffer;
		Framebuffer* m_Framebuffer;
		Shader *m_ModelShader, *m_TerrainShader;
	};

}
