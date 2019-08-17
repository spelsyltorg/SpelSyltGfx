#pragma once
#include "OpenGL.h"
#include <string>
#include <unordered_set>
#include <unordered_map>

namespace SSGFX
{
	class CTexture;

	class CShader
	{
	public:

		enum class EShaderType
		{
			Vertex,
			Geometry,
			Fragment
		};

		CShader();
		~CShader();

		bool Load(EShaderType Type, void* Data, size_t DataSize);
		bool Load(EShaderType Type, const std::string& FilePath);

		bool Link();

		void Bind();

		void SetUniform(const std::string& Name, float Value);
		void SetUniform(const std::string& Name, int Value);
		void SetUniform(const std::string& Name, bool Value);
		void SetUniform(const std::string& Name, const CTexture& Texture);

	private:
		unsigned int ProgramID;
		bool HasLinked = false;

		std::unordered_set<int> Shaders;
		std::unordered_map<std::string, int> Samplers;
	};
}