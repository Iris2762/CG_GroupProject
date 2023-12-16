#include "helper.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_imag.h>
#include <string>
#include <iostream>
#include <windows.h>

//Initialize glfw and configre.
bool initGlfw()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    return true;
}

//Use for the function "glfwSetWindowSizeCallback(window, frameSizeCallback);".
void _frameSizeCallback(GLFWwindow* window, int width, int height)
{
	frameSizeCallback(window, width, height);
}

//Load all OpenGL function pointers.
bool loadOpengl()
{
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize glad!" << std::endl;
		return false;
	}
	return true;
}

//initialize glfw, create a window with its name and a basic frameSizeCallback
//, then load all OpenGL function pointers with glad.
GLFWwindow* createBasicWindow(const std::string& name)
{
	if (!initGlfw()) return NULL;
	GLFWwindow* window = glfwCreateWindow(2*SCREEN_WIDTH, 2*SCREEN_HEIGHT, name.c_str(), NULL, NULL);
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, _frameSizeCallback);
	if (!loadOpengl()) return NULL;
	return window;
}

//Simply set a color. If you just want to check an environment, use it.
void basicRenderLoop(GLFWwindow* window)
{
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.8f, 0.6f, 0.6f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(window);
		glfwPollEvents();

		Sleep(33);
	}
}

//Load an image and create a texture with it. 
unsigned int loadTexture(const std::string& name)
{
	//load data
	unsigned int ID;
	int width, height,nrChannels;
	unsigned char* data = stbi_load(name.c_str(), &width, &height, &nrChannels, 0);
	//define
	glGenTextures(1, &ID);
	glBindTexture(GL_TEXTURE_2D, ID);
	//configure
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//load and generate texture 
	if (data)
	{
		std::cout << nrChannels << std::endl;
		//如果图片的通道数和绑定的格式不匹配，则会造成显示的纹理出错。
		if (nrChannels < 4)
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		else glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);
	return ID;
}
unsigned int loadCubemap(std::vector<std::string> faces) {
	unsigned int textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

	int width, height, nrChannels;
	std::cout << "read cube texture\n";
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	for (unsigned int i = 0; i < faces.size(); i++) {
		unsigned char* data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
		if (data) {
			//如果图片的通道数和绑定的格式不匹配，则会造成显示的纹理出错。
			if (nrChannels < 4)
				glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			else	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
			std::cout << nrChannels << std::endl;
			//glGenerateMipmap(GL_TEXTURE_2D);
			stbi_image_free(data);
		}
		else {
			std::cout << "Cubemap texture failed to load at path: " << faces[i] << std::endl;
			stbi_image_free(data);
		}
	}

	return textureID;
}