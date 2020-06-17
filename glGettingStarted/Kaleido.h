#pragma once

#include "utils/utils.h"
#include "Shader.h"
#include "Equil.h"
#include "Vendor/FastNoise.h"

#include "GLFW/glfw3.h"

class Kaleido
{

public:
	float b = 0.5f;
	glm::vec2 tZero = glm::vec2(0.0f, 0.0f);
	glm::vec2 tOne = glm::vec2(b, 0.0f);
	glm::vec2 tTwo = glm::vec2(b / 2, b * sin(-30));
	float rot = 0;
	glm::mat4 projection;
	float zoomLevel = 1.0f;
	bool firstMouse = true;
	float lastX = 400, lastY = 300;
	std::string texPath = "res/textures/im.jpg";
	bool setTex = false;
	bool play = false;

	float m_height;
	float m_width;

	Shader shader;
	Equil lattice;
	FastNoise noise;

	float nose = 0.0f;
	int n = 0;


	Kaleido() {};
	void init(int height, int width);
	void draw();


	void framebuffer_size_callback(int width, int height);
	void key_callback(int key, int scancode, int action, int mods);
	void drop_callback(int path_count, const char* paths[]);
	void scroll_callback(double xoffset, double yoffset);
	void mouse_callback(GLFWwindow* window, double xpos, double ypos);
	glm::vec2 scaleVec2(glm::vec2 tVec, float offset);
	glm::vec2 rotateVec2(glm::vec2 tVec, float offset);

	
};

