#include "shader/fairyShader.h"
#include <iostream>

bool FairyShader::is_built = false;
GLuint FairyShader::ID;

FairyShader::FairyShader() {
	if (!is_built) {
		ID = load_shader("../shader/fairyShader.vert", "../shader/fairyShader.frag");
		is_built = true;
	}
}

void FairyShader::render(glm::mat4 modelMat, glm::mat4 viewMat, glm::mat4 projMat, GLuint VAO, int num) const {
	glUseProgram(ID);
	glEnable(GL_PROGRAM_POINT_SIZE);
	glUniformMatrix4fv(glGetUniformLocation(ID, "model"), 1, GL_FALSE, glm::value_ptr(modelMat));
	glUniformMatrix4fv(glGetUniformLocation(ID, "view"), 1, GL_FALSE, glm::value_ptr(viewMat));
	glUniformMatrix4fv(glGetUniformLocation(ID, "proj"), 1, GL_FALSE, glm::value_ptr(projMat));
	glBindVertexArray(VAO);
	glDrawArrays(GL_POINTS, 0, num);
}