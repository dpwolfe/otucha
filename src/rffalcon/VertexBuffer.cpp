#include "VertexBuffer.hpp"

#include <vector>
#include <sstream>j

using namespace rffalcon;

VertexBuffer::VertexBuffer(const std::string &format) : _format(format)
{
	for (int index = 0; index < MAX_VERTEX_ATTRIBUTES; ++index)
	{
		_attributes[index] = nullptr;
	}

	std::vector<std::string> formatParts;
	std::stringstream formatStringStream(format);
	std::string formatPart;
	while (std::getline(formatStringStream, formatPart, ','))
	{
		formatParts.push_back(formatPart);
	}

	for (int index = 0; index < MAX_VERTEX_ATTRIBUTES && index < static_cast<int>(formatParts.size()); ++index)
	{
		std::shared_ptr<VertexAttribute> attribute = VertexAttribute::parse(formatParts[index]);
	}
}

VertexBuffer::~VertexBuffer()
{

}