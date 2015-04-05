#pragma once

#include <string>
#include <memory>
#include "VertexAttribute.hpp"

namespace rffalcon {
	class VertexBuffer {
	public:
		VertexBuffer(const std::string &format);
		~VertexBuffer();

	private:
		std::string _format;
		std::shared_ptr<VertexAttribute> _attributes[MAX_VERTEX_ATTRIBUTES];
	};
}