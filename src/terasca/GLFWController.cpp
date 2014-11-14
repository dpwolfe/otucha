#include "GLFWController.h"

GLFWController::GLFWController(const std::string& windowTitle)
{

}

GLFWController::~GLFWController()
{

}

void GLFWController::reportWindowInterfaceVersion(std::ostream& os) const
{
	os << "    GLFW: " << glfwGetVersionString() << std::endl;
}