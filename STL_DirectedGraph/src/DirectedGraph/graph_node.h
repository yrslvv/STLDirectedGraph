#pragma once

template<typename T>
class directed_graph;

namespace details {

	template<typename T>
	class graph_node {
	public:
		// Constructs a graph_node with the given value (copy)
		graph_node(directed_graph<T>* graph, const T& t);

		// Constructs a graph_node with the given value (move for large data or temporaries)
		graph_node(directed_graph<T>* graph, T&& t);

		// Returns reference to the stored value
		[[nodiscard]] T& value() noexcept;

		// Returns const reference to the stored value
		[[nodiscard]] const T& value() const noexcept;

		// Uses C++20 defaulted comparison: defines both == and !=
		bool operator==(const graph_node&) const = default;

	private:
		// Only the graph can access private members of nodes
		friend class directed_graph<T>;

		using adjacency_list_type = std::set<size_t>;

		// Returns reference to the adjacency list
		[[nodiscard]] adjacency_list_type& get_adjacent_nodes_indices();

		// Returns const reference to the adjacency list
		[[nodiscard]] adjacency_list_type& get_adjacent_nodes_indices() const;

		// ---------- Data Members ----------
		T m_data;
		adjacency_list_type m_adjacentNodeIndices;
		directed_graph<T>* m_graph; // Graph this node belongs to
	};
}
