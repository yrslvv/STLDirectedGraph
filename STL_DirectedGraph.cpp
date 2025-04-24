// STL_DirectedGraph.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "basic_directed_graph.h"

using namespace std;
int main()
{
	directed_graph<int> graph;
	// Insert some nodes and edges.
	graph.insert(11);
	graph.insert(22);
	graph.insert(33);
	graph.insert(44);
	graph.insert(55);
	graph.insert_edge(11, 33);
	graph.insert_edge(22, 33);
	graph.insert_edge(22, 44);
	graph.insert_edge(22, 55);
	graph.insert_edge(33, 44);
	graph.insert_edge(44, 55);
	std::wcout << to_dot(graph, L"Graph1");

	// Remove edge and a node
	graph.erase_edge(22, 44);
	graph.erase(44);
	std::wcout << to_dot(graph, L"Graph1");
	
	cout << "Size: " << graph.size() << endl;
	/*
	digraph Graph1 {
		11 -> 33
		22 -> 33
		22 -> 44
		22 -> 55
		33 -> 44
		44 -> 55
		55
	}
	digraph Graph1 {
		11 -> 33
		22 -> 33
		22 -> 55
		33
		55
	}
Size: 4
	*/
	
}

