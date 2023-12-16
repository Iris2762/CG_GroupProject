#include "shader/meshShader.h"

bool MeshShader::is_built = false;
GLuint MeshShader::ID;

MeshShader::MeshShader() {
	if(!is_built) {
		ID = load_shader("../shader/SH/multi_tex_lightShader.vert", "../shader/SH/multi_tex_lightShader.frag");
		is_built = true;
	}
	//initialize light param
	light_position[0] = glm::vec4(10.0f, 0.0f, 0.0f, 0);//定位光源，在(0.0f, 0.0f, 0.0f)处
	light_position[1] = glm::vec4(0.0f, 5.0f, 0.0f, 0);
	light_position[2] = glm::vec4(-10.0f, 4.0f, 0.0f, 0);
	
	for (int i = 0; i < 3; i++) {
	light_ambient[i] = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	light_diffuse[i] = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	light_specular[i] = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	}
	cube_mat_ambient = glm::vec4(0.6f, 0.6f, 0.6f, 1.0f);
	cube_mat_diffuse = glm::vec4(0.8f, 0.8f, 0.8f, 1.0f);
	cube_mat_specular = glm::vec4(1, 1, 1, 1.0f);
	cube_mat_emission = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
	cube_mat_shininess = 80.0f;
}

void MeshShader::render(Mesh& mesh, glm::mat4& modelMat, glm::mat4& viewMat, glm::mat4& projMat, glm::vec3 _pos) const {

	glUseProgram(ID);
	glUniformMatrix4fv(glGetUniformLocation(ID, "model"), 1, GL_FALSE, glm::value_ptr(modelMat));
	glUniformMatrix4fv(glGetUniformLocation(ID, "view"), 1, GL_FALSE, glm::value_ptr(viewMat));
	glUniformMatrix4fv(glGetUniformLocation(ID, "proj"), 1, GL_FALSE, glm::value_ptr(projMat));
	//将光照参数传递给着色器f
	glm::vec4 ambientProduct[3];
	glm::vec4 diffuseProduct[3];
	glm::vec4 specularProduct[3];
	for (int i = 0; i < 3; i++) {
		ambientProduct[i] = light_ambient[i] * cube_mat_ambient;
		diffuseProduct[i] = light_diffuse[i] * cube_mat_diffuse;
		specularProduct[i] = light_specular[i] * cube_mat_specular;
		std::string str_i = std::to_string(i);
	}
	glUniform4fv(glGetUniformLocation(ID, "lights[0].ambientProduct"), 1, glm::value_ptr(ambientProduct[0]));
	glUniform4fv(glGetUniformLocation(ID, "lights[0].diffuseProduct"), 1, glm::value_ptr(diffuseProduct[0]));
	glUniform4fv(glGetUniformLocation(ID, "lights[0].specualrProduct"), 1, glm::value_ptr(specularProduct[0]));
	glUniform4fv(glGetUniformLocation(ID, "lights[0].LightPosition"), 1, glm::value_ptr(light_position[0]));
	glUniform1f(glGetUniformLocation(ID, "lights[0].Shininess"), cube_mat_shininess);

	glUniform4fv(glGetUniformLocation(ID, "lights[1].ambientProduct"), 1, glm::value_ptr(ambientProduct[1]));
	glUniform4fv(glGetUniformLocation(ID, "lights[1].diffuseProduct"), 1, glm::value_ptr(diffuseProduct[1]));
	glUniform4fv(glGetUniformLocation(ID, "lights[1].specualrProduct"), 1, glm::value_ptr(specularProduct[1]));
	glUniform4fv(glGetUniformLocation(ID, "lights[1].LightPosition"), 1, glm::value_ptr(light_position[1]));
	glUniform1f(glGetUniformLocation(ID, "lights[1].Shininess"), cube_mat_shininess);

	glUniform4fv(glGetUniformLocation(ID, "lights[2].ambientProduct"), 1, glm::value_ptr(ambientProduct[2]));
	glUniform4fv(glGetUniformLocation(ID, "lights[2].diffuseProduct"), 1, glm::value_ptr(diffuseProduct[2]));
	glUniform4fv(glGetUniformLocation(ID, "lights[2].specualrProduct"), 1, glm::value_ptr(specularProduct[2]));
	glUniform4fv(glGetUniformLocation(ID, "lights[2].LightPosition"), 1, glm::value_ptr(light_position[2]));
	glUniform1f(glGetUniformLocation(ID, "lights[2].Shininess"), cube_mat_shininess);
	//设置pos
	glUniform3fv(glGetUniformLocation(ID, "pos"), 1, glm::value_ptr(_pos));

	//增加纹理
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureID);
	GLuint tex_loc;
	tex_loc = glGetUniformLocation(ID, "texMap");
	glUniform1i(tex_loc, 0);

	glBindVertexArray(mesh.get_VAO());
	glDrawElements(GL_TRIANGLES, mesh.indices.size(), GL_UNSIGNED_INT, 0);
}
void MeshShader::setLightParam(std::string p_name,int index ,glm::vec4 v1, float v2) {
	//if set light_%,index must be set correctly
	if (p_name == "pos") {
		light_position[index] = v1;
	}
	else if (p_name == "ambient") {
		light_ambient[index] = v1;
	}
	else if (p_name == "diffuse") {
		light_diffuse[index] = v1;
	}
	else if (p_name == "specular") {
		light_specular[index] = v1;
	}
	else if (p_name == "mat_ambient")cube_mat_ambient = v1;
	else if (p_name == "mat_diffuse")cube_mat_diffuse = v1;
	else if (p_name == "mat_specular")cube_mat_specular = v1;
	else if (p_name == "mat_emission")cube_mat_emission = v1;
	else if (p_name == "mat_shininess") cube_mat_shininess = v2;

}

//difine boxshader

bool boxShader::is_built = false;
GLuint boxShader::ID;

boxShader::boxShader() {
	if (!is_built) {
		ID = load_shader("../shader/SH/texShader.vert", "../shader/SH/texShader.frag");
		is_built = true;
	}
	//initialize light param
}

void boxShader::render(Mesh& mesh, glm::mat4& viewMat, glm::mat4& projMat) const {
	glDepthFunc(GL_LEQUAL);
	glUseProgram(ID);
	
	//glUniformMatrix4fv(glGetUniformLocation(ID, "model"), 1, GL_FALSE, glm::value_ptr(modelMat));
	glm::mat4 view = glm::mat4(glm::mat3(viewMat));
	glUniformMatrix4fv(glGetUniformLocation(ID, "view"), 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(glGetUniformLocation(ID, "proj"), 1, GL_FALSE, glm::value_ptr(projMat));

	//增加纹理
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureID);
	GLuint tex_loc;
	tex_loc = glGetUniformLocation(ID, "skybox");
	glUniform1i(tex_loc, 0);

	glBindVertexArray(mesh.get_VAO());
	glDrawElements(GL_TRIANGLES, mesh.indices.size(), GL_UNSIGNED_INT, 0);
	glDepthFunc(GL_LESS);
}