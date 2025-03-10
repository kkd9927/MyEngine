#include "Camera.h"

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
    pov(45.0f)
{
    updateCameraVectors();
}

Camera::Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = -90.f, float pitch = 0.0f) :
    position(position),
    front(glm::vec3(0.0f, 0.0f, -1.0f)),
    up(up),
    worldUp(up),
    right(glm::normalize(glm::cross(front, worldUp))),
    yaw(yaw),
    pitch(pitch),
    movementSpeed(2.5f),
    mouseSensitivity(0.1f),
    pov(45.0f)
{
	updateCameraVectors();
}

Camera::Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) :
    position(glm::vec3(posX, posY, posZ)),
    front(glm::vec3(0.0f, 0.0f, -1.0f)),
    up(glm::vec3(0.0f, 1.0f, 0.0f)),
    worldUp(glm::vec3(upX, upY, upZ)),
    right(glm::normalize(glm::cross(front, worldUp))),
    yaw(yaw),
    pitch(pitch),
    movementSpeed(2.5f),
    mouseSensitivity(0.1f),
    pov(45.0f)
{
    updateCameraVectors();
}

void Camera::processKeyboard(CameraMovement direction, float deltaTime)
{
    float velocity = movementSpeed * deltaTime;
    if (direction == FORWARD) 
        position += front * velocity;
    if (direction == BACKWARD) 
        position -= front * velocity;
    if (direction == LEFT) 
        position -= right * velocity;
    if (direction == RIGHT) 
        position += right * velocity;
}

void Camera::processMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true)
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

    updateCameraVectors();
}

void Camera::processMouseScroll(float yoffset)
{
    pov -= (float)yoffset;
    if (pov < 1.0f)
        pov = 1.0f;
    if (pov > 45.0f)
        pov = 45.0f;
}

void Camera::updateCameraVectors()
{
    glm::vec3 newFront;
    newFront.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    newFront.y = sin(glm::radians(pitch));
    newFront.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front = glm::normalize(newFront);

    right = glm::normalize(glm::cross(front, worldUp));
    up = glm::normalize(glm::cross(right, front));
}