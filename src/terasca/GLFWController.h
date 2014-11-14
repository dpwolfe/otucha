#pragma once

#include "Controller.h"

#include <GLFW/glfw3.h>

class GLFWController : public Controller
{
public:
	GLFWController(const std::string& windowTitle);
	virtual ~GLFWController();

protected:
	void reportWindowInterfaceVersion(std::ostream& os) const;
};