#include "Kaleido.h"


void Kaleido::init(int height, int width)
{
	m_height = height;
	m_width = width;

	shader = Shader("res/shaders/shader.sh");
	lattice = Equil(150.0f, 5, 4);

	noise.SetNoiseType(FastNoise::Perlin);

	std::vector<int> layout = { 3, 2 };
	shader.bind();

	Texture tex("res/textures/im3.jpg", "texture1");
	shader.setTexture(tex);


	glm::mat4 model = glm::mat4(0.1f);

	glm::mat4 view = glm::mat4(1.0f);
	projection = glm::ortho(100.0f, 800.0f, 0.0f, 600.0f, -1.0f, 1.0f);



	shader.setUniformMat4("model", model);
	shader.setUniformMat4("view", view);
	shader.setUniformMat4("projection", projection);
}

void Kaleido::draw()
{
	if (play)
	{
		float nos = noise.GetNoise(nose + 42, nose + 2);
		float nos2 = noise.GetNoise(nose, nose + 138);

		if (n > 10)
		{
			tZero.x = nos;
			tZero.y = nos2;
			LOG << nos << "  " << nos2 << END;

			tOne.x = nos + b;
			tOne.y = nos2;

			tTwo.x = nos + b / 2;
			tTwo.y = nos2 + b * sin(-30);

			nose += 0.1f;
			n = 0;
		}
		else
		{
			n++;
		}
	}

	lattice.bind();
	shader.bind();

	if (setTex)
	{
		Texture t(texPath, "texture1");
		shader.setTexture(t);
		setTex = false;
	}

	shader.setUniformVec2("tOne", tOne);
	shader.setUniformVec2("tTwo", tTwo);
	shader.setUniformVec2("tZero", tZero);

	shader.setUniformMat4("projection", projection);

	glCall(glDrawElements(GL_TRIANGLES, 600, GL_UNSIGNED_INT, 0));

	lattice.unbind();
	shader.unbind();
}

void Kaleido::framebuffer_size_callback(int width, int height)
{
	projection = glm::ortho(100.0f, (width - 100.0f) * zoomLevel, 0.0f, (float)height * zoomLevel, -1.0f, 1.0f);
	m_width = width;
	m_height = height;
}

void Kaleido::key_callback(int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_P && action == GLFW_PRESS)
	{
		play = true;
	}

	if (key == GLFW_KEY_S && action == GLFW_PRESS)
	{
		play = false;
	}
}

void Kaleido::drop_callback(int path_count, const char* paths[])
{
	setTex = true;
	texPath = std::string(paths[0]);
}

void Kaleido::scroll_callback(double xoffset, double yoffset)
{
	float of = yoffset;
	tZero = scaleVec2(tZero, of);
	tOne = scaleVec2(tOne, of);
	tTwo = scaleVec2(tTwo, of);
}

void Kaleido::mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	int pressed = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
	int rPressed = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT);
	int mPressed = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_MIDDLE);

	if (rPressed == GLFW_PRESS)
	{
		float yof = lastY - ypos;

		tZero = rotateVec2(tZero, yof);
		tOne = rotateVec2(tOne, yof);
		tTwo = rotateVec2(tTwo, yof);
	}

	if (mPressed)
	{
		if (zoomLevel > 1)
		{
			zoomLevel -= abs((lastY - ypos) / m_height);
		}
		if (zoomLevel < .5)
		{
			zoomLevel += abs((lastY - ypos) / m_height);
		}

		zoomLevel += (lastY - ypos) / m_height;


		projection = glm::ortho(100.0f, m_width * zoomLevel, 0.0f, m_height * zoomLevel, -1.0f, 1.0f);

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

glm::vec2 Kaleido::scaleVec2(glm::vec2 tVec, float offset)
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

	s = glm::translate(s, -pivot) * glm::scale(s, glm::vec3(mul, mul, 1.0f)) * glm::translate(s, pivot);


	tm4 = s * tm4;

	glm::vec2 tm2(tm4);

	return tm2;
}

glm::vec2 Kaleido::rotateVec2(glm::vec2 tVec, float offset)
{
	glm::mat4 s = glm::mat4(1.0f);
	glm::vec4 tm4(tVec, 1.0f, 1.0f);
	glm::vec3 pivot((tZero + tOne + tTwo) / 3.0f, 1.0f);

	s = glm::translate(s, -pivot) * glm::rotate(s, glm::radians(offset * 0.1f), glm::vec3(0.0f, 0.0f, 1.0f)) * glm::translate(s, pivot);


	tm4 = s * tm4;

	glm::vec2 tm2(tm4);

	return tm2;
}
