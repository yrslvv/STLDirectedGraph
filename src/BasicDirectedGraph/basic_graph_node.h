#pragma once
#include <set>

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

		using adjacency_list_type = std::set<size_t>;

	private:
		// Only the graph can access private members of nodes
		friend class directed_graph<T>;

		

		// Returns reference to the adjacency list
		[[nodiscard]] adjacency_list_type& get_adjacent_nodes_indices();

		// Returns const reference to the adjacency list
		[[nodiscard]] const adjacency_list_type& get_adjacent_nodes_indices() const;

		// ---------- Data Members ----------
		T m_data;
		adjacency_list_type m_adjacentNodeIndices;
		directed_graph<T>* m_graph; // Graph this node belongs to
	};
}

namespace details {

	template<typename T>
	graph_node<T>::graph_node(directed_graph<T>* graph, const T& t)
		:m_graph{ graph }, m_data{ t } {
	}

	template<typename T>
	graph_node<T>::graph_node(directed_graph<T>* graph, T&& t)
		: m_graph{ graph }, m_data{ std::move(t) } {
	}

	template<typename T>
	T& graph_node<T>::value() noexcept { return m_data; }

	template<typename T>
	const T& graph_node<T>::value() const noexcept { return m_data; }

	template<typename T>
	typename graph_node<T>::adjacency_list_type& graph_node<T>::get_adjacent_nodes_indices() { return m_adjacentNodeIndices; }

	template<typename T>
	typename const graph_node<T>::adjacency_list_type& graph_node<T>::get_adjacent_nodes_indices() const { return m_adjacentNodeIndices; }

}
