#pragma once
#include <set>
#include <vector>
#include <algorithm>
#include <iostream>
#include <format>
#include <sstream>
#include <string>
#include "basic_graph_node.h" 
#include "directed_graph_iterator.h"


namespace details {
	template<typename T>
	class graph_node;
}

template<typename DirectedGraph>
class const_directed_graph_iterator;


template<typename T>
class directed_graph
{
public:
	// STL native adaption
	using value_type = T;
	using reference = value_type&;
	using const_reference = const value_type&;
	using size_type = size_t;
	using difference_type = ptrdiff_t;

	// Iterator types
	using iterator = const_directed_graph_iterator<directed_graph>;
	using const_iterator = const_directed_graph_iterator<directed_graph>;

	// STL native methods
	[[nodiscard]] size_type size() const noexcept;
	[[nodiscard]] size_type max_size() const noexcept;
	[[nodiscard]] bool empty() const noexcept;

	// STL native Bounds Checking
	reference at(size_type index);
	const_reference at(size_type index) const;

	// Returns ref to the node with given index.
	// No Bounds checking is done.
	reference operator[](size_type index);
	const_reference operator[](size_type index) const;

	// Iterator Methods
	iterator begin() noexcept;
	iterator end() noexcept;
	const_iterator begin() const noexcept;
	const_iterator end() const noexcept;
	const_iterator cbegin() const noexcept;
	const_iterator cend() const noexcept;

	// Returns true if new node has been added.
	// Returns false if there was already node with this value.
	std::pair<iterator, bool> insert(const T& node_value);
	std::pair<iterator, bool> insert(T&& node_value);
	std::pair<iterator, bool> insert(const_iterator hint, const T& node_value);
	std::pair<iterator, bool> insert(const_iterator hint, const T&& node_value);
	template<typename Iter> void insert(Iter first, Iter second);

	// True if node was erased, false otherwise.
	bool erase(const T& node_value);
	iterator erase(const_iterator pos);
	iterator erase(const_iterator first, const_iterator last);

	// Removed all nodes from the graph
	void clear() noexcept;

	// Swaps all nodes between this and given graph.
	void swap(directed_graph& other_graph) noexcept;

	iterator find(const T& node_value);
	const_iterator find(const T& node_value) const;

	// True if edge was inserted, false otherwise.
	bool insert_edge(const T& from_node_value, const T& to_node_value);

	// True if edge was erased, false otherwise.
	bool erase_edge(const T& from_node_value, const T& to_node_value);

	// Returns set of the adjacent nodes of a given node
	std::set<T> get_adjacent_nodes_values(const T& node_value) const;

	// Comparison for 2 graphs. True if they have the same nodes
	// Order does not matter
	bool operator==(const directed_graph& rhs) const;
	bool operator!=(const directed_graph& rhs) const;

private:
	friend class const_directed_graph_iterator<directed_graph>;
	friend class directed_graph_iterator<directed_graph>;

	using nodes_container_type = std::vector<details::graph_node<T>>;
	nodes_container_type m_nodes;

	typename nodes_container_type::iterator findNode(const T& node_value);
	typename nodes_container_type::const_iterator findNode(const T& node_value) const;

	size_t get_index_of_node(const typename nodes_container_type::const_iterator& node);

	// Removes links to the node passed
	void remove_all_links_to(typename nodes_container_type::const_iterator& node_iter);

	std::set<T> get_adjacent_nodes_values(const typename details::graph_node<T>::adjacency_list_type& indices) const;
};


// -----------------------------------------
//
//    Graph Implementation
//
// -----------------------------------------

template<typename T>
std::wstring to_dot(const directed_graph<T>& graph, std::wstring_view graph_name) {
	std::wstringstream wss;
	wss << std::format(L"digraph {} {{", graph_name.data()) << std::endl;
	for (size_t index{ 0 }; index < graph.size(); ++index) {
		const auto& node_value{ graph[index] };
		const auto adjacent_nodes{ graph.get_adjacent_nodes_values(node_value) };
		if (adjacent_nodes.empty()) {
			wss << "\t" << node_value << std::endl;
		}
		else {
			for (auto&& node : adjacent_nodes) {
				wss << std::format(L"\t{} -> {}", node_value, node) << std::endl;
			}
		}
	}
	wss << "}" << std::endl;
	return wss.str();

}


template<typename T>
void swap(directed_graph<T>& lhs, directed_graph<T>& rhs) {
	lhs.swap(rhs);
}

