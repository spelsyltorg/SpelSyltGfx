#include "Shader.h"

#include "Texture.h"

#include <iostream>
#include <fstream>
#include <sstream>

SSGFX::CShader::CShader()
{
	ProgramID = glCreateProgram();
}

SSGFX::CShader::~CShader()
{
}

bool SSGFX::CShader::Load(EShaderType Type, void * Data, size_t DataSize)
{
	int type;
	switch (Type)
	{
	case EShaderType::Vertex:
		type = GL_VERTEX_SHADER;
		break;
	case EShaderType::Geometry:
		type = GL_GEOMETRY_SHADER;
		break;
	case EShaderType::Fragment:
		type = GL_FRAGMENT_SHADER;
		break;
	}

	const char* source;
	memcpy(&source, Data, DataSize);

	unsigned shader = glCreateShader(type);
	glShaderSource(shader, 1, &source, NULL);
	glCompileShader(shader);

	int success;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		char info[512];
		glGetShaderInfoLog(shader, 512, NULL, info);
		std::cout << "SHADER: Compiling error:\n" << info << std::endl;
		return false;
	}

	glAttachShader(ProgramID, shader);

	return true;
}

bool SSGFX::CShader::Load(EShaderType Type, const std::string & FilePath)
{
	std::ifstream stream(FilePath);
	std::stringstream buffer;
	buffer << stream.rdbuf();

	std::string data = buffer.str();
	const char* cstr = data.c_str();

	if (!buffer) {
		std::cout << "Could not find \"" << FilePath << "\"" << std::endl;
		return false;
	}

	return Load(Type, &cstr, sizeof(cstr));
}

bool SSGFX::CShader::Link()
{
	glLinkProgram(ProgramID);

	for (auto&& shader : Shaders) {
		glDeleteShader(shader);
	}
	Shaders.clear();

	int success;
	glGetProgramiv(ProgramID, GL_LINK_STATUS, &success);
	if (!success)
	{
		char info[512];
		glGetProgramInfoLog(ProgramID, 512, NULL, info);
		std::cout << "SHADER: Linking error:\n" << info << std::endl;
		return false;
	}

	HasLinked = true;

	return true;
}

void SSGFX::CShader::Bind()
{
	glUseProgram(ProgramID);
}

void SSGFX::CShader::SetUniform(const std::string & Name, float Value)
{
	int uniformLocation = glGetUniformLocation(ProgramID, Name.c_str());
	if (uniformLocation >= 0)
	{
		Bind();
		glUniform1f(uniformLocation, Value);
	}
}

void SSGFX::CShader::SetUniform(const std::string & Name, const CTexture & Texture)
{
	int uniformLocation = glGetUniformLocation(ProgramID, Name.c_str());
	if (uniformLocation >= 0)
	{
		int index = Samplers.size();
		if (Samplers.find(Name) == Samplers.end())
			Samplers[Name] = index;

		index = Samplers.at(Name);

		Bind();
		glUniform1i(uniformLocation, index);
		glActiveTexture(GL_TEXTURE0 + index);
		glBindTexture(GL_TEXTURE_2D, Texture.GetID());
	}
}
