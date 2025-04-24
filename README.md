# Directed Graph - C++ STL Container Adaptation

This project implements a **directed graph** data structure using various versions of the graph class, progressively adapting it to leverage the power and efficiency of **C++ Standard Library (STL)** containers. The project is a demonstration of my understanding of graph theory and C++ container design patterns, as well as my ability to optimize and refactor code.

## What is there now (First Iteration)

In the first iteration of the **directed_graph** class, the focus was on implementing the basic functionality of a directed graph using custom classes and containers. The initial version leverages a simple `std::vector` of graph nodes and uses `std::set` for managing adjacency lists. Here are the key features of the first iteration:

- **Graph Nodes (`graph_node`)**: Each graph node stores a value and maintains a set of adjacent nodes, which are represented by indices in the node container.
  
- **Graph Operations**: 
    - **Insertion of nodes**: Adds new nodes to the graph, ensuring no duplicates.
    - **Node removal**: Allows for the removal of nodes from the graph, and automatically removes any edges pointing to the deleted node.
    - **Edge management**: Inserts and removes directed edges between nodes using indices for efficient referencing.
    - **Accessing nodes**: Nodes can be accessed via their index or value.
    - **Equality comparison**: The `==` operator compares two graphs by checking if they have the same set of nodes and edges, regardless of order.

- **Adjacency List**: For each node, a `std::set<size_t>` is used to represent the indices of adjacent nodes, ensuring that each edge is unique and the adjacency list is kept ordered.

- **Graph Serialization**: The graph can be converted to a `.dot` representation for visualization, making it easy to generate a graphical representation of the graph structure using Graphviz or similar tools.

### Key Code Components

1. **`directed_graph` Class**:
   - Manages the graph as a collection of nodes.
   - Provides methods for inserting, removing, and accessing nodes and edges.
   - Uses `std::vector` for storing nodes and `std::set` for adjacency lists.

2. **`graph_node` Class**:
   - Represents individual nodes in the graph.
   - Stores the node's value and a set of indices representing adjacent nodes.
   - Provides methods to access the node's value and its adjacency list.

This initial implementation serves as the foundation for further optimization and adaptation to more efficient STL containers in subsequent versions of the project.

### Example Code Snippet (First Iteration)

Here’s how you can interact with the graph in the first iteration:

```cpp
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

 return 0;
}
```
### Output
```
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
```
