#include "Engine/Render/Renderer.h"

namespace Engine
{
	Renderer& Renderer::GetInstance()
	{
		static Renderer instance;
		return instance;
	}

	bool Renderer::ShouldAPIClose()
	{
		return api.ShouldClose();
	}

	void Renderer::Close()
	{
		api.Shutdown();
	}

	void Renderer::DrawCall()
	{
		// 렌더링 전처리
		api.BeginFrame();

		// 키보드 입력
		api.KeyboardInputListener(*currentCamera);

		// 드로우 콜
		api.DrawIndexed(*currentCamera, 0);

		// 렌더링 후처리
		api.EndFrame();
	}

	Renderer::Renderer()
		: api()
		, currentCamera(nullptr)
	{
		api.Initialize();
	}

	Renderer::~Renderer()
	{
		currentCamera = nullptr;
		api.Shutdown();
	}

	/*
	void Renderer::bufferInitialize()
	{
		float vertices[] = {
			-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
			 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
			 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
			 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
			 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
			 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
			-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

			-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
			-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
			-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

			 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
			 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
			 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
			 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
			 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

			-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
			 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
			 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
			-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
			-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
		};

		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);

		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);

		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);

		//glGenBuffers(1, &EBO);
		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		string imageName;
		ResourceManager& manager = ResourceManager::getInstance();

		// 텍스쳐 1
		glGenTextures(1, &textureIds[0]);
		glBindTexture(GL_TEXTURE_2D, textureIds[0]);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		imageName = "awesomeface";
		Texture& texture1 = manager.getResource(imageName)->getTextrue();

		if (texture1.buffer)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texture1.width, texture1.height, 0, GL_RGB, GL_UNSIGNED_BYTE, texture1.buffer);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else
		{
			cerr << "[ERROR] 이미지 \"" << imageName << "\"이 존재하지 않습니다." << endl;
		}

		// 텍스쳐 2
		glGenTextures(1, &textureIds[1]);
		glBindTexture(GL_TEXTURE_2D, textureIds[1]);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		imageName = "container";
		Texture& texture2 = manager.getResource(imageName)->getTextrue();

		if (texture2.buffer)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texture2.width, texture2.height, 0, GL_RGB, GL_UNSIGNED_BYTE, texture2.buffer);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else
		{
			cerr << "[ERROR] 이미지 \"" << imageName << "\"이 존재하지 않습니다." << endl;
		}

		shader->use();
		shader->setInt("texture1", 0);
		shader->setInt("texture2", 1);
	}
	*/
}