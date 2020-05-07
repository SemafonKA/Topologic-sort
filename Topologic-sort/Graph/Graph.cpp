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

Dlist<int> Graph::linksTo(int _key) const {
	int elementPos = m_findWithKey(_key);
	if (elementPos == 0) return Dlist<int>();
	return m_list.at(elementPos - 1)->parents();
}

int Graph::linksAmountTo(int _key) const {
	int elementPos = m_findWithKey(_key);
	if (elementPos == 0) return -1;
	return m_list.at(elementPos - 1)->parentsAmount();
}


/* Checks that all keys belong to subgraphs */
bool isAllSubgraphsFounded(const Dlist<std::pair<int, int>>& _list) {
	for (int i = 0; i < _list.size(); ++i) {
		if (_list.at(i).second == 0) return false;
	}
	return true;
}

/* Searches element position in list by key */
int findPos(int _key, const Dlist<std::pair<int, int>>& _list) {
	for (int i = 0; i < _list.size(); ++i) {
		if (_list.at(i).first == _key) return i;
	}
	return -1;
}

/* Checks if a key element belongs to a subgraph */
bool isBelongToSubgraph(int _key, const Dlist<std::pair<int, int>>& _list) {
	return _list.at(findPos(_key, _list)).second != 0;
}

std::pair<int, Dlist<int>> Graph::subgraphs() const {
	int subgraphsCount{ 0 };
	Dlist<std::pair<int, int>> keys;				// pair<key, subgraph number>
	keys.resize(this->size());
	Dlist<int> inputKeys = getKeys();						
	for (int i = 0; i < keys.size(); ++i) {
		keys.at(i).first = inputKeys.at(i);
	}

	while (!isAllSubgraphsFounded(keys)) {			
		int i{ 0 };
		for (i = 0; keys.at(i).second != 0 && i < keys.size(); ++i);	// find element without subgraph
		Dlist<int> queue_keys;									
		queue_keys.push_back(keys.at(i).first);							// push this element to queue
		subgraphsCount++;										

		while (!queue_keys.isEmpty()) {									// pushing all parents and childs from popped key
			int key = queue_keys.pop_front();
			keys.at(findPos(key, keys)).second = subgraphsCount;

			Dlist<int> parents = linksTo(key);
			while (!parents.isEmpty()) {
				int parentKey = parents.pop_back();
				if (!isBelongToSubgraph(parentKey, keys))
					queue_keys.push_back(parentKey);
			}

			Dlist<int> childs = linksFrom(key);
			while (!childs.isEmpty()) {
				int childKey = childs.pop_back();
				if (!isBelongToSubgraph(childKey, keys))
					queue_keys.push_back(childKey);
			}
		}
	}

	std::pair<int, Dlist<int>> out;
	out.first = subgraphsCount;
	for (int i = 0; i < keys.size(); ++i) {
		out.second.push_back(keys.at(i).second);
	}
	return out;
}