#ifndef HELPER_H
#define HELPER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>
#include <functional>
#include<vector>
const int SCREEN_WIDTH = 600;
const int SCREEN_HEIGHT = 600;

extern std::function<void(GLFWwindow*, int, int)> frameSizeCallback;

//Initialize glfw and configre.
bool initGlfw();

//Load all OpenGL function pointers.
bool loadOpengl();

//initialize glfw, create a window with its name and a basic frameSizeCallback
//, then load all OpenGL function pointers with glad.
GLFWwindow* createBasicWindow(const std::string& name);

//Simply set a color. If you just want to check an environment, use it.
void basicRenderLoop(GLFWwindow* window);

//Load an image and create a texture with it. return ID.
unsigned int loadTexture(const std::string& name);
unsigned int loadCubemap(std::vector<std::string> faces);
#endif