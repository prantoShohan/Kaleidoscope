#include "glad/glad.h" 
#include "GLFW/glfw3.h"

#include "utils/utils.h"
#include "Object.h"
#include "Texture.h"
#include "Camera.h"

#include <map>

#include "Shader.h"


const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;	
float lastFrame = 0.0f;

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);

}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(0, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(1, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(2, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(3, deltaTime);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
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

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	
	glViewport(0, 0, 800, 600);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	{
// 		float vertices[] = {
// 
// 		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
// 		 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
// 		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
// 		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
// 		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
// 		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f
// 
// 		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
// 		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
// 		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
// 		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
// 		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
// 		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
// 
// 		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
// 		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
// 		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
// 		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
// 		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
// 		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
// 
// 		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
// 		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
// 		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
// 		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
// 		 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
// 		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
// 
// 		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
// 		 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
// 		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
// 		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
// 		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
// 		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
// 
// 		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
// 		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
// 		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
// 		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
// 		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
// 		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
// 
// 		};
// 		float vertices[] = {
// 			// positions          // colors           // texture coords
// 			 0.5f,  0.5f, 0.0f,  1.0f, 1.0f,   // top right
// 			 0.5f, -0.5f, 0.0f,  1.0f, 0.0f,   // bottom right
// 			-0.5f, -0.5f, 0.0f,  0.0f, 0.0f,   // bottom left
// 			-0.5f,  0.5f, 0.0f,  0.0f, 1.0f    // top left 
// 		};
// 
// 		unsigned int indices[] = {
// 			0, 1, 2,
// 			0, 2, 3
// 		};
// 		float vertices[] = {
// 			0.5f,   0.5f,  -0.5f,       0.0f,  0.0f,
// 			0.5f,   0.5f,   0.5f,		1.0f,  0.0f,
// 		   -0.5f,   0.5f,   0.5f,		1.0f,  1.0f,
// 		   -0.5f,   0.5f,  -0.5f,		0.0f,  1.0f,
// 
// 			0.5f,  -0.5f,  -0.5f,		1.0f,  1.0f,
// 			0.5f,  -0.5f,   0.5f,		0.0f,  1.0f,
// 		   -0.5f,  -0.5f,   0.5f,		0.0f,  0.0f,
// 		   -0.5f,  -0.5f,  -0.5f,		1.0f,  0.0f,
// 
// 		};
// 
// 		unsigned int indices[] = {
// 			2, 1, 0, 
// 			2, 0, 3,
// 			1, 5, 4, 
// 			1, 4, 0, 
// 			6, 5, 4,
// 			6, 4, 7,
// 			2, 6, 5,
// 			2, 5, 1, 
// 			0, 4, 7,
// 			0, 7, 3,
// 			3, 7, 6, 
// 			3, 6, 2
// 		};
// 
// 		//Object cube(vertices, layout, indices)
// 
// 		unsigned int vao, vbo, ebo;
// 
// 		glCall(glGenVertexArrays(1, &vao));
// 		glCall(glBindVertexArray(vao));
// 
// 		glCall(glGenBuffers(1, &vbo));
// 		glCall(glBindBuffer(GL_ARRAY_BUFFER, vbo));
// 		glCall(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW));
// 
// 		glCall(glGenBuffers(1, &ebo));
// 		glCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo));
// 		glCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW));
// 
// 		glCall(glEnableVertexAttribArray(0));
// 		glCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 20, (void*)0));
// 
// 		glCall(glEnableVertexAttribArray(1));
// 		glCall(glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 20, (void*)12));

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

		Object cube(vertices, layout, indices);

		Shader shader("res/shaders/shader.sh");
		shader.bind();

		Texture tex("res/textures/container.jpg", "texture1");

		shader.setTexture(tex);

		glEnable(GL_DEPTH_TEST);

		while (!glfwWindowShouldClose(window))
		{
			//Process inputs
			processInput(window);
			glCall(glClearColor(0.2f, 0.3f, 0.3f, 1.0f));
			glCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

			float currentFrame = glfwGetTime();
			deltaTime = currentFrame - lastFrame;
			lastFrame = currentFrame;


			cube.bind();
			shader.bind();

			glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
			shader.setUniformMat4("projection", projection);

			glm::mat4 view = camera.GetViewMatrix();
			shader.setUniformMat4("view", view);

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