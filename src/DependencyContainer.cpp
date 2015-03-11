#include "DependencyContainer.hpp"

using namespace otucha;

std::shared_ptr<DependencyContainer> DependencyContainer::_singleton = nullptr;

DependencyContainer::DependencyContainer()
{
	_console = std::make_shared<warbler::Console>();
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