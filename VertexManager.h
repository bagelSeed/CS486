#ifndef CLASS__VERTEX_MANAGER__
#define CLASS__VERTEX_MANAGER__

#include <iostream>
#include <vector>
#include "Vertex.h"

class VertexManager
{
public:
	VertexManager(std::istream &stream) {
		int entries;
		stream >> entries;

		// std::cout << entries << std::endl;
		while(entries) {
			Vertex v(stream);
			vertices.push_back(v);
			--entries;
		}
		for (int i = 0; i < vertices.size(); i++) {
			vertices[i].debug();
		}
		minCost = 0;
	}
	~VertexManager(){}
	void printMinOrdering() {
		for (std::vector<int>::iterator it = minOrdering.begin(); it != minOrdering.end(); ++it) {
			std::cout<<*it<<" ";
		}
		std::cout<<std::endl;
	}

	// Focus: ITerative improvement with threshold acceptance
	void getMinOrdering() {

		// First start, starting node = sort all null parent vertex from smallest to largest.
		// This ensure that the large parent set vertex will have some other vertex to compare with
		getAscendingOrdering();
		getInitialOrderCost();

		int v_size = minOrdering.size();
		int max_threshold = v_size * v_size;
		int cur_threshold = max_threshold;
		int i = v_size - 2;
		int j = v_size - 1;

		tempMinOrdering = minOrdering;
		tempMinOrderingCost = minOrderingCost;
		
		std::cout << "Begin local search, initial mincost: " << minCost << std::endl;
		// generate rand for size of threshold. If threshold reach, and no new improvement, let that improvement stay and continue

		while(cur_threshold) {
			if (i == 0 && j == 1) {
				i = v_size - 2;
				j = v_size - 1;
			}

			computeNewOrdering(i, j);
			if(tempMinCost < minCost) {
				minCost = tempMinCost;
				minOrdering = tempMinOrdering;
				minOrderingCost = tempMinOrderingCost;
				cur_threshold = max_threshold;

				std::cout << "*** local search finds better ordering, mincost: " << minCost << std::endl;
				
			} else {
				--cur_threshold;
			}
			--i;
			--j;
		}

		std::cout << "Terminated local search, final mincost: " << minCost << std::endl;
	}

	void getAscendingOrdering() {
		// Selection sort, vertices are < 100. O(1).
		for(std::vector<Vertex>::iterator v = vertices.begin(); v != vertices.end(); ++v) {

			std::vector<float> v_cost = v->cost;

			int min_size = minOrdering.size();
			int cost = v_cost[v->getEmptyParentSet()];
			int index = v->index;

			bool inserted = false;

			for (int i = 0; i < min_size; ++i) {
				if (minOrderingCost[i] > cost) {
					minOrderingCost.insert(minOrderingCost.begin()+i, cost);
					minOrdering.insert(minOrdering.begin()+i, index);
					inserted = true;
					break;
				}
			}
			if(!inserted){
				minOrderingCost.push_back(cost);
				minOrdering.push_back(index);
			}
		}
	}

	void getInitialOrderCost() {
		printMinOrdering();
		// std::cout << "*****************************************************************************" << std::endl;
		for (int i = 0; i < minOrdering.size(); ++i) {
			// std::cout << "Vertex: "<< vertices[i].index << ". ";
			minCost += vertices[i].findMinCostWithOrdering(minOrdering);
			// std::cout << std::endl;
		}
		// std::cout << "*****************************************************************************" << std::endl;
	}
	
	void computeNewOrdering(int i, int j) {
		std::vector< int >::iterator it = tempMinOrdering.begin();
		iter_swap(it+i, it+j);
		tempMinCost = 0;
		for (int i = 0; i < tempMinOrdering.size(); ++i) {
			tempMinCost += vertices[i].findMinCostWithOrdering(tempMinOrdering);
		}
	}

	std::vector< Vertex > vertices;

	float minCost;
	std::vector< int > minOrdering;
	std::vector< int > minOrderingCost;

	float tempMinCost;
	std::vector< int > tempMinOrdering;
	std::vector< int > tempMinOrderingCost;
};

#endif