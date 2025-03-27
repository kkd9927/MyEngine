#pragma once

#include <unordered_map>
#include <string>

#include "Engine/Camera/Camera.h"
#include "API/OpenGL/OpenGL.h"
#include "Util/Header/Common.h"

namespace Engine
{
	class Renderer
	{
	public:
		static Renderer& GetInstance();
		bool ShouldAPIClose();
		void Close();

		void DrawCall();

		uint32_t GetTextureIdByName(const std::string& textureName) const;
		void SetCurrentCamera(Camera& camera) { currentCamera = &camera; };
		Camera& GetCurrentCamera() const { return *currentCamera; }

	private:
		API::OpenGL api;
		Camera* currentCamera;
		std::unordered_map<std::string, uint32_t> textureMap;

		Renderer();
		~Renderer();

		Renderer(const Renderer&) = delete;
		Renderer& operator=(const Renderer&) = delete;
	};
}