# Directed Graph - C++ STL Container Adaptation

This project implements a **directed graph** data structure using various versions of the graph class, progressively adapting it to leverage the power and efficiency of **C++ Standard Library (STL)** containers. The project is a demonstration of my understanding of graph theory and C++ container design patterns, as well as my ability to optimize and refactor code.

## 🚀 First Iteration

In the first iteration of the **directed_graph** class, the focus was on implementing the basic functionality of a directed graph using custom classes and containers. The initial version leverages a simple `std::vector` of graph nodes and uses `std::set` for managing adjacency lists.

## 🚀 Second Iteration: Iterator Support
In the second iteration of the **directed_graph** class, the primary enhancement was the addition of **custom iterator support**, enabling standard C++ iteration patterns over graph nodes.
Key upgrades in this version:
- **Read-only Iteration**: The `const_directed_graph_iterator` class was introduced to allow safe, read-only traversal of graph nodes using familiar iterator syntax (e.g., range-based for loops).
- **Modifiable Iteration**: The `directed_graph_iterator` class extends the const iterator, enabling modification of node values during iteration.
- **Bidirectional Capability**: Both iterators are **bidirectional**, supporting `++` and `--` operations for forward and reverse traversal.
- **Iterator Integration**: The `directed_graph` class exposes `begin()` and `end()` functions (const and non-const versions), integrating seamlessly with C++ STL-style iteration.

This iteration brings the graph structure closer to STL compliance, improves usability, and lays the foundation for more advanced algorithms and container behaviors in future versions.

## Class Hierarchy
- **Graph Nodes (`graph_node`)**: Each graph node stores a value and maintains a set of adjacent nodes, which are represented by indices in the node container.
  
- **Graph Operations**: 
    - **Insertion of nodes**: Adds new nodes to the graph, ensuring no duplicates.
    - **Node removal**: Allows for the removal of nodes from the graph, and automatically removes any edges pointing to the deleted node.
    - **Edge management**: Inserts and removes directed edges between nodes using indices for efficient referencing.
    - **Accessing nodes**: Nodes can be accessed via their index or value.
    - **Equality comparison**: The `==` operator compares two graphs by checking if they have the same set of nodes and edges, regardless of order.

- **Adjacency List**: For each node, a `std::set<size_t>` is used to represent the indices of adjacent nodes, ensuring that each edge is unique and the adjacency list is kept ordered.

- **Graph Serialization**: The graph can be converted to a `.dot` representation for visualization, making it easy to generate a graphical representation of the graph structure using Graphviz or similar tools.

1. **`directed_graph` Class**:
   - Manages the graph as a collection of nodes.
   - Provides methods for inserting, removing, and accessing nodes and edges.
   - Uses `std::vector` for storing nodes and `std::set` for adjacency lists.
   - **Iterator support**: Exposes `begin()` and `end()` for range-based loops over nodes.

2. **`graph_node` Class**:
   - Represents individual nodes in the graph.
   - Stores the node's value and a set of indices representing adjacent nodes.
   - Provides methods to access the node's value and its adjacency list.
   - Encapsulates access to adjacency lists with proper iterators.

3. **`const_directed_graph_iterator` Class**:
   - A bidirectional iterator for read-only traversal of nodes in the graph.
   - Works with `const` instances of the graph.
   - Supports standard iterator operations: dereferencing, incrementing, comparison.

4. **`directed_graph_iterator` Class**:
   - Inherits from `const_directed_graph_iterator` and allows **modification** of node values.
   - Used for non-const traversal and modification of graph nodes.
   - Supports both pre/post increment and decrement operations.

This initial implementation serves as the foundation for further optimization and adaptation to more efficient STL containers in subsequent versions of the project.

