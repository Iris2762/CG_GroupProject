#include "key.h"
#include <math.h>
#include <iostream>
void processInputs(GLFWwindow* window, std::shared_ptr<Camera> camera,double* x_begin,double* y_begin,float STEP_TIME,float VIEW_RADIUS){
	glm::vec3 position = camera->getPosition();
	glm::mat4 rotation = camera->getRotation();
	glm::vec3 direction = glm::vec3(rotation[2].x, rotation[2].y, rotation[2].z);
	glm::vec3 up = glm::vec3(rotation[1].x, rotation[1].y, rotation[1].z);
	glm::vec3 right = glm::vec3(rotation[0].x, rotation[0].y, rotation[0].z);
	
	if (glfwGetKey(window,GLFW_KEY_W)==GLFW_PRESS)
	{	
		if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		{
			position -= direction * (3*STEP_TIME);
		}
		position -= direction * STEP_TIME;

	}
	else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{	
		if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		{
			position += direction * (3 * STEP_TIME);
		}
		position += direction * STEP_TIME;
	}
	else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{	
		if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		{
			position -= right * (3 * STEP_TIME);
		}
		position -= right * STEP_TIME;
	}
	else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{	
		if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		{
			position += right * (3 * STEP_TIME);
		}
		position += right * STEP_TIME;
	}
	else if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
	{
		position += up * STEP_TIME;
	}
	camera->setPosition(position);
	double xpos, ypos,x_dif,y_dif;
	glfwGetCursorPos(window, &xpos, &ypos);
	x_dif = xpos - *x_begin;
	y_dif = ypos - *y_begin;
	rotation=glm::rotate(rotation, glm::radians(-180*float(asin(y_dif/ VIEW_RADIUS))), glm::vec3(1.0, 0.0, 0.0));
	rotation= glm::rotate(rotation, glm::radians(-180*float(asin(x_dif / VIEW_RADIUS))), glm::vec3(0.0, 1.0, 0.0));
	camera->setRotation(rotation);
	*x_begin = xpos;
	*y_begin = ypos;
}