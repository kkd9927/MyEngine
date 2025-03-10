#include "Renderer.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

Renderer::Renderer() : 
	textureIds(2), 
	firstMouse(true), 
	lastX(screenWidth / 2.0f), 
	lastY(screenHeight / 2.0f)
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWmonitor* monitor = glfwGetPrimaryMonitor();
	const GLFWvidmode* mode = glfwGetVideoMode(monitor);

	screenWidth = mode->width;
	screenHeight = mode->height;

	window = glfwCreateWindow(screenWidth, screenHeight, "MyEngine", nullptr, nullptr);
	if (!window)
	{
		cerr << "[ERROR] GLFW 윈도우 생성에 실패했습니다." << endl;
		cout << "Process Terminated" << endl;
		exit(0);
	}

	glfwMakeContextCurrent(window);

	bool isGLADInitialized = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	if (!isGLADInitialized)
	{
		cerr << "[ERROR] Renderer() : GLAD 초기화를 실패했습니다." << endl;
		cout << "Process Terminated" << endl;
		exit(0);
	}

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glEnable(GL_DEPTH_TEST);

	shader = new Shader("vertex", "fragment");
	camera = new Camera(glm::vec3(0.0f, 0.0f, 3.0f));
}

Renderer::~Renderer()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glfwTerminate();

	delete shader;
	delete window;
	delete camera;
}

Renderer& Renderer::getInstance()
{
	static Renderer instance;
	return instance;
}

bool Renderer::isClose() const
{
	return glfwWindowShouldClose(window);
}

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

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	Renderer& renderer = Renderer::getInstance();

	renderer.setScreenWidth(width);
	renderer.setScreenHeight(height);
	glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
	Renderer& renderer = Renderer::getInstance();
	Camera& camera = renderer.getCamera();

	float xpos = static_cast<float>(xposIn);
	float ypos = static_cast<float>(yposIn);

	// Renderer 생성자 초기화 리스트에서 true로 초기화 되며 mouse_callback 최초 호출 이후에는 아래 조건문이 사용되지 않음
	if (renderer.isFirstMouse())
	{
		renderer.setLastX(xpos);
		renderer.setLastY(ypos);
		renderer.setFirstMouse(false);
	}

	float xoffset = xpos - renderer.getLastX();
	float yoffset = renderer.getLastY() - ypos;

	renderer.setLastX(xpos);
	renderer.setLastY(ypos);

	camera.processMouseMovement(xoffset, yoffset, true);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	Renderer& renderer = Renderer::getInstance();
	Camera& camera = renderer.getCamera();
	camera.processMouseScroll(static_cast<float>(yoffset));
}