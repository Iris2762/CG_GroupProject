#include "model/fairy.h"

Fairy::Fairy() {
	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &VAO);
}

Fairy::~Fairy() {
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}

void Fairy::update()
{
	std::vector<float> data(pos.size() * 3);
	for (int i = 0; i < pos.size(); ++i) {
		data[3 * i] = pos[i][0];
		data[3 * i + 1] = pos[i][1];
		data[3 * i + 2] = pos[i][2];
	}
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * data.size(), data.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Fairy::render(glm::mat4 viewMat, glm::mat4 projMat)
{
	auto modelMat = getTransMat();
	_shader.render(modelMat, viewMat, projMat, VAO, pos.size());
}