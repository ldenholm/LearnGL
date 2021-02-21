#include <iostream>

// Always include glad before glfw for dependencies
#include <glad/glad.h>
#include <GLFW/glfw3.h>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

int main()
{
	// ----------------------------
	//          SETUP
	// ----------------------------

   /* - Initialize library.
	* - Configure to use OpenGL 3.3 (major-minor versions).
	* - Explicitly declare we will use core-profile, a subset of OpenGL features.
	*/

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// ----------------------------
	//       Create Window
	// ----------------------------

	GLFWwindow* window = glfwCreateWindow(800, 600, "Practice Good Learning", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create the window" << std::endl;
		glfwTerminate();
		return -1;
	}

	// Make the context of our window the main context on the current thread.
	glfwMakeContextCurrent(window);

	// Tell GLAD to load address of the OpenGL function pointers
    // (which is OS specific), using GetProcAddress.
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// Callback func to handle window resizing.
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// ----------------------------
	//       Control Loop
	// ----------------------------

	while (!glfwWindowShouldClose(window))
	{
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// ----------------------------
    //         Terminate
    // ----------------------------

	glfwTerminate();
	return 0;
}

// ----------------------------
//       STATIC METHODS
// ----------------------------

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}