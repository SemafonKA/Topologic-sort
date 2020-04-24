#include "Graph.Node.h"

using n_Graph::Node;

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
	int linkPos = isLinkedTo(_to);
	int parentPos = isParentTo(_to);
	if (linkPos == 0) return 2;
	else {
		_to->m_parents.pop(parentPos - 1);
		m_links.pop(linkPos - 1);
		return 1;
	}
}

Dlist<int> n_Graph::Node::links() const {
	Dlist<int> links;
	for (int i = 0; i < m_links.size(); ++i) {
		links.push_back(m_links.at(i)->m_key);
	}
	sort(links);
	return links;
}

std::ostream& n_Graph::operator<<(std::ostream& _out, Node& _node) {
	_out << _node.m_key << ")";
	for (int i = 0; i < _node.m_links.size(); ++i) {
		_out << " --> " << _node.m_links.at(i)->m_key;
	}
	_out << "   |   has " << _node.m_parents.size() << " parents" << std::endl;
	return _out;
}