#ifndef CLASS__VERTEX_MANAGER__
#define CLASS__VERTEX_MANAGER__

#include <iostream>
#include <vector>
#include "Vertex.h"

class VertexManager
{
public:
	VertexManager(std::istream &stream){
		int entries;
		stream >> entries;

		std::cout << entries << std::endl;
		while(entries) {
			Vertex v(stream);
			vertices.push_back(v);
			--entries;
		}
	}
	~VertexManager(){}
	std::vector< Vertex > vertices;
};

#endif