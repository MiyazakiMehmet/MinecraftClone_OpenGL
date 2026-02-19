#pragma once

#include <glew.h>
#include <glfw3.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include <iostream>

class Window {
private:
	GLFWwindow* mainWindow;
	int screenWidth, screenHeight;
	float currentFrame, lastFrame, deltaTime, cameraSpeed;

    // Camera state stored in window
    glm::vec3 cameraPos;
    glm::vec3 cameraFront;
    glm::vec3 cameraUp;
    glm::vec3 cameraRight;

    // Mouse control
    float lastX;
    float lastY;
    float yaw;
    float pitch;
    bool firstMouse;
public:
	Window();
	Window(int width, int height, float camSpeed);

	int Initialize();

	bool GetShouldClose() { return glfwWindowShouldClose(mainWindow); }

	void SwapBuffers() { return glfwSwapBuffers(mainWindow); }

    void HandleKeys();

    // Mouse processing is via GLFW callback registered by Initialize
    void ProcessMouseMovement(double xpos, double ypos);

    glm::vec3 GetCameraPos() { return cameraPos; }
    glm::vec3 GetCameraFront() { return cameraFront; }
    glm::vec3 GetCameraUp() { return cameraUp; }

	GLFWwindow* GetWindow() { return mainWindow; }

	~Window();
};