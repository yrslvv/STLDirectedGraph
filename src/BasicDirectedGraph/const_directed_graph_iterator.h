#pragma once

template<typename T>
class directed_graph;

template<typename DirectedGraph>
class const_directed_graph_iterator {
public:
	using value_type = typename DirectedGraph::value_type;
	using difference_type = ptrdiff_t;
	using iterator_category = std::bidirectional_iterator_tag;
	using pointer = const value_type*;
	using reference = const value_type&;
	using iterator_type = typename DirectedGraph::nodes_container_type::const_iterator;

	// Default constructor must be done in bidirectional iterators.
	// We can default it, because it does not matter how it is initialized.
	const_directed_graph_iterator() = default;

	// No transfer of ownership
	const_directed_graph_iterator(iterator_type it, const DirectedGraph* graph);

	reference operator*() const;

	// Return type must be something to which -> can be applied.
	// So return a pointer
	pointer operator->() const;

	const_directed_graph_iterator& operator++();
	const_directed_graph_iterator& operator++(int);

	// C++20 defaulted operator==
	bool operator==(const const_directed_graph_iterator&) const = default;

protected:
	friend class directed_graph<value_type>;

	iterator_type m_nodeIterator;
	const DirectedGraph* m_graph{ nullptr };

	// Helper methods for operator++ and operator--
	void increment();
	void decrement();

};

template<typename DirectedGraph>
inline const_directed_graph_iterator<DirectedGraph>::const_directed_graph_iterator(iterator_type it, const DirectedGraph* graph)
	: m_nodeIterator(it), m_graph{ graph } {
}
template<typename DirectedGraph>
inline const_directed_graph_iterator<DirectedGraph>::reference const_directed_graph_iterator<DirectedGraph>::operator*() const
{
	return m_nodeIterator->value();
}
template<typename DirectedGraph>
inline const_directed_graph_iterator<DirectedGraph>::pointer const_directed_graph_iterator<DirectedGraph>::operator->() const
{
	return &(m_nodeIterator->value());
}
template<typename DirectedGraph>

inline typename const_directed_graph_iterator<DirectedGraph>::const_directed_graph_iterator& const_directed_graph_iterator<DirectedGraph>::operator++()
{
	increment();
	return *this;
}
template<typename DirectedGraph>
inline typename const_directed_graph_iterator<DirectedGraph>::const_directed_graph_iterator& const_directed_graph_iterator<DirectedGraph>::operator++(int)
{
	auto OldIt{ *this };
	increment();
	return OldIt;
}

template<typename DirectedGraph>
inline void const_directed_graph_iterator<DirectedGraph>::increment()
{
	++m_nodeIterator;
}

template<typename DirectedGraph>
inline void const_directed_graph_iterator<DirectedGraph>::decrement()
{
	--m_nodeIterator;
}
