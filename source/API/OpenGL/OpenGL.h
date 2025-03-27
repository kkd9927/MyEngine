#pragma once

#include <memory>

#include <glad/glad.h>
#include <glfw/glfw3.h>

#include "Util/Header/Common.h"
#include "Engine/Render/Shader.h"
#include "Engine/Camera/Camera.h"

namespace API
{
	class OpenGL
	{
	public:
		// 라이프사이클
		bool Initialize();
		bool ShouldClose();
		void Shutdown();

		// 렌더링
		void BeginFrame();
		void DrawIndexed(Engine::Camera& camera, uint32_t indexCount, uint32_t startIndex = 0, int32_t baseVertex = 0);
		void EndFrame();
		void FrameBufferClear(float r, float g, float b, float a);
		float GetDeltaTime();

		// 셰이더
		void SetShader(Engine::Shader& shader);
		void RegisterShader(Engine::Shader& shader);

		// 버퍼
		//void SetVertexBuffer(/* const Mesh& mesh */);
		//void SetIndexBuffer(/* const Mesh& mesh */);

		// 입력감지
		void KeyboardInputListener(Engine::Camera& camera);

		float GetAspectRatio() const;
		
		OpenGL();
		~OpenGL();

	private:
		struct WindowContext
		{
			int screenWidth;
			int screenHeight;
			float aspectRatio;

			float deltaTime;
			float lastFrame;

			uint32_t vertexBufferId;
			uint32_t vertexArrayId;
			uint32_t indexBufferId;
		};

		GLFWwindow* window;
		WindowContext context;
		Engine::Shader shader;

		OpenGL(const OpenGL& rhs) = delete;
		OpenGL& operator=(const OpenGL& rhs) = delete;

		void UpdateDeltaTime();
	};
}