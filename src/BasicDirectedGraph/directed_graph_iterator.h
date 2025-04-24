#pragma once
#include "const_directed_graph_iterator.h"

template<typename DirectedGraph>
class directed_graph_iterator : public const_directed_graph_iterator<DirectedGraph> {
public:
	using value_type = typename DirectedGraph::value_type;
	using difference_type = ptrdiff_t;
	using iterator_category = std::bidirectional_iterator_tag;
	using pointer = value_type*;
	using reference = value_type&;
	using iterator_type = typename DirectedGraph::nodes_container_type::iterator;

	directed_graph_iterator() = default;
	directed_graph_iterator(iterator_type it, const DirectedGraph* graph);

	reference operator*();
	pointer operator->();

	directed_graph_iterator& operator++();
	directed_graph_iterator& operator++(int);

	directed_graph_iterator& operator--();
	directed_graph_iterator& operator--(int);

};

template<typename DirectedGraph>
inline directed_graph_iterator<DirectedGraph>::directed_graph_iterator(iterator_type it, const DirectedGraph* graph)
 : const_directed_graph_iterator{ it, graph } {}

template<typename DirectedGraph>
inline typename directed_graph_iterator<DirectedGraph>::reference directed_graph_iterator<DirectedGraph>::operator*()
{
	return const_cast<reference>(this->m_nodeIterator->value());
}

template<typename DirectedGraph>
inline typename directed_graph_iterator<DirectedGraph>::pointer directed_graph_iterator<DirectedGraph>::operator->()
{
	return const_cast<pointer>(&(this->m_nodeIterator->value()));
}

template<typename DirectedGraph>
inline typename directed_graph_iterator<DirectedGraph>::directed_graph_iterator& directed_graph_iterator<DirectedGraph>::operator++()
{
	this->increment();
	return *this;
}

template<typename DirectedGraph>
inline typename directed_graph_iterator<DirectedGraph>::directed_graph_iterator& directed_graph_iterator<DirectedGraph>::operator++(int)
{
	auto oldIt{ *this };
	this->increment();
	return oldIt;
}

template<typename DirectedGraph>
inline typename directed_graph_iterator<DirectedGraph>::directed_graph_iterator& directed_graph_iterator<DirectedGraph>::operator--()
{
	this->decrement();
	return *this;
}

template<typename DirectedGraph>
inline typename directed_graph_iterator<DirectedGraph>::directed_graph_iterator& directed_graph_iterator<DirectedGraph>::operator--(int)
{
	auto oldIt{ *this };
	this->decrement();
	return oldIt;
}