template<typename T>
typename directed_graph<T>::nodes_container_type::iterator directed_graph<T>::findNode(const T& node_value)
{
	return std::find_if(
		std::begin(m_nodes),
		std::end(m_nodes),
		[&node_value](const auto& node) {return node.value() == node_value; }
	);
}

template<typename T>
inline typename directed_graph<T>::nodes_container_type::const_iterator
directed_graph<T>::findNode(const T& node_value) const
{
	return const_cast<directed_graph<T>*>(this)->findNode(node_value);
}

template<typename T>
inline size_t directed_graph<T>::get_index_of_node(const typename nodes_container_type::const_iterator& node)
{
	const auto index{ std::distance(std::cbegin(m_nodes), node) };
	return static_cast<size_t>(index);
}

template<typename T>
inline void directed_graph<T>::remove_all_links_to(typename nodes_container_type::const_iterator& node_iter)
{
	// Iterating over all nodes
	const size_t node_index{ get_index_of_node(node_iter) };
	for (auto&& node : m_nodes) {
		auto& adjacencyIndices{ node.get_adjacent_nodes_indices() };
		// Removing References to the to-be-deleted node
		adjacencyIndices.erase(node_index);

		// Decreasing the index of after-the-deleted nodes by one to encounter for deletion.
		std::vector<size_t> indices(std::begin(adjacencyIndices), std::end(adjacencyIndices));
		std::for_each(
			std::begin(indices), std::end(indices),
			[&node_index](size_t& index) {
				if (index > node_index)
					--index;
			}
		);
		adjacencyIndices.clear();
		adjacencyIndices.insert(std::begin(indices), std::end(indices));
	}
}

template<typename T>
inline std::set<T> directed_graph<T>::get_adjacent_nodes_values
(const typename details::graph_node<T>::adjacency_list_type& indices) const
{
	std::set<T> values;
	for (auto&& index : indices) { values.insert(m_nodes[index].value()); }
	return values;
}

template<typename T>
inline std::pair<typename directed_graph<T>::iterator, bool> directed_graph<T>::insert(T&& node_value)
{
	auto iter{ findNode(node_value) };
	{
		if (iter != std::end(m_nodes)) return { { iter, this }, false };
	}

	// Use perfect forwarding
	m_nodes.push_back(details::graph_node<T>(this, std::forward<T>(node_value)));
	return { iterator{--std::end(m_nodes), this}, true };
}
template<typename T>
inline std::pair<typename directed_graph<T>::iterator, bool> directed_graph<T>::insert(const_iterator hint, const T&& node_value)
{
	return insert(std::move(node_value)).first;
}
template<typename T>
inline std::pair<typename directed_graph<T>::iterator, bool> directed_graph<T>::insert(const T& node_value)
{
	T copy{ node_value };
	return insert(std::move(copy));
}

template<typename T>
inline std::pair<typename directed_graph<T>::iterator, bool> directed_graph<T>::insert(const_iterator hint, const T& node_value)
{
	return insert(node_value).first;
}

template<typename T>
inline typename directed_graph<T>::iterator directed_graph<T>::begin() noexcept
{
	return iterator{ std::begin(m_nodes), this };
}

template<typename T>
inline typename directed_graph<T>::iterator directed_graph<T>::end() noexcept
{
	return iterator{ std::end(m_nodes), this };
}

template<typename T>
inline typename directed_graph<T>::const_iterator directed_graph<T>::begin() const noexcept
{
	return const_iterator{ std::begin(m_nodes), this };
}

template<typename T>
inline typename directed_graph<T>::const_iterator directed_graph<T>::end() const noexcept
{
	return const_iterator{ std::end(m_nodes), this };
}

template<typename T>
inline typename directed_graph<T>::const_iterator directed_graph<T>::cbegin() const noexcept
{
	return begin();
}

template<typename T>
inline typename directed_graph<T>::const_iterator directed_graph<T>::cend() const noexcept
{
	return end();
}



template<typename T>
inline bool directed_graph<T>::erase(const T& node_value)
{
	auto iter{ findNode(node_value) };
	if (iter == std::end(m_nodes)) return false;

	remove_all_links_to(iter);
	m_nodes.erase(iter);
	return true;
}

