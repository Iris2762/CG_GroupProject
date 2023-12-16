#include "shader/shader.h"
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <direct.h>
#include <memory>

GLuint load_shader(const std::string& vertexPath, const std::string& fragmentPath)
{
	GLuint ID;
	//Get Shader Source
	//----------------------------------------------------------------------
	//define
	std::string fragmentShaderSource;
	std::string vertexShaderSource;
	std::ifstream vertexShaderFile;
	std::ifstream fragmentShaderFile;
	//allow to throw errorr
	vertexShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fragmentShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	char buf[512];
	getcwd(buf, 512);
	printf("%s", buf);
	try
	{
		//open file
		vertexShaderFile.open(vertexPath);
		fragmentShaderFile.open(fragmentPath);
		std::stringstream vertexShaderStream, fragmentShaderStream;
		//read file
		vertexShaderStream << vertexShaderFile.rdbuf();
		fragmentShaderStream << fragmentShaderFile.rdbuf();
		//close file
		vertexShaderFile.close();
		fragmentShaderFile.close();
		//sstream to string
		vertexShaderSource = vertexShaderStream.str();
		fragmentShaderSource = fragmentShaderStream.str();
	}
	catch (std::ifstream::failure &error)
	{
		std::cerr << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ" << std::endl;
		return 0;
	}
	const char* cVertexShaderSource = vertexShaderSource.c_str();
	const char* cFragmentShaderSource = fragmentShaderSource.c_str();
	//Complie Shader
	//---------------------------------------------------------------------
	//define
	unsigned int vertexShaderID, fragmentShaderID;
	int result;
	char infoLog[512];
	//vertex shader
	vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShaderID, 1, &cVertexShaderSource, NULL);
	glCompileShader(vertexShaderID);
	//print error information if error occured
	glGetShaderiv(vertexShaderID, GL_COMPILE_STATUS, &result);
	if (result != GL_TRUE)
	{
		glGetShaderInfoLog(vertexShaderID, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED" << std::endl;
		std::cout << "Source:" << std::endl;
		std::cout << cVertexShaderSource << std::endl;
		std::cout << "Error:" << std::endl;
		std::cout << infoLog;
		return 0;
	}
	//fragment shader
	fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShaderID, 1, &cFragmentShaderSource, NULL);
	glCompileShader(fragmentShaderID);
	//print error information if error occured
	glGetShaderiv(fragmentShaderID, GL_COMPILE_STATUS, &result);
	if (result != GL_TRUE)
	{
		glGetShaderInfoLog(fragmentShaderID, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << std::endl;
		std::cout << "Source:" << std::endl;
		std::cout << cFragmentShaderSource << std::endl;
		std::cout << "Error:" << std::endl;
		std::cout << infoLog;
		return 0;
	}
	//Link Shader
	//-------------------------------------------------------------------------
	ID = glCreateProgram();
	glAttachShader(ID, vertexShaderID);
	glAttachShader(ID, fragmentShaderID);
	glLinkProgram(ID);
	glGetProgramiv(ID, GL_LINK_STATUS, &result);
	if (result != GL_TRUE)
	{
		glGetProgramInfoLog(ID, 512, NULL, infoLog);
		std::cout << "ERROR:SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
		return 0;
	}
	//Delete Shader
	//------------------------------------------------------------------------
	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);
	return ID;
}