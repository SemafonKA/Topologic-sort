#pragma once
#include "Graph.h"
#include <utility>

class Topological_sort {
private:
	Topological_sort() {};

	enum class Color {
		white,
		gray,
		black
	};

	static Dlist<int> m_outList;
	static Dlist<std::pair<int, Color>> m_list;
	static Dlist<int> m_roots;
	static const Graph* m_graph;
	/*
		* Refilling list with keys from _list;
	*/
	static void list_fill(void);

	/*
		* Find position of _key-element in list
	*/
	static int list_find(int _key);

	/*
		* Refilling roots by elements in list
	*/
	static void roots_fill(void);

	/*
		* Recursive method of depth travelling for _graph from _key element 
		* with filling outList and change color of element 
*/
	static int rec_depthTravel(int _key);

public:
	/*
		* Topological sorting for _inputGraph
		* Return list of sorted elements
		* or empty list, if is recursive or empty
	*/
	static Dlist<int> forGraph(const Graph& _inputGraph);
};