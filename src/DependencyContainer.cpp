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

std::shared_ptr<FT_Face> DependencyContainer::getFontFace()
{
	if (_fontFace == nullptr)
	{
		_loadFontFace();
	}
	return _fontFace;
}

std::string DependencyContainer::getAppDir()
{
	return _appDir;
}

void DependencyContainer::setAppDir(const std::string &appDir)
{
	_appDir = appDir;
}

void DependencyContainer::_initializeFreeType()
{
	_freeType = std::make_shared<FT_Library>();
	FT_Error error = FT_Init_FreeType(&*_freeType);
	if (error != FT_Err_Ok)
	{
		std::cout << "Error occurred during FreeType initialization: " << error << std::endl;
	}
	else
	{
		std::cout << "FreeType initialized" << std::endl;
	}
}

void DependencyContainer::_loadFontFace()
{
	if (_appDir.length() == 0) { throw new std::exception(); }

	_fontFace = std::make_shared<FT_Face>();
	auto file = _appDir + std::string("DejaVuSansMono.ttf");
	FT_Error error = FT_New_Face(*_freeType, file.c_str(), 0, &*_fontFace);
	if (error != FT_Err_Ok)
	{
		std::cout << "Error occurred loading font: " << error << std::endl;
	}
	else
	{
		std::cout << "Font loaded" << std::endl;
	}
}