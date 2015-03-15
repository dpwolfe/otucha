#include "DependencyContainer.hpp"

#include <iostream>

using namespace otucha;

std::shared_ptr<DependencyContainer> DependencyContainer::_singleton = nullptr;

DependencyContainer::DependencyContainer()
{
	_console = std::make_shared<warbler::Console>();
	_initializeFreeType();
}

std::shared_ptr<warbler::Console> DependencyContainer::getConsole()
{
	return _console;
}

std::shared_ptr<DependencyContainer> DependencyContainer::getSingleton()
{
	if (_singleton == nullptr)
	{
		_singleton = std::make_shared<DependencyContainer>();
	}
	return _singleton;
}

std::shared_ptr<FT_Library> DependencyContainer::getFreeType()
{
	return _freeType;
}

void DependencyContainer::_initializeFreeType()
{
	_freeType = std::make_shared<FT_Library>();
	FT_Error error = FT_Init_FreeType(&*_freeType);
	if (error)
	{
		std::cout << "Error occurred during FreeType initialization: " << error << std::endl;
	}
	else
	{
		std::cout << "FreeType initialized" << std::endl;
	}
}