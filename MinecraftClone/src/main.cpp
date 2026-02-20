#include <glew.h>
#include <glfw3.h>

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include "Window.h"
#include "Mesh.h"
#include "Shader.h"
#include "Chunk.h"
#include "Texture.h"

#include <vector>

int main(void)
{
    // Use Window wrapper (which initializes GLFW / GLEW and sets up GL)
    Window windowObj(1080, 700, 3.0f);
    if (windowObj.Initialize() != 0) {
        return -1;
    }

    GLFWwindow* window = windowObj.GetWindow();

    // Get framebuffer size and set viewport
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);

    std::cout << "Framebuffer size: " << width << "x" << height << std::endl;

    //Chunk
    Chunk chunk(glm::vec3(0.0f, 0.0f, 0.0f));
    chunk.BuildChunk();


    // Camera will be managed by Window; we'll query it each frame
    glm::vec3 cameraPos;
    glm::vec3 cameraFront;
    glm::vec3 cameraUp;

    // Compile shaders (shader files should be in src/Shaders/)
    Shader shader;
    shader.CompileShader("src/Shaders/triangle.vert", "src/Shaders/triangle.frag");

    // Uniform locations
    unsigned int shaderID = shader.GetShaderID();
    int modelLoc = glGetUniformLocation(shaderID, "model");
    int viewLoc = glGetUniformLocation(shaderID, "view");
    int projLoc = glGetUniformLocation(shaderID, "projection");
    int texLoc = glGetUniformLocation(shaderID, "uTexture");

    /* Loop until the user closes the window */
    while (!windowObj.GetShouldClose())
    {
        // Handle keyboard input (WASD) and mouse (internal to Window)
        windowObj.HandleKeys();

        // Query camera state from Window
        cameraPos = windowObj.GetCameraPos();
        cameraFront = windowObj.GetCameraFront();
        cameraUp = windowObj.GetCameraUp();

        /* Render here */
        glClearColor(0.1f, 0.1f, 0.15f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.UseShader();

        // Build transformation matrices
        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
        glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 100.0f);

        // Upload matrices
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

		chunk.Render(shader);

        /* Swap front and back buffers */
        windowObj.SwapBuffers();

        /* Poll for and process events */
        glfwPollEvents();
    }

    return 0;
}
