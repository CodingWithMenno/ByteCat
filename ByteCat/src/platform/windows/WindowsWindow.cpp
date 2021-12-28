#include "bcpch.h"
#include <GLFW/glfw3.h>
#include "platform/windows/WindowsWindow.h"

#include "byteCat/app/Application.h"
#include "byteCat/input/events/ApplicationEvent.h"
#include "byteCat/input/events/KeyEvent.h"
#include "byteCat/input/events/MouseEvent.h"

namespace BC
{
	namespace Platform
	{
		static GLFWwindow* nativeWindow;
		
		WindowsWindow::WindowsWindow(WindowSetting& setting)
		{
			LOG_INFO("Trying to create a Windows window");

			windowSetting = setting;

			if (!glfwInit())
			{
				LOG_CRITICAL("Could not initialize GLFW");
				std::exit(-1);
			}

			nativeWindow = glfwCreateWindow(windowSetting.width, windowSetting.height, windowSetting.title.c_str(), NULL, NULL);
			if (windowSetting.width == 0 || windowSetting.height == 0)
			{
				minimized = true;
			}
			else
			{
				minimized = false;
			}

			if (!nativeWindow)
			{
				LOG_CRITICAL("Failed to create a Windows window");
				glfwTerminate();
				std::exit(-1);
			}

			LOG_INFO("Created a Windows window with title: {0}, width: {1}, height: {2} and vSync: {3}", windowSetting.title, windowSetting.width, windowSetting.height, windowSetting.vSync);

			context = GraphicsContext::Create(nativeWindow, GraphicsAPI::OpenGL);
			context->init();

			setVsync(windowSetting.vSync);

			glfwSetWindowSizeCallback(nativeWindow, [](GLFWwindow* window, int width, int height)
				{
					WindowResizeEvent event(width, height);
					Application::GetInstance().getWindow().getEventListener()->onEvent(event);
				});

			glfwSetWindowCloseCallback(nativeWindow, [](GLFWwindow* window)
				{
					WindowCloseEvent event;
					Application::GetInstance().getWindow().getEventListener()->onEvent(event);
				});

			glfwSetKeyCallback(nativeWindow, [](GLFWwindow* window, int key, int scancode, int action, int mods)
				{
					switch (action)
					{
					case GLFW_PRESS:
					{
						KeyPressedEvent event(static_cast<KeyCode>(key), false);
						Application::GetInstance().getWindow().getEventListener()->onEvent(event);
						break;
					}

					case GLFW_RELEASE:
					{
						KeyReleasedEvent event(static_cast<KeyCode>(key));
						Application::GetInstance().getWindow().getEventListener()->onEvent(event);
						break;
					}

					case GLFW_REPEAT:
					{
						KeyPressedEvent event(static_cast<KeyCode>(key), true);
						Application::GetInstance().getWindow().getEventListener()->onEvent(event);
						break;
					}
					}
				});

			glfwSetCharCallback(nativeWindow, [](GLFWwindow* window, unsigned int keycode)
				{
					KeyTypedEvent event(static_cast<KeyCode>(keycode));
					Application::GetInstance().getWindow().getEventListener()->onEvent(event);
				});

			glfwSetMouseButtonCallback(nativeWindow, [](GLFWwindow* window, int button, int action, int mods)
				{
					switch (action)
					{
					case GLFW_PRESS:
					{
						MouseButtonPressedEvent event(static_cast<MouseCode>(button));
						Application::GetInstance().getWindow().getEventListener()->onEvent(event);
						break;
					}
					case GLFW_RELEASE:
					{
						MouseButtonReleasedEvent event(static_cast<MouseCode>(button));
						Application::GetInstance().getWindow().getEventListener()->onEvent(event);
						break;
					}
					}
				});

			glfwSetScrollCallback(nativeWindow, [](GLFWwindow* window, double xOffset, double yOffset)
				{
					MouseScrolledEvent event((float)xOffset, (float)yOffset);
					Application::GetInstance().getWindow().getEventListener()->onEvent(event);
				});

			glfwSetCursorPosCallback(nativeWindow, [](GLFWwindow* window, double xPos, double yPos)
				{
					MouseMovedEvent event((float)xPos, (float)yPos);
					Application::GetInstance().getWindow().getEventListener()->onEvent(event);
				});
		}

		void WindowsWindow::update() const
		{
			glfwPollEvents();
			context->swapBuffers();
		}

		void WindowsWindow::shutdown() const
		{
			delete context;
			glfwDestroyWindow(nativeWindow);
			glfwTerminate();
		}

		void WindowsWindow::resize(unsigned int width, unsigned int height)
		{
			windowSetting.width = width;
			windowSetting.height = height;

			if (width == 0 || height == 0)
			{
				minimized = true;
			}
			else
			{
				minimized = false;
			}
		}

		void WindowsWindow::setVsync(bool enabled)
		{
			windowSetting.vSync = enabled;
			
			if (enabled)
			{
				glfwSwapInterval(1);
			}
			else
			{
				glfwSwapInterval(0);
			}
		}

		void* WindowsWindow::getNativeWindow() const
		{
			return (void*) nativeWindow;
		}
	}
}
