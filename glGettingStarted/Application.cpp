#include "glad/glad.h" 
#include "GLFW/glfw3.h"

#include "utils/utils.h"
#include "Geometry.h"
#include "Texture.h"
#include "Equil.h"

#include <map>

#include "Shader.h"

#include <Windows.h>

float b = 0.5f;

glm::vec2 tZero = glm::vec2(0.0f, 0.0f);
glm::vec2 tOne = glm::vec2(b, 0.0f);
glm::vec2 tTwo = glm::vec2(b / 2, b* sin(-30));

float rot = 0;

glm::mat4 projection;


bool firstMouse = true;
float lastX = 400, lastY = 300;



glm::vec2 scaleVec2(glm::vec2 tVec, float offset)
{
	float mul = 1.0f;
	if (offset > 0)
	{
		mul = 1.03f;
	}
	else if (offset < 0)
	{
		mul = 0.97f;
	}
	glm::mat4 s = glm::mat4(1.0f);
	glm::vec4 tm4(tVec, 1.0f, 1.0f);
	glm::vec3 pivot((tZero + tOne + tTwo) / 3.0f, 1.0f);

	s = glm::translate(s, -pivot) * glm::scale(s, glm::vec3(mul,  mul, 1.0f)) * glm::translate(s, pivot);


	tm4 = s * tm4;

	glm::vec2 tm2(tm4);

	return tm2;
}

glm::vec2 rotateVec2(glm::vec2 tVec, float offset)
{
	glm::mat4 s = glm::mat4(1.0f);
	glm::vec4 tm4(tVec, 1.0f, 1.0f);
	glm::vec3 pivot((tZero + tOne + tTwo) / 3.0f, 1.0f);

	s = glm::translate(s, -pivot) * glm::rotate(s, glm::radians(offset * 0.2f), glm::vec3(0.0f, 0.0f, 1.0f)) * glm::translate(s, pivot);


	tm4 = s * tm4;

	glm::vec2 tm2(tm4);

	return tm2;
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	float of = yoffset ;
	tZero = scaleVec2(tZero, of);
	tOne = scaleVec2(tOne, of);
	tTwo = scaleVec2(tTwo, of);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{	

	int pressed = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
	int rPressed = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT);

	if (rPressed == GLFW_PRESS)
	{
		float yof = lastY - ypos;

		tZero = rotateVec2(tZero, yof);
		tOne =  rotateVec2(tOne, yof);
		tTwo =  rotateVec2(tTwo, yof);
	}

	if (pressed == GLFW_PRESS)
	{

		if (firstMouse)
		{
			lastX = xpos;
			lastY = ypos;
			firstMouse = false;
		}

		float xoffset = xpos - lastX;
		float yoffset = lastY - ypos;
		

		float sensitivity = 1.0f;
		xoffset *= sensitivity;
		yoffset *= sensitivity;

		tZero.x += xoffset / 800;
		tZero.y += yoffset / 600;

		tOne.x += xoffset / 800;
		tOne.y += yoffset / 600;

		tTwo.x += xoffset / 800;
		tTwo.y += yoffset / 600;
	}
	lastX = xpos;
	lastY = ypos;

}


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
	projection = glm::ortho(100.0f, width - 100.0f, 0.0f, (float)height, -1.0f, 1.0f);


}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

int WinMain( _In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd )
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

	glViewport(0, 0, 800, 600);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	{
		std::vector<int> layout = { 3, 2 };

		//Geometry cube(vertices, layout, indices);
		Equil lattice(150.0f, 5, 4);

		Shader shader("res/shaders/shader.sh");

		shader.bind();

		Texture tex("res/textures/im3.jpg", "texture1");

		shader.setTexture(tex);
		 
		glm::mat4 model = glm::mat4(0.1f);

		glm::mat4 view = glm::mat4(1.0f);
		//view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));



		projection = glm::ortho(100.0f, 800.0f, 0.0f, 600.0f, -1.0f, 1.0f);



		shader.setUniformMat4("model", model);
		shader.setUniformMat4("view", view);
		shader.setUniformMat4("projection", projection);

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

			shader.setUniformVec2("tOne", tOne);
			shader.setUniformVec2("tTwo", tTwo);
			shader.setUniformVec2("tZero", tZero);

			shader.setUniformMat4("projection", projection);

			glCall(glDrawElements(GL_TRIANGLES, 600, GL_UNSIGNED_INT, 0));

			lattice.unbind();
			shader.unbind();


			glfwSwapBuffers(window);
			glfwPollEvents();
		}

	}
	
	glfwTerminate();
	return 0;
}