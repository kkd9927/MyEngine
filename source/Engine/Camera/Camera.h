#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Engine
{
    enum class ECameraMovement {
        FORWARD,
        BACKWARD,
        LEFT,
        RIGHT
    };

    class Camera
    {
    public:
        explicit Camera(glm::vec3 position);
        explicit Camera(float x, float y, float z);
        // Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch);
        // Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);
        ~Camera() = default;

        void ProcessKeyboard(ECameraMovement direction, float deltaTime);
        void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch);
        void ProcessMouseScroll(float yoffset);
        glm::mat4 GetViewMatrix() const { return glm::lookAt(position, position + front, up); }
        float GetPov() { return pov; }
        float GetLastX() const { return lastX; }
        float GetLastY() const { return lastY; }
        void SetLastX(float x) { lastX = x; }
        void SetLastY(float y) { lastY = y; }

    private:
        glm::vec3 position;
        glm::vec3 front;
        glm::vec3 up;
        glm::vec3 right;
        glm::vec3 worldUp;
        float yaw;
        float pitch;
        float movementSpeed;
        float mouseSensitivity;
        float pov;

        float lastX;
        float lastY;

        void UpdateCameraVectors();
    };
}