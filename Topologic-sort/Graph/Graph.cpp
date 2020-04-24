#include "Graph.h"
#include <utility>

using n_Graph::Node;

int Graph::m_findWithKey(int _key) const {
	if (_key < m_nextKey / 2) {
		for (int i = 0; i < m_list.size(); ++i) {
			Node* currentElem = m_list.at(i);
			if (currentElem->key() == _key)
				return i + 1;
		}
	}
	else {
		for (int i = m_list.size() - 1; i >= 0; i--) {
			Node* currentElem = m_list.at(i);
			if (currentElem->key() == _key)
				return i + 1;
		}
	}
	return 0;
}

Graph::Graph(size_t _size) {
	makeGraph(_size);
}

void Graph::makeGraph(size_t _size) {
	removeAll();
	m_nextKey = 1;
	for (int i = 0; i < _size; ++i) {
		m_list.push_back();
		m_list.back() = new Node(m_nextKey++);
	}
}

Graph::~Graph() {
	removeAll();
}

int Graph::removeAll() {
	if (m_list.size() == 0) return 2;
	while (m_list.size() > 0) {
		delete m_list.pop_back();
	}
	return 1;
}

int Graph::makeLink(int _firstKey, int _lastKey) {
	if (_firstKey != _lastKey) {
		Node* first{ nullptr }, * last{ nullptr };
		for (int i = 0; i < m_list.size(); ++i) {
			Node* currentElem = m_list.at(i);
			if (currentElem->key() == _firstKey)       first = currentElem;
			else if (currentElem->key() == _lastKey)   last = currentElem;
		}
		if (first == nullptr || last == nullptr) return 0;
		first->addLinkTo(last);
		return 0;
	}
	return 0;
}

int Graph::removeLink(int _firstKey, int _lastKey) {
	if (_firstKey != _lastKey) {
		Node* first{ nullptr }, * last{ nullptr };
		for (int i = 0; i < m_list.size(); ++i) {
			Node* currentElem = m_list.at(i);
			if (currentElem->key() == _firstKey)       first = currentElem;
			else if (currentElem->key() == _lastKey)   last = currentElem;
		}
		if (first == nullptr || last == nullptr) return 0;
		first->removeLinkTo(last);
		return 0;
	}
	return 0;
}

int Graph::addElement(int _key) {
	if (m_findWithKey(_key) == 0) {
		m_list.push_back(new Node(_key));
		return 1;
	}
	return 0;
}

int Graph::removeElemenent(int _key) {
	int pos = m_findWithKey(_key);
	if (pos != 0) {		
		Node* element =  m_list.pop(pos - 1);
		delete element;
		return 1;
	}
	return 0;
}

void Graph::outList() const {
	for (int i = 0; i < m_list.size(); ++i) {
		Node& elem = *(m_list.at(i));
		std::cout << elem << std::endl;
	}
}

Dlist<int> Graph::getKeys() const {
	Dlist<int> keys;
	for (int i = 0; i < m_list.size(); ++i) {
		keys.push_back(m_list.at(i)->key());
	}
	sort(keys);
	return keys;
}

int Graph::size() const {
	return m_list.size();
}

Dlist<int> Graph::linksFrom(int _key) const {
	int elementPos = m_findWithKey(_key);
	if (elementPos == 0) return Dlist<int>();
	return m_list.at(elementPos - 1)->links();
}

int Graph::linksAmountFrom(int _key) const {
	int elementPos = m_findWithKey(_key);
	if (elementPos == 0) return -1;
	return m_list.at(elementPos - 1)->links().size();
}

int Graph::linksAmountTo(int _key) const {
	int elementPos = m_findWithKey(_key);
	if (elementPos == 0) return -1;
	return m_list.at(elementPos - 1)->parentsAmount();
}