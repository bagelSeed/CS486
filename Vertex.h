#ifndef CLASS__VERTEX__
#define CLASS__VERTEX__

#include <vector>
#include <string>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

class Vertex
{
	void parseEntry(std::istream& stream) {
		char buffer;
		float c;
		std::vector<int> set;

		stream >> buffer;
		while (buffer != '}') {

			if (stream.peek() == '}') {
				stream >> buffer;
				break;
			}

			char halfBuffer[256];
			int index=1;

			stream >> buffer;
			halfBuffer[0] = buffer;

			while(stream.peek()!=',' && stream.peek()!='}') {
				stream >> buffer;
				halfBuffer[index] = buffer;
				++index;
			}
			halfBuffer[index] = '\0';
			stream >> buffer;

			int val = atoi(halfBuffer);
			set.push_back(val);

		}
		stream >> c;
		parent_set.push_back(set);
		cost.push_back(c);

	}
public:
	Vertex(std::istream& stream) {
		int i, entries;
		stream >> i;
		stream >> entries;

		index = i;
		while (entries) {
			parseEntry(stream);
			--entries;
		}
	}
	~Vertex(){}
	int index;
	std::vector < std::vector<int> > parent_set;
	std::vector <float> cost;
};

#endif