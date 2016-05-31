#ifndef CLASS__VERTEX__
#define CLASS__VERTEX__

#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
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
		if (set.size() == 0) {
			parentEmptyIndex = parent_set.size()-1;
		}
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
	float findMinCostWithOrdering(std::vector<int> order) {
		float minCost = cost[getEmptyParentSet()];
		int tmp_index = 0;

		while(order[order.size()-1]!=index) {
			order.pop_back();
		}

		for (int j = 0; j < parent_set.size(); ++j) {
			bool contains = false;
			for (int k = 0; k < parent_set[j].size(); ++k) {
				if (std::find(order.begin(), order.end(), parent_set[j][k]) != order.end()) {
					contains = true;
				} else {
					contains = false;
				}
			}
			if(contains) {
				if(minCost > cost[j]) {
					minCost = cost[j];
					tmp_index = j;
				}
			}
		}

		// std::cout << "ParentSet: @index: " << tmp_index << " ";
		// for (int i = 0; i < parent_set[tmp_index].size(); ++i) {
		// 	std::cout << parent_set[tmp_index][i] << " ";
		// }
		// std::cout<<std::endl;

		return minCost;
	}

	int getEmptyParentSet() {return parentEmptyIndex;}

	void debug() {
		for (int i = 0; i < parent_set.size(); i++) {
			std::cout << "{";
			for (int j = 0; j < parent_set[i].size(); j++) {
				std::cout << parent_set[i][j] << ",";
			}
			std::cout << "} " << cost[i] << std::endl;

		}
	}
	int index;
	int parentEmptyIndex;
	std::vector < std::vector<int> > parent_set;
	std::vector <float> cost;
};

#endif