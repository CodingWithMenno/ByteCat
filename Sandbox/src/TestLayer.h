#pragma once
#include <ByteCat.h>

#include "CameraBehaviour.h"

using namespace BC;

class TestLayer : public Layer
{	
public:
	TestLayer() : Layer("UserLayer")
	{
		// Maak een nieuwe scene
			auto scene = SceneManager::CreateScene("TestScene");
			scene->registerDefaultSystems();
			SceneManager::ActivateScene(scene);

			auto ecsCoordinator = scene->getEcsCoordinator();

		
		// Maak een shader
			const char* vertexSource = R"(
				#version 330 core

				layout (location = 0) in vec3 vertexPos;
				layout (location = 1) in vec2 texCoord;

				out vec2 passTexCoord;
			
				uniform mat4 modelMatrix;
				uniform mat4 viewMatrix;
				uniform mat4 projectionMatrix;
			
				void main()
				{		
					passTexCoord = texCoord;
					gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(vertexPos, 1.0);
				}
			)";

			const char* fragmentSource = R"(
				#version 330 core

				in vec2 passTexCoord;
			
				out vec4 FragColor;

				uniform sampler2D texture1;
				uniform sampler2D texture2;
			
				void main()
				{		
					FragColor = mix(texture(texture1, passTexCoord), texture(texture2, passTexCoord), 0.5);
				}
			)";

			auto shader = Shader::Create("Test", vertexSource, fragmentSource);
			shader->setTextureSlots({ "texture1", "texture2" });


		// Maak een vao met data
			float data[] = {
			    // Vertex positions		Texture Coords
				-0.5f, -0.5f, 0.0f,		0.0f, 0.0f,
				 0.5f, -0.5f, 0.0f,		1.0f, 0.0f,
				 0.0f,  0.5f, 0.0f,		0.5f, 1.0f
			};

			unsigned int indices[] = {
				0, 1, 2
			};

			auto vao = VertexArray::Create();

			auto ebo = IndexBuffer::Create(indices, sizeof(indices));
			vao->setIndexBuffer(ebo);

			auto vbo = VertexBuffer::Create(data, sizeof(data));
			BufferLayout layout = { { ShaderDataType::Float3, "vertexPos" }, {ShaderDataType::Float2, "texCoord"} };
			vbo->setLayout(layout);
			vao->addVertexBuffer(vbo);

		// Maak een entity en voeg components toe
			auto texture = Texture2D::Create("turtle.jpg", 0.5);
			auto texture2 = Texture2D::Create("wall.jpg", 0.5);

			auto entity = ecsCoordinator->createEntity("Test Entity");
			ecsCoordinator->addComponent<Transform>(entity, { glm::vec3(0, 0, 2), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1) });
			ecsCoordinator->addComponent<Mesh>(entity, { vao });
			ecsCoordinator->addComponent<Material>(entity, { shader, { texture, texture2} });

			auto camera = ecsCoordinator->createEntity("Camera");
			ecsCoordinator->addComponent<Transform>(camera, { glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1) });
			ecsCoordinator->setBehaviour<CameraBehaviour>(camera);
	}

	void onUpdate() override
	{

	}

	void onRender() override
	{
		
	}

	void onEvent(Event& event) override
	{
		if (KeyPressedEvent* keyEvent = dynamic_cast<KeyPressedEvent*>(&event); keyEvent != nullptr)
		{
			if (keyEvent->getKeyCode() == KeyCode::Escape)
			{
				static bool captured = true;
				Application::GetInstance().getWindow().captureMouse(captured);
				captured = !captured;

				Input::GetMouseVelocity();
			}
		}
	}
};