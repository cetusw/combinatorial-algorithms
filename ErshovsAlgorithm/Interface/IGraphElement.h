#pragma once
#include <memory>

class Edge;
using EdgePtr = std::shared_ptr<Edge>;

class IGraphElement
{
public:
	~IGraphElement() = default;
};
