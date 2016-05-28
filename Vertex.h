#include <vector>
#include <iostream>

class Vertex
{
public:
	Vertex(std::istream& stream) {
		int l;
		stream >> l;
		std::cout << l << std::endl;
	}
	~Vertex(){}
	std::vector < std::vector<int> > parent_set;
	std::vector <float> cost;
};