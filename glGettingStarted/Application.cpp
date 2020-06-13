#include "glad/glad.h" 
#include "GLFW/glfw3.h"

#include "utils/utils.h"
#include "Geometry.h"
#include "Texture.h"
#include "Equil.h"

#include <map>

#include "Shader.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
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
	
	glViewport(0, 0, 800, 600);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	{
	 	std::vector<float> vertices = {
			 0.0f,  0.5f,  0.0f,    0.0f,  0.5f,
			-0.5f, -0.5f,  0.0f,   -0.5f, -0.5f,
			 0.5f, -0.5f,  0.0f,    0.5f, -0.5f,
		};

		std::vector<unsigned int> indices = {
			0, 1, 2
		};


		std::vector<int> layout = { 3, 2 };

		//Geometry cube(vertices, layout, indices);
		Equil lattice(.5f);

		Shader shader("res/shaders/shader.sh");
		shader.bind();

		Texture tex("res/textures/im.jpg", "texture1");

		shader.setTexture(tex);
		 
		glm::mat4 model = glm::mat4(0.1f);

		glm::mat4 view = glm::mat4(1.0f);
		//view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

		glm::mat4 projection;
		projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);


		shader.setUniformMat4("model", model);
		shader.setUniformMat4("view", view);

		glEnable(GL_DEPTH_TEST);

		//model = cube.move(0.5f, 0.0f, -3.0f);

		while (!glfwWindowShouldClose(window))
		{
			//Process inputs
			processInput(window);
			glCall(glClearColor(0.2f, 0.3f, 0.3f, 1.0f));
			glCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

			

			lattice.bind();
			shader.bind();

			glCall(glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0));

			lattice.unbind();
			shader.unbind();


			glfwSwapBuffers(window);
			glfwPollEvents();
		}

	}
	
	glfwTerminate();
	return 0;
}