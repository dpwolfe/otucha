#pragma once

#include <string>

class ShaderProgram
{
public:
	ShaderProgram(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
	virtual ~ShaderProgram();

	int getId() const { return _id; }

private:
	int _id;
};