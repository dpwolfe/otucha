#pragma once

#include <string>

namespace rffalcon {
	class VertexBuffer {
	public:
		VertexBuffer(const std::string &format);
		~VertexBuffer();
	};
}