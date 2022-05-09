#pragma once
#include "byteCat/graphics/renderer/Renderer.h"

namespace BC
{
	namespace Graphics
	{
		/// <summary>
		/// This renderer is used to draw simple 2D geometry without much hassle.
		/// The Renderer still has to be initialized before you will be able to use this renderer!
		/// </summary>
		class Renderer2D
		{
		private:
			inline static bool s_isInit = false;
		
		public:
			static void Clear(const glm::vec4& color);
			static void SetColor(const glm::vec4& color);
			static void DrawRectangle(const glm::vec2& position, float rotation, const glm::vec2& scale);
			static void DrawImage(const glm::vec2& position, float rotation, const glm::vec2& scale, const std::shared_ptr<Texture2D>& texture);
		};
	}
}
