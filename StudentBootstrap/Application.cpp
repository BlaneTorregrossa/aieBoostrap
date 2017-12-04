#include "Application.h"
#include "gl_core_4_4.h"
#include <GLFW\glfw3.h>


Application::Application()
{
}


Application::~Application()
{

}

void Application::run(const char * title, int width, int height, bool fullscreen)
{
	//GLFW function for initialization. if initialization fails terminates program
	if (glfwInit() == GL_FALSE)
	{
		return; // Terminate program
	}

	GLFWmonitor* monitor = (fullscreen) ? glfwGetPrimaryMonitor() : nullptr;
	m_window = glfwCreateWindow(width, height, title, monitor, nullptr); // Creates the application window

	glfwMakeContextCurrent(m_window); // Gives/Makes the context of m_window current for calling

	if (ogl_LoadFunctions() == ogl_LOAD_FAILED) //Load OpenGL functions and if it can't the program is terminated.
	{
		glfwDestroyWindow(m_window);
		glfwTerminate();
		return;
	}

	glEnable(GL_DEPTH_TEST);


	double prevTime = glfwGetTime(); // Sets prevTime to return the value of the GLFW timer
	double currTime = 0;
	double deltaTime = 0;
	startup();

	while (!m_check) // loop could be set better
	{
		currTime = glfwGetTime();  // Sets currTime to return the value of the GLFW timer
		deltaTime = currTime - prevTime;  // deltaTime set to equal the change of time between current time and the previous time
		prevTime = currTime; // Updates prevTime
		glClear(GL_COLOR_BUFFER_BIT || GL_DEPTH_BUFFER_BIT);
		glfwSwapBuffers(m_window); // Swaps the front and back buffers of the window
		glfwPollEvents(); // processes all events
		m_check = m_check || (glfwWindowShouldClose(m_window) == GLFW_TRUE);

	}
}

void Application::setBackgroundColors(float red, float green, float blue, float alpha)
{
	glClearColor(red, green, blue, alpha);
}

void Application::quit()
{
	m_check = true;
}

void Application::startup()
{
}

void Application::shutdown()
{
}

void Application::update(float)
{
}

void Application::draw()
{
}
