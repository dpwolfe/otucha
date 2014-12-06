#include "GLFWController.h"

GLFWController::GLFWController(const std::string& windowTitle) :
	lastPixelPosX(0), lastPixelPosY(0)
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
	glfwSetWindowSizeCallback(_window, reshapeCB);
	glfwSetCharCallback(_window, charCB);
}

void GLFWController::displayCB(GLFWwindow* window)
{
	if (_instance != nullptr)
	{
		dynamic_cast<GLFWController*>(_instance)->handleDisplay();
	}
}

void GLFWController::reshapeCB(GLFWwindow* window, int width, int height)
{
	dynamic_cast<GLFWController*>(_instance)->handleReshape(width, height);
}

void GLFWController::charCB(GLFWwindow* window, unsigned int theChar)
{
	if (theChar < 128)
	{
		GLFWController* controller = dynamic_cast<GLFWController*>(_instance);
		controller->handleAsciiChar(static_cast<unsigned char>(theChar), controller->lastPixelPosX, controller->lastPixelPosY);
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