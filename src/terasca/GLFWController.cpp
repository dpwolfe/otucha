#include "GLFWController.hpp"
#ifdef __EMSCRIPTEN__
    #include "emscripten.h"
    #include "html5.h"
#endif

bool GLFWController::glfwInitialized = false;

GLFWController::GLFWController(const std::string& windowTitle, int rcFlags) :
	lastPixelPosX(0), lastPixelPosY(0)
{
	if (!glfwInitialized)
	{
		glfwInit();
		glfwInitialized = true;
	}

	createWindow(windowTitle, rcFlags);
}

GLFWController::~GLFWController()
{

}

void one_iter() {
	GLFWController::runLoopIter();
}

void GLFWController::run()
{
	establishInitialCallbacksForRC();
#ifdef __EMSCRIPTEN__
	// void emscripten_set_main_loop(em_callback_func func, int fps, int simulate_infinite_loop);
	emscripten_set_main_loop(one_iter, 0, 1);
#else
	while (!glfwWindowShouldClose(_window))
	{
		one_iter();
	}
#endif
	glfwDestroyWindow(_window);
	_window = nullptr;
}

void GLFWController::runLoopIter()
{
	if (_instance != nullptr)
	{
		GLFWController* controller = dynamic_cast<GLFWController*>(_instance);
		controller->handleDisplay();
		glfwWaitEvents();
	}
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
	glfwSetScrollCallback(_window, scrollCB);
	glfwSetCursorPosCallback(_window, cursorPosCB);
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
		MouseButton mButton;
		if (button == GLFW_MOUSE_BUTTON_LEFT)
		{
			mButton = LEFT_BUTTON;
		}
		else if (button == GLFW_MOUSE_BUTTON_RIGHT)
		{
			mButton = RIGHT_BUTTON;
		}
		else
		{
			mButton = MIDDLE_BUTTON;
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
		controllerMods |= ALT;
	}
	if ((glfwMods & GLFW_MOD_CONTROL) != 0)
	{
		controllerMods |= CONTROL;
	}
	if ((glfwMods & GLFW_MOD_SHIFT) != 0)
	{
		controllerMods |= SHIFT;
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

void GLFWController::scrollCB(GLFWwindow* window, double xOffset, double yOffset)
{
	dynamic_cast<GLFWController*>(_instance)->handleMouseScroll(xOffset, yOffset);
}

void GLFWController::cursorPosCB(GLFWwindow* window, double x, double y)
{
	if (_instance != nullptr)
	{
		GLFWController* controller = dynamic_cast<GLFWController*>(_instance);
		controller->lastPixelPosX = static_cast<int>(x + 0.5);
		controller->lastPixelPosY = static_cast<int>(y + 0.5);
		controller->handleMousePosition(controller->lastPixelPosX, controller->lastPixelPosY);
	}
}

void GLFWController::createWindow(const std::string& windowTitle, int rcFlags)
{
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#ifdef __APPLE_CC__
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#else
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
#endif
	
	if ((rcFlags & DEPTH) == 0)
	{
		glfwWindowHint(GLFW_DEPTH_BITS, 0);
	}
	else
	{
		glfwWindowHint(GLFW_DEPTH_BITS, 24);
	}
	setClearFlags(rcFlags);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	int minor = 8;
	_window = nullptr;
	while ((_window == nullptr) && (minor > 0))
	{
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor);
		_window = glfwCreateWindow(initialWindowWidth, initialWindowHeight, windowTitle.c_str(), nullptr, nullptr);
		minor--;
	}
	if (_window == nullptr)
	{
		std::cerr << "Unable to create a 4.x rendering context!" << std::endl;
		glfwTerminate();
		glfwInitialized = false;
	}

	glfwMakeContextCurrent(_window);

	// set glewExperimental to true in order to avoid a GL_INVALID_ENUM error from calling glewInit
	// https://www.opengl.org/wiki/OpenGL_Loading_Library, this error can still occur
	glewExperimental = GL_TRUE;
	GLenum err = glewInit();
	// clearing the error code caused by glew that still happens even with glewExperimental
	glGetError();
	if (GLEW_OK != err)
	{
		std::cerr << "GLEW failed to initialize 0x" << std::hex << err << std::endl;
	}
	else
	{
		std::cout << "GLEW initialized with version " << glewGetString(GLEW_VERSION) << std::endl;
	}

	if ((rcFlags & DEPTH) != 0)
	{
		glEnable(GL_DEPTH_TEST);
	}
}
