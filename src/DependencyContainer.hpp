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

		static std::shared_ptr<DependencyContainer> getSingleton();

	private:
		std::shared_ptr<warbler::Console> _console;
		std::shared_ptr<FT_Library> _freeType;

		void _initializeFreeType();

		static std::shared_ptr<DependencyContainer> _singleton;
	};
}