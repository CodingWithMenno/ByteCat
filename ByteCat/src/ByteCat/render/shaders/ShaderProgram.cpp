#include "bcpch.h"
#include <GL/glew.h>
#include <iostream>
#include "byteCat/render/shaders/ShaderProgram.h"


namespace BC
{
	ShaderProgram::ShaderProgram(std::string& vertexShader, std::string& fragmentShader)
	{
		vertexShaderID = loadShader(vertexShader, GL_VERTEX_SHADER);
		fragmentShaderID = loadShader(fragmentShader, GL_FRAGMENT_SHADER);
		
		programID = glCreateProgram();
		glAttachShader(programID, vertexShaderID);
		glAttachShader(programID, fragmentShaderID);
	}

	void ShaderProgram::init()
	{
		bindAttributes();
		glLinkProgram(programID);
		glValidateProgram(programID);
	}

	void ShaderProgram::start() const
	{
		glUseProgram(programID);
	}

	void ShaderProgram::stop() const
	{
		glUseProgram(0);
	}

	void ShaderProgram::cleanUp() const
	{
		stop();
		glDetachShader(programID, vertexShaderID);
		glDetachShader(programID, fragmentShaderID);
		glDeleteShader(vertexShaderID);
		glDeleteShader(fragmentShaderID);
		glDeleteProgram(programID);
	}

	void ShaderProgram::bindAttribute(int attribute, std::string variableName) const
	{
		glBindAttribLocation(programID, attribute, variableName.c_str());
	}

	int ShaderProgram::loadShader(std::string& shader, int type)
	{
		const GLchar* shaderText = shader.c_str();
		const GLuint shaderID = glCreateShader(type);
		glShaderSource(shaderID, 1, &shaderText, NULL);
		glCompileShader(shaderID);

		GLint succes = 0;
		glGetShaderiv(shaderID, GL_COMPILE_STATUS, &succes);
		if (succes == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> errorLog(maxLength);
			glGetShaderInfoLog(shaderID, maxLength, &maxLength, &errorLog[0]);
			for (std::vector<GLchar>::const_iterator i = errorLog.begin(); i != errorLog.end(); ++i)
			{
				std::cout << *i;
			}
			std::cout << std::endl;
			std::cerr << "Could not compile shader" << std::endl;
			std::exit(-1);
		}

		return shaderID;
	}
}
