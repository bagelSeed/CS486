#include <iostream>
#include <vector>
#include "VertexManager.h"
#include "Vertex.h"

int main() {
	VertexManager vm(std::cin);
	vm.getMinOrdering();
	vm.printMinOrdering();
	return 0;
}