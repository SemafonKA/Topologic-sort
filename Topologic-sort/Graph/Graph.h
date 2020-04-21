#pragma once

#include <iostream>
#include "../Dlist/Dlist.h"

namespace n_Graph{
class Node {
private:
	int m_key{};
	Dlist <Node*> m_parents;
	Dlist <Node*> m_links;

public:
	/*
		* Принимает ключ данного звена
	*/
	Node(int _key);

	~Node();

	/* 
		* Возвращает ключ данного звена
	*/
	int key() const;

	/*
		* Возвращает число предков данного звена
		* (То, сколько звеньев на него ссылаются)
	*/
	int parentsAmount() const;

	/*
		* Добавляет ссылку этому звену на другое звено
	*/
	int addLinkTo(Node* _to);

	/*
		* Проверяет, связано ли звено с другим звеном	
		* Если да, то вернёт pos+1
	*/
	int isLinkedTo(const Node* _to) const;

	int isParentTo(const Node* _to) const;

	/*
		* Удаляет ссылку на звено	
	*/
	int removeLinkTo(Node* _to);

	friend std::ostream& operator<<(std::ostream& _out, n_Graph::Node& _node);
};
}	//namespace n_Graph


class Graph {
private:
	Dlist <n_Graph::Node*> m_list;
	int m_nextKey = 1;

	int m_findWithKey(int _key);
public:
	/*
		* Создаёт граф размера _size
	*/
	Graph(size_t _size = 0);

	~Graph();

	/*
		* Удаляет прошлый граф и создаёт новый граф размера _size
	*/
	void makeNewGraph(size_t _size = 0);

	/* 
		* Удаляет весь граф 
	*/
	int removeAll();

	/*
		* Создаёт ссылку с первого ключевого элемента на второй
	*/
	int makeLink(int _firstKey, int _lastKey);

	/*
		* Удаляет ссылку с первого ключевого элемента на второй
	*/
	int removeLink(int _firstKey, int _lastKey);

	/*
		* Добавляет элемент с ключом в граф
	*/
	int addElement(int _key);

	/*
		* Удаляет ключевой элемент
	*/
	int removeElemenent(int _key);

	/*
		* Выводит граф в виде иерархического списка
	*/
	void outList();

	/*
		* Возвращает размер графа
	*/
	int size();
};
