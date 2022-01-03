#include "bcpch.h"
#include "byteCat/graphics/Shader.h"
#include "byteCat/graphics/RendererAPI.h"
#include "platform/openGL/OpenGLShader.h"

namespace BC
{
	Shader* Shader::Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		switch (RendererAPI::GetAPI())
		{
		case GraphicsAPI::None:		LOG_CRITICAL("No Graphics API selected!"); return nullptr;
		case GraphicsAPI::OpenGL:	return new Platform::OpenGLShader(name, vertexSrc, fragmentSrc);
		}

		LOG_CRITICAL("Unsupported Graphics API selected!");
		return nullptr;
	}
}
