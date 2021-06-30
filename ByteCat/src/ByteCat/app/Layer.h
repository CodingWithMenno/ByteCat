#pragma once

#include "byteCat/Core.h"
#include "byteCat/input/events/Event.h"

namespace BC
{
	class BYTECAT_API Layer
	{
	private:
		std::string name;
		
	public:
		Layer(std::string name): name(name) {}
		virtual ~Layer() = default;

		virtual void onAttach() {}
		virtual void onDetach() {}
		virtual void onUpdate() {}
		virtual void onEvent(Event& event) {}

		std::string getName() const { return name; }
	};
}