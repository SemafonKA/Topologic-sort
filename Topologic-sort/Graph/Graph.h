///////////////////////////////////////////////////////////////////
//                                                               //
//                      Graph v.1.0.1                            //
//                Project made by SemafonKA                      //
//          Me on gitHub (https://github.com/SemafonKA)          //
//                                                               //
///////////////////////////////////////////////////////////////////

#pragma once

#include "Graph.Node.h"
#include "../Dlist/Dlist.h"
#include <iostream>
#include <utility>

class Graph {
private:
	Dlist <n_Graph::Node*> m_list;
	int m_nextKey = 1;

	int m_findWithKey(int _key) const;
public:
	/*
		* Создаёт граф размера _size
	*/
	Graph(size_t _size = 0);

	~Graph();

	/*
		* Удаляет прошлый граф и создаёт новый граф размера _size
	*/
	void makeGraph(size_t _size = 0);

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
	void outList() const;

	/*
		* Возвращает список всех ключей в данном графе
		* (В порядке по возрастанию)
	*/
	Dlist<int> getKeys() const;

	/*
		* Возвращает размер графа
	*/
	int size() const;

	/* 
		* Возврщает список ключей, на которые ссылается данный элемент 
	*/
	Dlist<int> linksFrom(int _key) const;

	/* 
		* Возвращает число ключей, на которые ссылается данный элемент 
	*/
	int linksAmountFrom(int _key) const;

	/*
		* Возвращает список ключей, которые ссылаются на данный элемент
	*/
	Dlist<int> linksTo(int _key) const;
	/* 
		* Возвращает число ключей, которые ссылаются на данный элемент 
	*/
	int linksAmountTo(int _key) const;

	/*
		Возвращает число подграфов и массив вершин в порядке 
		возрастания, пронумерованных соответсвующим подграфом
	*/
	std::pair<int, Dlist<int>> subgraphs() const;
};