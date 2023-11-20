// LearnRenderingEngine.cpp : Defines the entry point for the application.

#include "LearnRenderingEngine.h"
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "glm.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "imgui.h"
#include <cstdio>

const float triangleArray[6] =
{
	-.6f, -.4f,
	.6f, -.4f,
	0.f, .6f
};
int main(int argc, char** argv)
{
	if (!glfwInit())
		exit(-9999);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
	GLFWwindow* window = glfwCreateWindow(800, 600, "Simple example", nullptr, nullptr);
	glfwSetKeyCallback(
		window,
		[](GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
				glfwSetWindowShouldClose(window, GLFW_TRUE);
		}
	);
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);
	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		fprintf(stderr, "ERROR INTIALIZING GLEW");
	}
	unsigned int VBO, VAO;
	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangleArray), triangleArray, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),
		(void*)0);
	glEnableVertexAttribArray(0);
	// INICIALIZAMOS IMGUI
	// IMGUI_CHECKVERSION();
	// ImGui::CreateContext();
	// ESTABLECEMOS LA PATAFORMA Y RENDER
	// ImGui_ImplGlfw_InitForOpenGL(window, true);
	// ImGui_ImplOpenGL3_Init("#version 460");

	// LOAD LOGO
	int w, h, comp;
	unsigned char* texture_data = stbi_load("C:\\dev\\LearnRenderingEngine\\out\\resources\\textures\\logo.png", &w, &h, &comp, 0);
	unsigned int texture;
	if(texture_data)
	{
		printf("image loaded:  %p", texture_data);
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE,
			texture_data);
		stbi_image_free(texture_data);
	}
	while(!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(.0f, 0.f, 1.0f, 1.0f);
		glBindTexture(GL_TEXTURE_2D, texture);
		glm::vec2 position{1.f};
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 4);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}
