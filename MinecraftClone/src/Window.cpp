#include "Window.h"

Window::Window()
{
    screenWidth = 800;
    screenHeight = 1000;
    currentFrame = 0.0f;
    lastFrame = 0.0f;
    deltaTime = 0.0f;
    cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
    cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
    cameraRight = glm::normalize(glm::cross(cameraFront, cameraUp));
    lastX = (float)screenWidth / 2.0f;
    lastY = (float)screenHeight / 2.0f;
    yaw = -90.0f;
    pitch = 0.0f;
    firstMouse = true;
}

Window::Window(int width, int height, float camSpeed)
{
	screenWidth = width;
	screenHeight = height;
	cameraSpeed = camSpeed;
	currentFrame = 0.0f;
	lastFrame = 0.0f;
	deltaTime = 0.0f;
    cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
    cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
    cameraRight = glm::normalize(glm::cross(cameraFront, cameraUp));
    lastX = (float)screenWidth / 2.0f;
    lastY = (float)screenHeight / 2.0f;
    yaw = -90.0f;
    pitch = 0.0f;
    firstMouse = true;
}

int Window::Initialize()
{
	//Initialize GLFW
	if (!glfwInit()) {
		std::cout << "Initialization has failed." << std::endl;
		glfwTerminate();

		return -1;
	}

    // Optional: print GLFW errors to console
    glfwSetErrorCallback([](int error, const char* description) {
        std::cerr << "GLFW Error (" << error << "): " << description << std::endl;
    });

	//Setup GLFW window properties
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//Core Profile = No backwards compatibility
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//Allow forward compatibility
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    mainWindow = glfwCreateWindow(screenWidth, screenHeight, "VoxelCraft", NULL, NULL);
	if (!mainWindow) {
		std::cout << "GLFW window creation failed." << std::endl;
		glfwTerminate();

		return -1;
	}

	glfwMakeContextCurrent(mainWindow);
    glViewport(0, 0, screenWidth, screenHeight);

	// Initialize GLEW
	glewExperimental = GL_TRUE; // Load OpenGL functions from GPU to use it in c++
	if (glewInit() != GLEW_OK) {
		std::cout << "Failed to initialize GLEW" << std::endl;
		return -1;
	}

    glEnable(GL_DEPTH_TEST);
    // Draw both sides of faces to avoid visible holes when face winding is inconsistent.
    // Once winding is fixed, you can enable culling for a small performance gain.
    glDisable(GL_CULL_FACE);

    // Capture mouse and set callback
    glfwSetInputMode(mainWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    // register a lambda wrapper to forward mouse events to this instance
    glfwSetCursorPosCallback(mainWindow, [](GLFWwindow* wnd, double xpos, double ypos) {
        Window* self = reinterpret_cast<Window*>(glfwGetWindowUserPointer(wnd));
        if (self) self->ProcessMouseMovement(xpos, ypos);
    });
    // handle framebuffer resize to keep viewport correct
    glfwSetFramebufferSizeCallback(mainWindow, [](GLFWwindow* wnd, int w, int h) {
        glViewport(0, 0, w, h);
    });
    // attach this instance to the GLFWwindow user pointer
    glfwSetWindowUserPointer(mainWindow, this);

    // Ensure the window is shown and enable V-Sync
    glfwShowWindow(mainWindow);
    glfwSwapInterval(1);

    std::cout << "Window initialized: " << screenWidth << "x" << screenHeight << std::endl;
    std::cout << "GLEW Version: " << glewGetString(GLEW_VERSION) << std::endl;

    return 0;
}

void Window::HandleKeys()
{
    currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    if (glfwGetKey(mainWindow, GLFW_KEY_W) == GLFW_PRESS)
        cameraPos += deltaTime * cameraSpeed * cameraFront;
    if (glfwGetKey(mainWindow, GLFW_KEY_S) == GLFW_PRESS)
        cameraPos -= deltaTime * cameraSpeed * cameraFront;
    if (glfwGetKey(mainWindow, GLFW_KEY_A) == GLFW_PRESS)
        cameraPos -= deltaTime * cameraRight * cameraSpeed;
    if (glfwGetKey(mainWindow, GLFW_KEY_D) == GLFW_PRESS)
        cameraPos += deltaTime * cameraRight * cameraSpeed;
}

void Window::ProcessMouseMovement(double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = (float)xpos;
        lastY = (float)ypos;
        firstMouse = false;
    }

    float xoffset = (float)xpos - lastX;
    float yoffset = lastY - (float)ypos; // reversed since y-coordinates go from bottom to top
    lastX = (float)xpos;
    lastY = (float)ypos;

    float sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(front);
    cameraRight = glm::normalize(glm::cross(cameraFront, cameraUp));
}

Window::~Window()
{
	glfwTerminate();
}
