#include "API/OpenGL/OpenGL.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Engine/Render/Renderer.h"
#include "Engine/Render/Shader.h"
#include "Engine/Camera/Camera.h"
#include "Util/Header/Common.h"
#include "Util/Logger/Logger.h"
#include "Util/FileSystem/FileSystem.h"

namespace API
{
	/**
	 * @brief OpenGL을 사용하기 위한 초기화 함수 입니다.
	 * 
	 * @return 필수 초기화(GFLW 초기화, 윈도우 컨텍스트 생성, GLAD 함수 바인딩)에 실패하면 도중에 작업이 중단되고 false를 반환합니다.
	 * @return 필수 초기화가 모두 성공했다면 true를 반환합니다.
	 */
	bool OpenGL::Initialize()
	{
		if (!glfwInit())
		{
			// Util::Logger::Error("GLFW 초기화에 실패 했습니다.");
			return false;
		}

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		
		GLFWmonitor* monitor = glfwGetPrimaryMonitor();
		const GLFWvidmode* mode = glfwGetVideoMode(monitor);
		int width = mode->width;
		int height = mode->height;

		window = glfwCreateWindow(width, height, "MyEngine", nullptr, nullptr);
		if (!window)
		{
			// Util::Logger::Error("윈도우 생성에 실패 했습니다.");
			return false;
		}

		context.screenWidth = width;
		context.screenHeight = height;

		glfwMakeContextCurrent(window);
		glfwSetWindowUserPointer(window, &context);

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			// Util::Logger::Error("GLAD 로드에 실패 했습니다.");
			return false;
		}

		glfwSetFramebufferSizeCallback(window,
			[](GLFWwindow* window, int width, int height) -> void
			{
				glViewport(0, 0, width, height);
			}
		);

		glfwSetCursorPosCallback(window,
			[](GLFWwindow* window, double xposIn, double yposIn) -> void
			{
				// Renderer, Camera 객체의 경우 glfwSetWindowUserPointer(window, this 포인터)로 등록하여 window 컨텍스트에서 바로 참조하도록 변경 가능
				// 단 glfwSetWindowUserPointer 함수는 void* 한개만 등록 가능하므로 Renderer, Camera등 현재 window 컨텍스트 상태를 가지는 별도의 구조체로 묶어야함 
				Engine::Renderer& renderer = Engine::Renderer::GetInstance();
				Engine::Camera& camera = renderer.GetCurrentCamera();

				float xpos = static_cast<float>(xposIn);
				float ypos = static_cast<float>(yposIn);

				float xoffset = xpos - camera.GetLastX();
				float yoffset = camera.GetLastY() - ypos;

				camera.SetLastX(xpos);
				camera.SetLastY(ypos);

				camera.ProcessMouseMovement(xoffset, yoffset, true);
			}
		);

		glfwSetScrollCallback(window,
			[](GLFWwindow* window, double xoffset, double yoffset) -> void
			{
				// 카메라의 POV값을 변경합니다.
				// Renderer, Camera 객체의 경우 glfwSetWindowUserPointer(window, this 포인터)로 등록하여 window 컨텍스트에서 바로 참조하도록 변경 가능
				// 단 glfwSetWindowUserPointer 함수는 void* 한개만 등록 가능하므로 Renderer, Camera등 현재 window 컨텍스트 상태를 가지는 별도의 구조체로 묶어야함
				Engine::Renderer& renderer = Engine::Renderer::GetInstance();
				Engine::Camera& camera = renderer.GetCurrentCamera();
				camera.ProcessMouseScroll(static_cast<float>(yoffset));
			}
		);
		
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

		glEnable(GL_DEPTH_TEST);

		SetShader(shader);

