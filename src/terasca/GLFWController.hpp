#pragma once

#include "Controller.hpp"

#include <GL/glew.h>

#ifdef __APPLE_CC__
#define GLFW_INCLUDE_GLCOREARB
#endif
#include <GLFW/glfw3.h>

class GLFWController : public Controller
{
public:
	GLFWController(const std::string& windowTitle, int rcFlags);
	virtual ~GLFWController();

	void run();

	static void runLoopIter();

protected:
	void reportWindowInterfaceVersion(std::ostream& os) const;
	void establishInitialCallbacksForRC();
	virtual void handleDisplay();

private:
	GLFWwindow* _window;
	int lastPixelPosX, lastPixelPosY;

	void createWindow(const std::string& windowTitle, int rcFlags);

	static bool glfwInitialized;

	static void displayCB(GLFWwindow* window);
	static void reshapeCB(GLFWwindow* window, int width, int height);
	static void charCB(GLFWwindow* window, unsigned int theChar);
	static void keyboardCB(GLFWwindow* window, int key, int scanCode, int action, int mods);
	static void mouseButtonCB(GLFWwindow* window, int button, int action, int mods);
	static int mapMods(int glfwMods);
	static void scrollCB(GLFWwindow* window, double xOffset, double yOffset);
	static void cursorPosCB(GLFWwindow* window, double x, double y);
};
