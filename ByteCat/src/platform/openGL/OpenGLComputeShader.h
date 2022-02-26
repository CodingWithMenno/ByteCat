#pragma once
#include <string>
#include "byteCat/graphics/components/Shader.h"

namespace BC
{
	namespace Platform
	{
		class OpenGLComputeShader : public ComputeShader
		{
		private:
			std::string m_name;
			unsigned int m_programID;

		public:
			OpenGLComputeShader(const std::string& name, const std::string& computeSrc, bool isFilePath);
			~OpenGLComputeShader();

			void compute(unsigned numberOfGroupsX, unsigned numberOfGroupsY, unsigned numberOfGroupsZ) override;
			void wait() override;
			
			void setOutputTexture(std::shared_ptr<Texture> texture, unsigned int textureUnit) override;
			
			const std::string& getName() const override { return m_name; }

		private:
			unsigned int loadShader(const std::string& shader, int type) const;
		};
	}
}