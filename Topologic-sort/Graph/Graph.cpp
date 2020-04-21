#include "Graph.h"
using n_Graph::Node;

// Resourses for class Node
Node::Node(int _key) {
	m_key = _key;
}

Node::~Node() {
	while (m_links.size() > 0) {
		removeLinkTo(m_links.at(0));
	}
	while (m_parents.size() > 0) {
		m_parents.at(0)->removeLinkTo(this);
	}
}

int Node::key() const { return m_key; }

int Node::parentsAmount() const { return m_parents.size(); }

int Node::addLinkTo(Node* _to) {
	if (isLinkedTo(_to)) return 2;
	
	m_links.push_back(_to);
	_to->m_parents.push_back(this);
	return 1;
}

int Node::isLinkedTo(const Node* _to) const {
	for (int i = 0; i < m_links.size(); ++i) {
		if (_to == m_links.at(i)) return i + 1;
	}
	return 0;
}

int Node::isParentTo(const Node* _to) const {
	for (int i = 0; i < _to->m_parents.size(); ++i) {
		if (this == _to->m_parents.at(i)) return i + 1;
	}
	return 0;
}

int Node::removeLinkTo(Node* _to) {
	int linkPos    = isLinkedTo(_to);
	int parentPos  = isParentTo(_to);
	if (linkPos == 0) return 2;
	else {
		_to->m_parents.pop(parentPos - 1);
		m_links.pop(linkPos - 1);
		return 1;
	}
}

std::ostream& n_Graph::operator<<(std::ostream& _out, Node& _node) {
	_out << _node.m_key << ")";
	for (int i = 0; i < _node.m_links.size(); ++i) {
		_out << " --> " << _node.m_links.at(i)->m_key;
	}
	_out << "   |   has " << _node.m_parents.size() << " parents" << std::endl;
	return _out;
}
// End resourses for class Node



// Resourses for class Graph
int Graph::m_findWithKey(int _key) {
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
	makeNewGraph(_size);
}

void Graph::makeNewGraph(size_t _size) {
	removeAll();
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

void Graph::outList() {
	for (int i = 0; i < m_list.size(); ++i) {
		Node& elem = *(m_list.at(i));
		std::cout << elem << std::endl;
	}
}

int Graph::size()
{
	return m_list.size();
}


// End resourses for class Graph