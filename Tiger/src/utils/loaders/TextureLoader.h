#pragma once

#include "graphics/texture/Texture.h"
#include "graphics/texture/Cubemap.h"

namespace tiger {

	class TextureLoader {

	private:

	public:
		static void initializeDefaultTextures();

		static Texture* load2DTexture(const std::string& path, bool isSRGB, TextureSettings* settings = nullptr);
		static Cubemap* loadCubemapTexture(const std::string& right, const std::string& left, const std::string& top, const std::string& bottom, const std::string& back, const std::string& front, bool isSRGB, CubemapSettings* settings = nullptr);

		inline static Texture* getDefaultAlbedo() { return m_DefaultAlbedo; }
		inline static Texture* getDefaultNormal() { return m_DefaultNormal; }
		inline static Texture* getDefaultMetallic() { return m_NoMetallic; }
		inline static Texture* getDefaultRoughness() { return m_NoRoughness; }
		inline static Texture* getDefaultAO() { return m_DefaultAO; }
		inline static Texture* getDefaultEmission() { return m_DefaultEmission; }
		inline static Texture* getFullMetallic() { return m_FullMetallic; }
		inline static Texture* getNoMetallic() { return m_NoMetallic; }
		inline static Texture* getFullRoughness() { return m_FullRoughness; }
		inline static Texture* getNoRoughness() { return m_NoRoughness; }

	private:
		static std::map<std::string, Texture*> m_TextureCache;
		// Default Textures
		static Texture* m_DefaultAlbedo;
		static Texture* m_DefaultNormal;
		static Texture* m_FullMetallic, * m_NoMetallic;
		static Texture* m_FullRoughness, * m_NoRoughness;
		static Texture* m_DefaultAO;
		static Texture* m_DefaultEmission;
	};

}