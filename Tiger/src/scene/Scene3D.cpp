#include "pch.h"
#include "Scene3D.h"

#include "graphics/mesh/Mesh.h"
#include "graphics/mesh/common/Cube.h"
#include "graphics/mesh/common/Sphere.h"
#include "graphics/mesh/common/Quad.h"

#include "graphics/renderer/renderpass/RenderPassType.h"

#include "utils/loaders/TextureLoader.h"

namespace tiger {

	Scene3D::Scene3D(Window* window)
		: m_SceneCamera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f), m_ModelRenderer(getCamera()), m_Terrain(glm::vec3(0.0f, -20.0f, 0.0f)), m_ProbeManager(m_SceneProbeBlendSetting)
	{
		m_GLCache = GLCache::getInstance();
		init();
	}

	Scene3D::~Scene3D() {

	}

	void Scene3D::init() {

		//// Load renderables
		//graphics::Quad windowPane;
		//windowPane.getMaterial().setDiffuseMap(utils::TextureLoader::load2DTexture(std::string("res/textures/window.png"), true));
		//windowPane.getMaterial().setSpecularMap(utils::TextureLoader::load2DTexture(std::string("res/textures/default/fullSpec.png"), false));
		//graphics::Model* glass = new graphics::Model(windowPane);

		//m_RenderableModels.push_back(new RenderableModel(glm::vec3(200.0f, 50.0f, 100.0f), glm::vec3(0.05f, 0.05f, 0.05f), glm::vec3(0.0f, 0.0f, 1.0f), glm::radians(0.0f), new tiger::Model("res/3D_Models/Sponza/sponza.obj"), nullptr, true, false));

		//m_RenderableModels.push_back(new RenderableModel(glm::vec3(40, 60, 40), glm::vec3(15, 15, 15), glm::vec3(0.0, 1.0, 0.0), glm::radians(180.0f), glass, nullptr, true, true));
		//m_RenderableModels.push_back(new RenderableModel(glm::vec3(80, 60, 80), glm::vec3(15, 15, 15), glm::vec3(0.0, 1.0, 0.0), glm::radians(180.0f), glass, nullptr, true, true));
		//m_RenderableModels.push_back(new RenderableModel(glm::vec3(120, 60, 120), glm::vec3(15, 15, 15), glm::vec3(0.0, 1.0, 0.0), glm::radians(180.0f), glass, nullptr, true, true));

		//m_RenderableModels.push_back(new RenderableModel(glm::vec3(20, 90, 20), glm::vec3(10, 10, 10), glm::vec3(1, 0, 0), 0, new Model(Cube()), nullptr, false, false));
		//m_RenderableModels.push_back(new RenderableModel(glm::vec3(140, 90, 140), glm::vec3(10, 10, 10), glm::vec3(1, 0, 0), 0, new Model(Sphere()), nullptr, false, false));
		//m_RenderableModels.push_back(new RenderableModel(glm::vec3(-20, 90, -20), glm::vec3(10, 10, 10), glm::vec3(1, 0, 0), 0, new Model(Quad()), nullptr, false, false));

		// Temp code until I rewrite the model loader
		//Model* helmet = new tiger::Model("res/3D_Models/DamagedHelmet/DamagedHelmet.gltf");
		//m_RenderableModels.push_back(new RenderableModel(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(6.0f, 6.0f, 6.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::radians(90.0f), helmet, nullptr, false, false));
		//helmet->getMeshes()[0].getMaterial().setMetallicMap(TextureLoader::getFullMetallic());

		TextureSettings srgbTextureSettings;
		srgbTextureSettings.IsSRGB = true;

		/*Model* window = new tiger::Model(Quad());
		m_RenderableModels.push_back(new RenderableModel(glm::vec3(150.0f, 60.0f, 150.0f), glm::vec3(25.0f, 25.0f, 25.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::radians(-90.0f), window, nullptr, true, false));
		window->getMeshes()[0].getMaterial().setAlbedoMap(TextureLoader::load2DTexture(std::string("res/textures/bricks2.jpg"), &srgbTextureSettings));
		window->getMeshes()[0].getMaterial().setNormalMap(TextureLoader::load2DTexture(std::string("res/textures/bricks2_normal.jpg")));
		window->getMeshes()[0].getMaterial().setRoughnessMap(TextureLoader::getWhiteTexture());
		window->getMeshes()[0].getMaterial().setDisplacementMap(TextureLoader::load2DTexture(std::string("res/textures/bricks2_disp.jpg")));

		Model* window2 = new tiger::Model(Quad());
		m_RenderableModels.push_back(new RenderableModel(glm::vec3(150.0f, 60.0f, 205.0f), glm::vec3(25.0f, 25.0f, 25.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::radians(-90.0f), window2, nullptr, true, true));
		window2->getMeshes()[0].getMaterial().setAlbedoMap(TextureLoader::load2DTexture(std::string("res/textures/Pebles_001_COLOR.png"), &srgbTextureSettings));
		window2->getMeshes()[0].getMaterial().setMetallicMap(TextureLoader::load2DTexture(std::string("res/textures/Pebles_001_SPEC.png")));
		window2->getMeshes()[0].getMaterial().setNormalMap(TextureLoader::load2DTexture(std::string("res/textures/Pebles_001_NRM.png")));
		window2->getMeshes()[0].getMaterial().setAmbientOcclusionMap(TextureLoader::load2DTexture(std::string("res/textures/Pebles_001_OCC.png")));
		window2->getMeshes()[0].getMaterial().setRoughnessMap(TextureLoader::getWhiteTexture());
		window2->getMeshes()[0].getMaterial().setDisplacementMap(TextureLoader::load2DTexture(std::string("res/textures/Pebles_Displace.png")));

		Model* tunnel = new tiger::Model(Cube());
		m_RenderableModels.push_back(new RenderableModel(glm::vec3(50.0f, 20.0f, 50.0f), glm::vec3(-100.0f, -10.0f, -10.0f), glm::vec3(0.0f, 1.0f, 0.0f), 0.0f, tunnel, nullptr, true, true));
		tunnel->getMeshes()[0].getMaterial().setAlbedoMap(TextureLoader::load2DTexture(std::string("res/textures/bricks2.jpg"), &srgbTextureSettings));
		tunnel->getMeshes()[0].getMaterial().setNormalMap(TextureLoader::load2DTexture(std::string("res/textures/bricks2_normal.jpg")));
		tunnel->getMeshes()[0].getMaterial().setRoughnessMap(TextureLoader::getWhiteTexture());*/

		Model* pbrGun = new tiger::Model("res/3D_Models/Cerberus_Gun/Cerberus_LP.FBX");
		m_RenderableModels.push_back(new RenderableModel(glm::vec3(815.0f, 150.0f, 1242.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::radians(-90.0f), pbrGun, nullptr, true, false));
		pbrGun->getMeshes()[0].getMaterial().setAlbedoMap(TextureLoader::load2DTexture(std::string("res/3D_Models/Cerberus_Gun/Textures/Cerberus_A.tga"), &srgbTextureSettings));
		pbrGun->getMeshes()[0].getMaterial().setNormalMap(TextureLoader::load2DTexture(std::string("res/3D_Models/Cerberus_Gun/Textures/Cerberus_N.tga")));
		pbrGun->getMeshes()[0].getMaterial().setMetallicMap(TextureLoader::load2DTexture(std::string("res/3D_Models/Cerberus_Gun/Textures/Cerberus_M.tga")));
		pbrGun->getMeshes()[0].getMaterial().setRoughnessMap(TextureLoader::load2DTexture(std::string("res/3D_Models/Cerberus_Gun/Textures/Cerberus_R.tga")));
		pbrGun->getMeshes()[0].getMaterial().setAmbientOcclusionMap(TextureLoader::load2DTexture(std::string("res/3D_Models/Cerberus_Gun/Textures/Cerberus_AO.tga")));

		m_RenderableModels.push_back(new RenderableModel(glm::vec3(946.9f, 165.5f, 859.0f), glm::vec3(100.0f, 100.0f, 100.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::radians(-90.0f), new Model(Cube()), nullptr, true, false));

		// Temp testing code
		//int nrRows = 1;
		//int nrColumns = 1;
		//float spacing = 2.5;
		//for (int row = 0; row < nrRows; row++) {
		//	for (int col = 0; col < nrColumns; col++) {
		//		Model* sphere = new tiger::Model("res/3D_Models/Sphere/globe-sphere.obj");
		//		Material& mat = sphere->getMeshes()[0].getMaterial();
		//		mat.setAlbedoMap(TextureLoader::getDefaultAO());
		//		mat.setNormalMap(TextureLoader::getDefaultNormal());
		//		mat.setAmbientOcclusionMap(TextureLoader::getDefaultAO());
		//		mat.setMetallicMap(TextureLoader::getFullMetallic());
		//		mat.setRoughnessMap(TextureLoader::getNoRoughness());
		//		m_RenderableModels.push_back(new RenderableModel(glm::vec3((float)(col - (nrColumns / 2)) * spacing + 60,
		//			(float)(row - (nrRows / 2)) * spacing + 90, 130.0f), glm::vec3(20.0f, 20.0f, 20.0f), glm::vec3(1.0f, 0.0f, 0.0f), 0.0f, sphere, nullptr, false, false));
		//	}
		//}

		Model* hyruleShield = new tiger::Model("res/3D_Models/Hyrule_Shield/HShield.obj");
		m_RenderableModels.push_back(new RenderableModel(glm::vec3(67.0f, 92.0f, 133.0f), glm::vec3(5.0f, 5.0f, 5.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::radians(180.0f), hyruleShield, nullptr, false, false));
		hyruleShield->getMeshes()[0].getMaterial().setAlbedoMap(TextureLoader::load2DTexture(std::string("res/3D_Models/Hyrule_Shield/HShield_[Albedo].tga"), &srgbTextureSettings));
		hyruleShield->getMeshes()[0].getMaterial().setNormalMap(TextureLoader::load2DTexture(std::string("res/3D_Models/Hyrule_Shield/HShield_[Normal].tga")));
		hyruleShield->getMeshes()[0].getMaterial().setMetallicMap(TextureLoader::load2DTexture(std::string("res/3D_Models/Hyrule_Shield/HShield_[Metallic].tga")));
		hyruleShield->getMeshes()[0].getMaterial().setRoughnessMap(TextureLoader::load2DTexture(std::string("res/3D_Models/Hyrule_Shield/HShield_[Roughness].tga")));
		hyruleShield->getMeshes()[0].getMaterial().setAmbientOcclusionMap(TextureLoader::load2DTexture(std::string("res/3D_Models/Hyrule_Shield/HShield_[Occlusion].tga")));

		/*Model* sponza = new tiger::Model("res/3D_Models/Sponza/sponza.obj");
		m_RenderableModels.push_back(new RenderableModel(glm::vec3(67.0f, 110.0f, 133.0f), glm::vec3(0.05f, 0.05f, 0.05f), glm::vec3(0.0f, 1.0f, 0.0f), glm::radians(180.0f), sponza, nullptr, true, false));*/
		
		// Skybox
		std::vector<std::string> skyboxFilePaths;
		skyboxFilePaths.push_back("res/skybox/right.png");
		skyboxFilePaths.push_back("res/skybox/left.png");
		skyboxFilePaths.push_back("res/skybox/top.png");
		skyboxFilePaths.push_back("res/skybox/bottom.png");
		skyboxFilePaths.push_back("res/skybox/back.png");
		skyboxFilePaths.push_back("res/skybox/front.png");
		m_Skybox = new Skybox(skyboxFilePaths);

		m_SceneCamera.setPosition(glm::vec3(90.0f, 80.0f, 180.0f));
	}

	void Scene3D::onUpdate(float deltaTime) {
		m_SceneCamera.processInput(deltaTime);

		m_DynamicLightManager.setSpotLightDirection(0, m_SceneCamera.getFront());
		m_DynamicLightManager.setSpotLightPosition(0, m_SceneCamera.getPosition());
	}

	void Scene3D::addModelsToRenderer() {
		auto iter = m_RenderableModels.begin();
		while (iter != m_RenderableModels.end()) {
			RenderableModel* curr = *iter;
			if (curr->getTransparent()) {
				m_ModelRenderer.submitTransparent(curr);
			}
			else {
				m_ModelRenderer.submitOpaque(curr);
			}

			iter++;
		}
	}

	void Scene3D::addStaticModelsToRenderer() {
		auto iter = m_RenderableModels.begin();
		while (iter != m_RenderableModels.end()) {
			RenderableModel* curr = *iter;
			if (curr->getStatic()) {
				if (curr->getTransparent()) {
					m_ModelRenderer.submitTransparent(curr);
				}
				else {
					m_ModelRenderer.submitOpaque(curr);
				}
			}
			iter++;
		}
	}

	void Scene3D::addTransparentModelsToRenderer() {
		auto iter = m_RenderableModels.begin();
		while (iter != m_RenderableModels.end()) {
			RenderableModel* curr = *iter;
			if (curr->getTransparent()) {
				m_ModelRenderer.submitTransparent(curr);
			}
			iter++;
		}
	}
	void Scene3D::addTransparentStaticModelsToRenderer() {
		auto iter = m_RenderableModels.begin();
		while (iter != m_RenderableModels.end()) {
			RenderableModel* curr = *iter;
			if (curr->getStatic() && curr->getTransparent()) {
				m_ModelRenderer.submitTransparent(curr);
			}
			iter++;
		}
	}
	void Scene3D::addOpaqueModelsToRenderer() {
		auto iter = m_RenderableModels.begin();
		while (iter != m_RenderableModels.end()) {
			RenderableModel* curr = *iter;
			if (!curr->getTransparent()) {
				m_ModelRenderer.submitOpaque(curr);
			}
			iter++;
		}
	}
	void Scene3D::addOpaqueStaticModelsToRenderer() {
		auto iter = m_RenderableModels.begin();
		while (iter != m_RenderableModels.end()) {
			RenderableModel* curr = *iter;
			if (curr->getStatic() && !curr->getTransparent()) {
				m_ModelRenderer.submitOpaque(curr);
			}
			iter++;
		}
	} 
}