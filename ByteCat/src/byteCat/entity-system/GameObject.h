#pragma once
#include <vector>
#include "glm/mat4x4.hpp"
#include "glm/vec3.hpp"
#include "byteCat/render/vertex-object/VertexArray.h"
#include "byteCat/render/shaders/Shader.h"

namespace BC
{
	class GameObject;

	// This struct holds all the information about an entity
	struct Transform
	{
		glm::vec3 position;
		glm::vec3 rotation;
		glm::vec3 scale;

		Transform(): position({0, 0, 0}), rotation({ 0, 0, 0 }), scale({ 1, 1, 1 }) {}
		Transform(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale): position(position), rotation(rotation), scale(scale) {}
	};

	
	// This class is used by the game objects as components of that object
	class ObjectComponent
	{
	private:		
		friend class GameObject;
	
	protected:
		GameObject* gameObject;
	
	public:
		ObjectComponent() = default;
		virtual ~ObjectComponent() = default;
		
		// Gets called when attached to a GameObject
		virtual void onAttach() {}
		// Gets called every frame
		virtual void onUpdate() {}
		// Gets called when the component gets removed from the GameObject
		virtual void onDetach() {}
	};

	// Use this class to make custom render components for the gameobject
	class RenderComponent: public ObjectComponent
	{
	private:
		friend class Renderer;

	public:
		virtual ~RenderComponent() = default;
	
	private:		
		// Gets called before rendering the GameObject (load the modelMatrix and bind the textures to the shader)
		virtual void prepareRender(glm::mat4& viewMatrix, glm::mat4& projectionMatrix) = 0;

		// Gets callend after rendering the GameObject
		virtual void finishRender() {}

		// Returns a VertexArray
		virtual std::shared_ptr<VertexArray>& getVao() = 0;
	};
	

	/*
	 * Class GameObject:
	 *		This class represents a 3D/2D object in 3D/2D space.
	 */
	class GameObject
	{
	public:
		std::string name;
		
		bool isEnabled = true;

		Transform transform;

	protected:
		std::vector<ObjectComponent*> components;
	
	public:
		GameObject(std::string& name, Transform const& transform = Transform()): name(name), transform(transform) {}
		virtual ~GameObject();

		void update();

		void addComponent(ObjectComponent* component);
		void removeComponent(ObjectComponent* toRemove);
		
		// This function returns the ObjectComponent with the given ObjectComponent type
		template<class T>
		T* getComponent();

		// This function checks if the gameobject already has this component
		template<class T>
		bool hasComponent();

		// This function removes the ObjectComponent with the given ObjectComponent type
		template<class T>
		void removeComponent() { removeComponent(getComponent<T>()); }

		glm::mat4 getModelMatrix() const;
	};

	// --------------------------------------------------------------------------------------
	// --------------------- Template elaborations of GameObject ----------------------------
	
	template <class T>
	T* GameObject::getComponent()
	{
		for (ObjectComponent* component : components)
		{
			if (T* x = dynamic_cast<T*>(component))
			{
				return x;
			}
		}

		return nullptr;
	}

	template <class T>
	bool GameObject::hasComponent()
	{
		for (ObjectComponent* component : components)
		{
			if (T* x = dynamic_cast<T*>(component))
			{
				return true;
			}
		}

		return false;
	}
}