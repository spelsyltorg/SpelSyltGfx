#include "Shader.h"

#include "Texture.h"
#include <SpelSyltCommonLibrary/Graphics/Public/Transformable2D.h>

#pragma comment(lib, "SpelSyltCommonLibrary_Debug")

#include <iostream>
#include <fstream>
#include <sstream>

SSGFX::CShader::CShader() :
	ProgramID(0)
{
}

SSGFX::CShader::~CShader()
{
}

bool SSGFX::CShader::Load(EShaderType Type, const char* InShaderFileData, size_t DataSize)
{
	if (!ProgramID)
		ProgramID = glCreateProgram();

	int type = -1;
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

	const GLchar* DataGlPtr = reinterpret_cast<const GLchar*>(InShaderFileData);
	const GLint* DataLenPtr = reinterpret_cast<GLint*>(&DataSize);

	unsigned shader = glCreateShader(type);
	glShaderSource(shader, 1, &DataGlPtr, DataLenPtr);
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

	return Load(Type, cstr, data.size());
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

void SSGFX::CShader::SetUniform(const std::string & Name, CL::CTransformable2D& Transform)
{
	int uniformLocation = glGetUniformLocation(ProgramID, Name.c_str());
	if (uniformLocation >= 0)
	{
		Bind();
		glUniformMatrix3fv(uniformLocation, 1, false, &Transform.GetMatrix().M11());
	}
}
