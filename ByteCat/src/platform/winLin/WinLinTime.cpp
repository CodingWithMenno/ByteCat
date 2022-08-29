#ifdef BC_PLATFORM_PC
#include "bcpch.h"
#include "byteCat/app/Time.h"
#include "GLFW/glfw3.h"

namespace BC
{
	namespace App
	{
		void Time::onUpdate()
		{
			const double currentTime = glfwGetTime();
			static double lastFrameTime = 0;
			s_deltaTime = (currentTime - lastFrameTime);
			lastFrameTime = currentTime;
		}
	}
}

#endif