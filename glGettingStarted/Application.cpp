#include "glad/glad.h" 
#include "GLFW/glfw3.h"

#include "utils/utils.h"
#include "Geometry.h"
#include "Texture.h"
#include "Equil.h"

#include "Kaleido.h"

#include <map>

#include "Shader.h"

#include <Windows.h>
#include "Vendor/FastNoise.h"


Kaleido kal;
// 
float WIDTH = 800;
float HEIGHT = 600;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	kal.key_callback(key, scancode, action, mods);

}

void drop_callback(GLFWwindow* window, int path_count, const char* paths[])
{
	kal.drop_callback(path_count, paths);

}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	kal.scroll_callback(xoffset, yoffset);

}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{	

	kal.mouse_callback(window, xpos, ypos);

}


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
	kal.framebuffer_size_callback(width, height);
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

//int WinMain( _In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd )
int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "Kaleidoscope", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetDropCallback(window, drop_callback);
	glfwSetKeyCallback(window, key_callback);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	glViewport(0, 0, 800, 600);



	{


		kal.init(HEIGHT, WIDTH);

		glEnable(GL_DEPTH_TEST);

		//model = cube.move(0.5f, 0.0f, -3.0f);

		while (!glfwWindowShouldClose(window))
		{
			//Process inputs
			processInput(window);
			glCall(glClearColor(0.2f, 0.3f, 0.3f, 1.0f));
			glCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

			kal.draw();

			glfwSwapBuffers(window);
			glfwPollEvents();
		}

	}
	
	glfwTerminate();
	return 0;
}