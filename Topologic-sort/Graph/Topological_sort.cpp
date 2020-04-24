#include "Topological_sort.h"
#include <iostream>

Dlist<int> Topological_sort::m_outList;
Dlist<std::pair<int, Topological_sort::Color>> Topological_sort::m_list;
Dlist<int> Topological_sort::m_roots;
const Graph* Topological_sort::m_graph;

void Topological_sort::list_fill(void) {
	const Dlist<int> list = m_graph->getKeys();
	m_list.clear();
	for (size_t i = 0; i < list.size(); i++) {
		m_list.push_back();
		m_list.at(i).first  = list.at(i);
		m_list.at(i).second = Color::white;
	}
}

int Topological_sort::list_find(int _key) {
	for (size_t i = 0; i < m_list.size(); i++) {
		if (m_list.at(i).first == _key) return i;
	}

	return -1;
}

void Topological_sort::roots_fill(void) {
	m_roots.clear();
	for (size_t i = 0; i < m_list.size(); i++) 	{
		if (m_graph->linksAmountTo(m_list.at(i).first) == 0)
			m_roots.push_back(m_list.at(i).first);
	}
}

int Topological_sort::rec_depthTravel(int _key) {
	int pos = list_find(_key);
	if (pos < 0) throw std::logic_error("Unexpectedly...");
	if (m_list.at(pos).second == Color::gray)  return 0;
	if (m_list.at(pos).second == Color::black) return 1;

	m_list.at(pos).second = Color::gray;
	Dlist<int> childs = m_graph->linksFrom(_key);
	while (!childs.isEmpty()) {
		if (rec_depthTravel(childs.pop_back()) == 0)
			return 0;
	}

	m_outList.push_front(_key);
	m_list.at(pos).second = Color::black;
	return 1;
}

Dlist<int> Topological_sort::forGraph(const Graph& _inputGraph) {
	if (_inputGraph.size() == 0) return Dlist<int>();
	m_list.clear();
	m_outList.clear();
	m_roots.clear();
	m_graph = &_inputGraph;

	list_fill();
	roots_fill();
	while (!m_roots.isEmpty()) {
		if (rec_depthTravel(m_roots.pop_back()) == 0) return Dlist<int>();
	}

	if (m_outList.size() != m_list.size()) return Dlist<int>();

	return m_outList;
}
