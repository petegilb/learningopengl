#include <memory>
#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

// intro code from: https://learnopengl.com/Getting-started/Hello-Window

// when the user resizes the window, the opengl viewport should also be resized
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

// handle input
void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

int main(){
    std::cout << "Starting up opengl learning app!" << std::endl;

    // Initialize glfw and configure it with our opengl version that we chose (in this case 3.3)
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Apparently this is required on Mac, so I added it here
#if defined(__APPLE__)
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // create a window for glfw
    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // initialize glad
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // tell opengl the size of the viewport
    glViewport(0, 0, 800, 600);

    // set callback for window resizing
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // simple render loop
    // we are swapping buffers because we are using a double buffer to prevent flickering issues/artifacts when the buffer is drawn to
    while(!glfwWindowShouldClose(window))
    {
        // input
        processInput(window);

        // rendering commands here
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // check and call events and swap the buffers
        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    // clean up all resources
    glfwTerminate();
    return 0;
}
