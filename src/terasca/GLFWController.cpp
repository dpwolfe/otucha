#include "GLFWController.h"

GLFWController::GLFWController(const std::string& windowTitle)
{

}

GLFWController::~GLFWController()
{

}

void GLFWController::run()
{
	establishInitialCallbacksForRC();
}

void GLFWController::reportWindowInterfaceVersion(std::ostream& os) const
{
	os << "    GLFW: " << glfwGetVersionString() << std::endl;
}

void GLFWController::establishInitialCallbacksForRC()
{
	glfwSetWindowRefreshCallback(_window, displayCB);
}

void GLFWController::displayCB(GLFWwindow* window)
{
	if (_instance != nullptr)
	{
		dynamic_cast<GLFWController*>(_instance)->handleDisplay();
	}
}

void GLFWController::handleDisplay()
{
	glfwMakeContextCurrent(_window);
	int width, height;
	glfwGetFramebufferSize(_window, &width, &height);
	glViewport(0, 0, width, height);
	glClear(glClearFlags);
	// draw the models
	for (std::vector<ModelView*>::iterator it = models.begin(); it < models.end(); it++)
	{
		(*it)->render();
	}

	glfwSwapBuffers(_window);

	checkForErrors(std::cout, "GLFWController::handleDisplay");
}