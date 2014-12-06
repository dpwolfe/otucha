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
	glfwSetKeyCallback(_window, keyboardCB);
	glfwSetMouseButtonCallback(_window, mouseButtonCB);
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

void GLFWController::keyboardCB(GLFWwindow* window, int key, int scanCode, int action, int mods)
{
	const unsigned char ESC = 27;
	if (_instance != nullptr)
	{
		GLFWController* controller = dynamic_cast<GLFWController*>(_instance);
		if (key == GLFW_KEY_ESCAPE)
		{
			controller->handleAsciiChar(ESC, controller->lastPixelPosX, controller->lastPixelPosY);
		}
	}
}

void GLFWController::mouseButtonCB(GLFWwindow*, int button, int action, int mods)
{
	if (_instance != nullptr)
	{
		Controller::MouseButton mButton;
		if (button == GLFW_MOUSE_BUTTON_LEFT)
		{
			mButton = Controller::LEFT_BUTTON;
		}
		else if (button == GLFW_MOUSE_BUTTON_RIGHT)
		{
			mButton = Controller::RIGHT_BUTTON;
		}
		else
		{
			mButton = Controller::MIDDLE_BUTTON;
		}

		bool isPressed = (action == GLFW_PRESS);
		GLFWController* controller = dynamic_cast<GLFWController*>(_instance);
		controller->handleMouseButton(mButton, isPressed, controller->lastPixelPosX, controller->lastPixelPosY, mapMods(mods));
	}
}

int GLFWController::mapMods(int glfwMods)
{
	int controllerMods = 0;
	if ((glfwMods & GLFW_MOD_ALT) != 0)
	{
		controllerMods |= ModifierBit::ALT;
	}
	if ((glfwMods & GLFW_MOD_CONTROL) != 0)
	{
		controllerMods |= ModifierBit::CONTROL;
	}
	if ((glfwMods & GLFW_MOD_SHIFT) != 0)
	{
		controllerMods |= ModifierBit::SHIFT;
	}
	return controllerMods;
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