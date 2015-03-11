#pragma once

#include <memory>
#include "Console.hpp"

namespace otucha {
	class DependencyContainer {
	public:
		DependencyContainer();
		
		std::shared_ptr<warbler::Console> getConsole();

		static std::shared_ptr<DependencyContainer> getSingleton();

	private:
		std::shared_ptr<warbler::Console> _console;

		static std::shared_ptr<DependencyContainer> _singleton;
	};
}