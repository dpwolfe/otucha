#pragma once

#include "Controller.h"

#include <GLFW/glfw3.h>

class GLFWController : public Controller
{
public:
	GLFWController(const std::string& windowTitle);
	virtual ~GLFWController();

	void run();

protected:
	void reportWindowInterfaceVersion(std::ostream& os) const;
	void establishInitialCallbacksForRC();
	virtual void handleDisplay();

private:
	GLFWwindow* _window;

	static void displayCB(GLFWwindow* window);
	static void reshapeCB(GLFWwindow* window, int width, int height);
};