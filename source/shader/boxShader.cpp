#include "shader/boxShader.h"

bool boxShader::is_built = false;
GLuint boxShader::ID;

boxShader::boxShader() {
	if (!is_built) {
		ID = load_shader("../shader/SH/tex.vert", "../shader/SH/tex.frag");
		is_built = true;
	}
	////initialize light param
	//light_position = glm::vec4(3.0f, 3.0f, 3.0f, 0);//定位光源，在(0.0f, 0.0f, 0.0f)处
	//light_ambient = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	//light_diffuse = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	//light_specular = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	//cube_mat_ambient = glm::vec4(0.6f, 0.6f, 0.6f, 1.0f);
	//cube_mat_diffuse = glm::vec4(0.8f, 0.8f, 0.8f, 1.0f);
	//cube_mat_specular = glm::vec4(1, 1, 1, 1.0f);
	//cube_mat_emission = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
	//cube_mat_shininess = 80.0f;
}

void boxShader::render(Mesh& mesh, glm::mat4& modelMat, glm::mat4& viewMat, glm::mat4& projMat) const {

	glUseProgram(ID);
	glUniformMatrix4fv(glGetUniformLocation(ID, "model"), 1, GL_FALSE, glm::value_ptr(modelMat));
	glUniformMatrix4fv(glGetUniformLocation(ID, "view"), 1, GL_FALSE, glm::value_ptr(viewMat));
	glUniformMatrix4fv(glGetUniformLocation(ID, "proj"), 1, GL_FALSE, glm::value_ptr(projMat));
	//将光照参数传递给着色器f
	//glm::vec4 ambientProduct = light_ambient * cube_mat_ambient;
	//glm::vec4 diffuseProduct = light_diffuse * cube_mat_diffuse;
	//glm::vec4 specularProduct = light_specular * cube_mat_specular;
	//glUniform4fv(glGetUniformLocation(ID, "ambientProduct"), 1, glm::value_ptr(ambientProduct));
	//glUniform4fv(glGetUniformLocation(ID, "diffuseProduct"), 1, glm::value_ptr(diffuseProduct));
	//glUniform4fv(glGetUniformLocation(ID, "specualrProduct"), 1, glm::value_ptr(specularProduct));
	//glUniform4fv(glGetUniformLocation(ID, "LightPosition"), 1, glm::value_ptr(light_position));
	//glUniform1f(glGetUniformLocation(ID, "Shininess"), cube_mat_shininess);
	////设置pos
	//glUniform3fv(glGetUniformLocation(ID, "pos"), 1, glm::value_ptr(_pos));

	//增加纹理
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureID);
	GLuint tex_loc;
	tex_loc = glGetUniformLocation(ID, "texMap");
	glUniform1i(tex_loc, 0);

	glBindVertexArray(mesh.get_VAO());
	glDrawElements(GL_TRIANGLES, mesh.indices.size(), GL_UNSIGNED_INT, 0);
}