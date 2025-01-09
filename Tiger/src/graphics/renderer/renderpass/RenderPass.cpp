#include "pch.h"
#include "RenderPass.h"

namespace tiger {

	RenderPass::RenderPass(Scene3D* scene) : m_ActiveScene(scene) {
		m_GLCache = GLCache::getInstance();
	}

	RenderPass::~RenderPass() {}

}