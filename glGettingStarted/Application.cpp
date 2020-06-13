#include "glad/glad.h" 
#include "GLFW/glfw3.h"

#include "utils/utils.h"
#include "Geometry.h"
#include "Texture.h"

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
			0.5f,   0.5f,  -0.5f,       0.0f,  0.0f,
			0.5f,   0.5f,   0.5f,		1.0f,  0.0f,
		   -0.5f,   0.5f,   0.5f,		1.0f,  1.0f,
		   -0.5f,   0.5f,  -0.5f,		0.0f,  1.0f,

			0.5f,  -0.5f,  -0.5f,		1.0f,  1.0f,
			0.5f,  -0.5f,   0.5f,		0.0f,  1.0f,
		   -0.5f,  -0.5f,   0.5f,		0.0f,  0.0f,
		   -0.5f,  -0.5f,  -0.5f,		1.0f,  0.0f,

		};

		std::vector<unsigned int> indices = {
			2, 1, 0, 
			2, 0, 3,
			1, 5, 4, 
			1, 4, 0, 
			6, 5, 4,
			6, 4, 7,
			2, 6, 5,
			2, 5, 1, 
			0, 4, 7,
			0, 7, 3,
			3, 7, 6, 
			3, 6, 2
		};

		glm::vec3 cubePositions[] = {
			glm::vec3(0.0f,  0.0f,  0.0f),
			glm::vec3(2.0f,  5.0f, -15.0f),
			glm::vec3(-1.5f, -2.2f, -2.5f),
			glm::vec3(-3.8f, -2.0f, -12.3f),
			glm::vec3(2.4f, -0.4f, -3.5f),
			glm::vec3(-1.7f,  3.0f, -7.5f),
			glm::vec3(1.3f, -2.0f, -2.5f),
			glm::vec3(1.5f,  2.0f, -2.5f),
			glm::vec3(1.5f,  0.2f, -1.5f),
			glm::vec3(-1.3f,  1.0f, -1.5f)
		};

		std::vector<int> layout = { 3, 2 };

		Geometry cube(vertices, layout, indices);

		Shader shader("res/shaders/shader.sh");
		shader.bind();

		Texture tex("res/textures/container.jpg", "texture1");

		shader.setTexture(tex);
		 
		 glm::mat4 model = cube.rotate(1.0f, 1.0f, 0.0f, 45.0f);

		glm::mat4 view = glm::mat4(1.0f);
		view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

		glm::mat4 projection;
		projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);


		shader.setUniformMat4("model", model);
		shader.setUniformMat4("view", view);
		shader.setUniformMat4("projection", projection);

		glEnable(GL_DEPTH_TEST);

		model = cube.move(0.5f, 0.0f, -3.0f);

		while (!glfwWindowShouldClose(window))
		{
			//Process inputs
			processInput(window);
			glCall(glClearColor(0.2f, 0.3f, 0.3f, 1.0f));
			glCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

			

			cube.bind();
			shader.bind();

			for (unsigned int i = 0; i < 10; i++)
			{
				glm::mat4 model = glm::mat4(1.0f);
				model = glm::translate(model, cubePositions[i]);
				float angle = 20.0f * i;
				model = glm::rotate(model, glm::radians(angle), glm::vec3(sin(glfwGetTime()), 0.3f, 0.5f));
				shader.setUniformMat4("model", model);

				glCall(glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0));
			}

			
			//glCall(glDrawArrays(GL_TRIANGLES, 0, 36));

			cube.unbind();
			shader.unbind();


			glfwSwapBuffers(window);
			glfwPollEvents();
		}

	}
	
	glfwTerminate();
	return 0;
}