template<typename T>
inline typename directed_graph<T>::iterator directed_graph<T>::erase(const_iterator pos)
{
	if (pos.m_nodeIterator == std::end(m_nodes)) {
		return iterator{ std::end(m_nodes), this };
	}
	remove_all_links_to(pos.m_nodeIterator);
	return iterator{ m_nodes.erase(pos.m_nodeIterator), this };
}

template<typename T>
inline typename directed_graph<T>::iterator directed_graph<T>::erase(const_iterator first, const_iterator last)
{
	for (auto iter{ first }; iter != last; ++iter) {
		if (iter.m_nodeIterator != std::end(m_nodes)) {
			remove_all_links_to(iter.m_nodeIterator);
		}
	}
	return iterator{ m_nodes.erase(first.m_nodeIterator, last.m_nodeIterator), this };
}

template<typename T>
inline typename directed_graph<T>::iterator directed_graph<T>::find(const T& node_value)
{
	return iterator();
}

template<typename T>
inline typename directed_graph<T>::const_iterator directed_graph<T>::find(const T& node_value) const
{
	return const_iterator();
}

template<typename T>
inline bool directed_graph<T>::insert_edge(const T& from_node_value, const T& to_node_value)
{
	const auto from = findNode(from_node_value);
	const auto to = findNode(to_node_value);
	if (from == std::end(m_nodes) || to == std::end(m_nodes)) return false;

	const size_t to_index = get_index_of_node(to);
	return from->get_adjacent_nodes_indices().insert(to_index).second;
}

template<typename T>
inline bool directed_graph<T>::erase_edge(const T& from_node_value, const T& to_node_value)
{
	const auto from{ findNode(from_node_value) };
	const auto to{ findNode(to_node_value) };
	bool invalid_connection = (from == std::end(m_nodes) || to == std::end(m_nodes));

	const size_t to_index{ get_index_of_node(to) };
	from->get_adjacent_nodes_indices().erase(to_index);
	return true;
}

template<typename T>
inline void directed_graph<T>::clear() noexcept { m_nodes.clear(); }

template<typename T>
inline typename directed_graph<T>::reference directed_graph<T>::operator[](size_type index)
{
	return m_nodes[index].value();
}

template<typename T>
inline typename directed_graph<T>::const_reference directed_graph<T>::operator[](size_type index) const
{
	return m_nodes[index].value();
}


template<typename T>
inline bool directed_graph<T>::operator==(const directed_graph& rhs) const
{
	if (m_nodes.size() != rhs.m_nodes.size()) return false;
	for (auto&& node : m_nodes) {
		const auto rhsNodeIter{ rhs.findNode(node.value()) };
		if (rhsNodeIter == std::end(rhs.m_nodes)) return false;

		const auto adjacent_values_lhs{
			get_adjacent_nodes_values(node.get_adjacent_nodes_indices()) };
		const auto adjacent_values_rhs{
			rhsNodeIter->get_adjacent_nodes_indices() };
		if (adjacent_values_lhs != adjacent_values_rhs) return false;
	}
	return true;
}

template<typename T>
inline bool directed_graph<T>::operator!=(const directed_graph& rhs) const
{
	return !(*this == rhs);
}

template<typename T>
inline void directed_graph<T>::swap(directed_graph& other_graph) noexcept
{
	m_nodes.swap(other_graph);
}

template<typename T>
inline size_t directed_graph<T>::size() const noexcept
{
	return m_nodes.size();
}

template<typename T>
inline typename directed_graph<T>::size_type directed_graph<T>::max_size() const noexcept
{
	return m_nodes.max_size();
}

template<typename T>
inline bool directed_graph<T>::empty() const noexcept
{
	return m_nodes.empty();
}

template<typename T>
inline typename directed_graph<T>::reference directed_graph<T>::at(size_type index)
{
	return m_nodes.at(index).value();
}

template<typename T>
inline typename directed_graph<T>::const_reference directed_graph<T>::at(size_type index) const
{
	return m_nodes.at(index).value();
}

template<typename T>
inline std::set<T> directed_graph<T>::get_adjacent_nodes_values(const T& node_value) const
{
	auto iter{ findNode(node_value) };
	if (iter == std::end(m_nodes)) return std::set<T>{};
	return get_adjacent_nodes_values(iter->get_adjacent_nodes_indices());
}

template<typename T>
template<typename Iter>
inline void directed_graph<T>::insert(Iter first, Iter second)
{
	// Copy each element in the range by using an insert_iterator adapter
	// Give begin() as dummy position -- insert ignores it
	std::copy(first, second, std::insert_iterator{ *this, begin() });
}
