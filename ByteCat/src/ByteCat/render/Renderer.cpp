#include "bcpch.h"
#include "byteCat/render/Renderer.h"
#include "byteCat/render/RenderAPI.h"
#include "byteCat/utils/Math.h"

namespace BC
{
	void Renderer::Init()
	{
		entities.reserve(ALLOCATE_PER_RESIZE);
		sceneData = std::make_unique<SceneData>();
		
		RenderAPI::Init();
	}

	void Renderer::Shutdown()
	{
		entities.clear();
		entities.shrink_to_fit();
	}

	void Renderer::OnWindowResize(unsigned width, unsigned height)
	{
		RenderAPI::SetViewport(0, 0, width, height);
	}

	void Renderer::BeginScene(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix)
	{
		sceneData->viewMatrix = viewMatrix;
		sceneData->projectionMatrix = projectionMatrix;
		
		drawCalls = 0;
		RenderAPI::Clear();
		RenderAPI::ClearColor(CLEAR_COLOR);
	}

	void Renderer::EndScene()
	{
		// TODO
		// Sorteer de entities
		// Render de entities efficient
		
		for (Entity& entity : entities)
		{
			entity.shader->bind();
			entity.shader->loadMatrix4("modelMatrix", entity.modelMatrix);
			entity.shader->loadMatrix4("projectionMatrix", sceneData->projectionMatrix);
			entity.shader->loadMatrix4("viewMatrix", sceneData->viewMatrix);
			entity.vao->bind();
			entity.shader->bindTextures();
			Render(entity.vao);
			entity.vao->unbind();
			entity.shader->unbind();
		}

		entities.clear();
		entities.shrink_to_fit();
		entities.reserve(ALLOCATE_PER_RESIZE);
	}

	void Renderer::Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vao, const glm::mat4& modelMatrix)
	{		
		if (entities.size() >= entities.capacity())
		{
			entities.reserve(entities.capacity() + ALLOCATE_PER_RESIZE);
		}

		entities.push_back({ shader, vao, modelMatrix });
	}

	void Renderer::Render(const std::shared_ptr<VertexArray>& vao)
	{
		++drawCalls;
		RenderAPI::Draw(vao);
	}
}
