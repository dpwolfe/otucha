#pragma once

#include <memory>
#include "Console.hpp"
#include "ft2build.h"
#include FT_FREETYPE_H

namespace otucha {
	class DependencyContainer {
	public:
		DependencyContainer();
		
		std::shared_ptr<warbler::Console> getConsole();
		std::shared_ptr<FT_Library> getFreeType();
		std::string getAppDir();
		void setAppDir(const std::string &appDir);
		std::shared_ptr<FT_Face> getFontFace();

		static std::shared_ptr<DependencyContainer> getSingleton();

	private:
		std::shared_ptr<warbler::Console> _console;
		std::shared_ptr<FT_Library> _freeType;
		std::shared_ptr<FT_Face> _fontFace;
		std::string _appDir;

		void _initializeFreeType();
		void _loadFontFace();

		static std::shared_ptr<DependencyContainer> _singleton;
	};
}