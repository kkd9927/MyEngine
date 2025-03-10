#pragma once

#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <utility>
#include <cstdlib>
#include <vector>

#include "Shader.h"
#include "Camera.h"

using namespace std;

class Renderer
{
private:
	ResourceManager* resourceManager;
	Shader* shader;
	GLFWwindow* window;
	Camera* camera;
	unsigned int VAO;
	unsigned int VBO;
	unsigned int EBO;
	vector<unsigned int> textureIds;
	
	int screenWidth;
	int screenHeight;
	bool firstMouse;
	float lastX;
	float lastY;

	Renderer();
	Renderer(const Renderer&) = delete;
	Renderer& operator=(const Renderer&) = delete;
	~Renderer();

public:
	static Renderer& getInstance();
	bool isClose() const;
	void bufferInitialize();
	const unsigned int getTextureIdByIndex(size_t index) const { return textureIds[index]; };
	Shader& getShader() const { return *shader; }
	GLFWwindow& getWindow() const { return *window; }
	Camera& getCamera() const { return *camera; }
	unsigned int getVAO() { return VAO; }
	unsigned int getVBO() { return VBO; }
	unsigned int getEBO() { return EBO; }

	int getScreenWidth() const { return screenWidth; }
	int getScreenHeight() const { return screenHeight; }
	void setScreenWidth(int width) { screenWidth = width; }
	void setScreenHeight(int height) { screenHeight = height; }
	bool isFirstMouse() { return firstMouse; }
	void setFirstMouse(bool param) { firstMouse = param; }
	float getLastX() const { return lastX; }
	float getLastY() const { return lastY; }
	void setLastX(float x) { lastX = x; }
	void setLastY(float y) { lastY = y; }

};