		return true;
	}

	bool OpenGL::ShouldClose()
	{
		return glfwWindowShouldClose(window);
	}

	/**
	 * @brief 프로그램 종료 또는 API에 문제가 발생했을 경우 자원을 반환 합니다.
	 */
	void OpenGL::Shutdown()
	{
		glDeleteVertexArrays(1, &context.vertexArrayId);
		glDeleteBuffers(1, &context.vertexBufferId);
		glDeleteBuffers(1, &context.indexBufferId);
		glfwDestroyWindow(window);
		glfwTerminate();
	}

	/**
	 * @brief 렌더링 전 델타 타임 갱신, 화면 초기화를 수행합니다.
	 */
	void OpenGL::BeginFrame()
	{
		UpdateDeltaTime();
		FrameBufferClear(0.f, 0.f, 0.f, 1.f);

		// 별도 텍스쳐 바인딩 함수 만들어서 반복문으로 처리
		/*
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, renderer.getTextureIdByIndex(0));
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, renderer.getTextureIdByIndex(1));
		*/

		shader.Use();
	}

	void OpenGL::DrawIndexed(Engine::Camera& camera, uint32_t indexCount, uint32_t startIndex, int32_t baseVertex)
	{
		float zoom = glm::radians(camera.GetPov());
		float aspect = context.aspectRatio;
		float nearPlane = 0.1f;
		float farPlane = 100.0f;

		glm::mat4 projection = glm::perspective(zoom, aspect, nearPlane, farPlane);
		shader.SetMat4("projection", projection);

		glm::mat4 view = camera.GetViewMatrix();
		shader.SetMat4("view", view);

		// 이후 glDrawElements()로 변경
		//glBindVertexArray(context.vertexArrayId);
		//for (unsigned int i = 0; i < 10; i++)
		//{
		//	glm::mat4 model = glm::mat4(1.0f);
		//	model = glm::translate(model, cubePositions[i]);
		//	float angle = 20.0f * i;
		//	model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
		//	shader.setMat4("model", model);

		//	glDrawArrays(GL_TRIANGLES, 0, 36);
		//}
	}

	/**
	 * @brief 렌더링 후 버퍼 스왑, 입력 감지를 수행합니다.
	 */
	void OpenGL::EndFrame()
	{
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	/**
	 * @brief 렌더링 전 프레임 버퍼 초기화를 수행합니다.
	 * @brief OpenGL은 더블 버퍼링으로 프레임을 표현합니다. 현재 화면에 보여지고 있는 프레임은 Front Buffer, 
	 * @brief 다음 화면을 위해 그려지고 있는 프레임은 Back Buffer에 저장하고 매 프레임 마다 버퍼를 스왑(glfwSwapBuffers)
	 * @brief 하면서 화면에 픽셀을 렌더링 합니다.
	 * @brief glClear함수의 인수 [GL_COLOR_BUFFER_BIT]는 glClearColor 함수로 설정한 색상으로 버퍼를 초기화 합니다.
	 * @brief [GL_DEPTH_BUFFER_BIT]는 3D에서 깊이값(Z-Depth) 버퍼를 초기화 합니다.
	 * @brief 버퍼 초기화를 하지 않으면 의도하지 않은 픽셀이 그려지거나, 픽셀이 겹치는 문제가 발생합니다.
	 * 
	 * @param 색상 버퍼 초기화를 위한 float 타입의 범위 0 ~ 1 RGBA 가중치를 인수로 받습니다.
	 */
	void OpenGL::FrameBufferClear(float r, float g, float b, float a)
	{
		glClearColor(r, g, b, a);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	/**
	 * @brief 오브젝트 트랜스폼 연산에서 곱할 경우 프레임 차이에 의해 발생하는 속도 차를 일정하게 보정합니다.
	 * 
	 * @return float 델타 시간을 반환합니다.
	 */
	float OpenGL::GetDeltaTime()
	{
		return context.deltaTime;
	}

	void OpenGL::SetShader(Engine::Shader& shader)
	{
		// 셰이더 프로그램이 생성되어 있지 않은 경우 등록
		if (!shader.GetShaderId())
		{
			RegisterShader(shader);
		}

		shader.Use();
	}

	void OpenGL::RegisterShader(Engine::Shader& shader)
	{
		Util::FileSystem& fileSystem = Util::FileSystem::GetInstance();
		const Util::File* vertexFile = fileSystem.FindFile("vertex.glsl");
		const Util::File* fragmentFile = fileSystem.FindFile("fragment.glsl");

		if (!vertexFile)
		{
			// Util::Logger::Error("Util::File* vertexFile = nullptr 입니다.");
			return;
		} 
		else if (!fragmentFile)
		{
			// Util::Logger::Error("Util::File* fragmentFile = nullptr 입니다.");
			return;
		}

		const char* vertexCode = vertexFile->GetStreamToString().c_str();
		const char* fragmentCode = vertexFile->GetStreamToString().c_str();

		uint32_t vertexShader, fragmentShader;
		int success;
		char infoLog[512];

		// 버텍스 셰이더
		vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShader, 1, &vertexCode, nullptr);
		glCompileShader(vertexShader);

		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
			// Util::Logger::Error("버텍스 셰이더 컴파일에 실패했습니다.");
		}

		// 프래그먼트 셰이더
		fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, 1, &fragmentCode, nullptr);
		glCompileShader(fragmentShader);

		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
			// Util::Logger::Error("프래그먼트 셰이더 컴파일에 실패했습니다.");
		}

		uint32_t shaderId = glCreateProgram();
		glAttachShader(shaderId, vertexShader);
		glAttachShader(shaderId, fragmentShader);
		glLinkProgram(shaderId);

		glGetProgramiv(shaderId, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(shaderId, 512, NULL, infoLog);
			// Util::Logger::Error("셰이더 프로그램 링크에 실패했습니다.");
		}

		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);

		shader.SetShaderId(shaderId);
	}

	/**
	 * @brief 하드웨어 속도에 따른 연산속도 차이를 제거하기 위해 델타 시간(Delta Time)을 갱신합니다.
	 */
	void OpenGL::UpdateDeltaTime()
	{
		float currentFrame = static_cast<float>(glfwGetTime());
		context.deltaTime = currentFrame - context.lastFrame;
		context.lastFrame = currentFrame;
	}

	/**
	 * @brief 키보드 인풋을 감지합니다.
	 */
	void OpenGL::KeyboardInputListener(Engine::Camera& camera)
	{
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(window, true);
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
			camera.ProcessKeyboard(Engine::ECameraMovement::FORWARD, GetDeltaTime());
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
			camera.ProcessKeyboard(Engine::ECameraMovement::BACKWARD, GetDeltaTime());
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
			camera.ProcessKeyboard(Engine::ECameraMovement::LEFT, GetDeltaTime());
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
			camera.ProcessKeyboard(Engine::ECameraMovement::RIGHT, GetDeltaTime());
	}
	
	float OpenGL::GetAspectRatio() const
	{
		return context.aspectRatio;
	}

	OpenGL::OpenGL()
		: window(nullptr)
		, context()
		, shader()
	{}

	OpenGL::~OpenGL()
	{
		delete window;
	}
}
