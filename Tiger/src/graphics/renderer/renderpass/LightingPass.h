#pragma once
#include "graphics/renderer/renderpass/RenderPass.h"
#include "graphics/Shader.h"
#include "scene/Scene3D.h"

namespace tiger
{

	class LightingPass : public RenderPass
	{
	public:
		LightingPass(Scene3D* scene);
		LightingPass(Scene3D* scene, Framebuffer* customFramebuffer);
		virtual ~LightingPass() override;

		LightingPassOutput executeRenderPass(ShadowmapPassOutput& shadowmapData, ICamera* camera, bool useIBL);
	private:
		void bindShadowmap(Shader* shader, ShadowmapPassOutput& shadowmapData);

	private:
		bool m_AllocatedFramebuffer;
		Framebuffer* m_Framebuffer;
		Shader *m_ModelShader, *m_TerrainShader;
	};

}
