#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Always include glad before glfw for dependencies

const char* vertexShaderSource = "#version 330 core\n"
"layout(location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

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

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// ----------------------------
	//        Vertex Data
	// ----------------------------

	float vertices[] = {
		-0.5f, -0.5f, 0.0f, // Left vertex  
		 0.5f, -0.5f, 0.0f, // Right vertex
		 0.0f,  0.5f, 0.0f  // Top  vertex
	};

	// ----------------------------
    //        Vertex Shader
    // ----------------------------

	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);

	// Now attach shader source code to the shader obj and compile the shader.
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	
	// Check that the shader compiled successfully.
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "Error::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	};

	// ----------------------------
	//       Fragment Shader
	// ----------------------------



	// First lets create our Vertex Buffer Object.
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	
	// Bind the buffer to the OpenGL vertex buffer type 'GL_ARRAY_BUFFER'
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	/* Copy our user-defined data into the currently bound buffer.
	   Below we pass: Target, Size, Data.
	   We use GL_STATIC_DRAW because the data does not change, 
	   if the data were to change frequently we could use GL_DYNAMIC_DRAW
	   so the GPU will place the data in memory that has faster writes.
	*/

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// ----------------------------
	//        Render Loop
	// ----------------------------

	while (!glfwWindowShouldClose(window))
	{
		// Check if esc pressed.
		processInput(window);

		// Rendering commands here.
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}