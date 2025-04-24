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

	// Try to insert a duplicate, and use structured bindings for the result.
	auto [iter22, inserted] { graph.insert(22)};
	if (!inserted) { std::cout << "Duplicate element.\n"; }

	// Print nodes using a for loop and iterators.
	for (auto iter{ graph.cbegin() }; iter != graph.cend(); ++iter)
	{
		std::cout << *iter << " ";
	}
	std::cout << std::endl;

	// Print nodes using a for loop and iterators retrieved with the non-member
	// functions std::cbegin() and std::cend().
	for (auto iter{ std::cbegin(graph) }; iter != std::cend(graph); ++iter)
	{
		std::cout << *iter << " ";
	}
	std::cout << std::endl;

	// Print nodes using a range-based for loop.
	for (auto& node : graph)
	{
		std::cout << node << std::endl;
	}
	std::cout << std::endl;

	// Search a node using the std::find() Standard Library algorithm.
	auto result{ std::find(std::begin(graph), std::end(graph), 22) };
	if (result != std::end(graph))
	{
		std::cout << "Node 22 found." << std::endl;
	}
	else
	{
		std::cout << "Node 22 NOT found." << std::endl;
	}

	// Count all nodes with values > 22.
	auto count{ std::count_if(std::begin(graph), std::end(graph),
		[](const auto& node) { return node > 22; }) };
}

