#include "Camera.h"

namespace Engine
{
    Camera::Camera(glm::vec3 position) :
        position(position),
        front(glm::vec3(0.0f, 0.0f, -1.0f)),
        up(glm::vec3(0.0f, 1.0f, 0.0f)),
        worldUp(up),
        right(glm::normalize(glm::cross(front, worldUp))),
        yaw(-90.f),
        pitch(0.0f),
        movementSpeed(2.5f),
        mouseSensitivity(0.1f),
        pov(45.0f),
        lastX(0),
        lastY(0)
    {
        UpdateCameraVectors();
    }

    Camera::Camera(float x, float y, float z) 
        : Camera(glm::vec3(x, y, z))
    {}

    /*Camera::Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = -90.f, float pitch = 0.0f) :
        position(position),
        front(glm::vec3(0.0f, 0.0f, -1.0f)),
        up(up),
        worldUp(up),
        right(glm::normalize(glm::cross(front, worldUp))),
        yaw(yaw),
        pitch(pitch),
        movementSpeed(2.5f),
        mouseSensitivity(0.1f),
        pov(45.0f),
        lastX(0),
        lastY(0)
    {
        UpdateCameraVectors();
    }*/

    /*Camera::Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) :
        position(glm::vec3(posX, posY, posZ)),
        front(glm::vec3(0.0f, 0.0f, -1.0f)),
        up(glm::vec3(0.0f, 1.0f, 0.0f)),
        worldUp(glm::vec3(upX, upY, upZ)),
        right(glm::normalize(glm::cross(front, worldUp))),
        yaw(yaw),
        pitch(pitch),
        movementSpeed(2.5f),
        mouseSensitivity(0.1f),
        pov(45.0f),
        lastX(0),
        lastY(0)
    {
        UpdateCameraVectors();
    }*/

    void Camera::ProcessKeyboard(Engine::ECameraMovement direction, float deltaTime)
    {
        float velocity = movementSpeed * deltaTime;
        if (direction == Engine::ECameraMovement::FORWARD)
            position += front * velocity;
        if (direction == Engine::ECameraMovement::BACKWARD)
            position -= front * velocity;
        if (direction == Engine::ECameraMovement::LEFT)
            position -= right * velocity;
        if (direction == Engine::ECameraMovement::RIGHT)
            position += right * velocity;
    }

    void Camera::ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true)
    {
        xoffset *= mouseSensitivity;
        yoffset *= mouseSensitivity;

        yaw += xoffset;
        pitch += yoffset;

        if (constrainPitch)
        {
            if (pitch > 89.0f)
                pitch = 89.0f;
            if (pitch < -89.0f)
                pitch = -89.0f;
        }

        UpdateCameraVectors();
    }

    void Camera::ProcessMouseScroll(float yoffset)
    {
        pov -= (float)yoffset;
        if (pov < 1.0f)
            pov = 1.0f;
        if (pov > 45.0f)
            pov = 45.0f;
    }

    void Camera::UpdateCameraVectors()
    {
        glm::vec3 newFront;
        newFront.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        newFront.y = sin(glm::radians(pitch));
        newFront.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        front = glm::normalize(newFront);

        right = glm::normalize(glm::cross(front, worldUp));
        up = glm::normalize(glm::cross(right, front));
    }
}