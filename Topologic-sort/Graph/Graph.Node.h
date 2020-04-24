#pragma once

#include "../Dlist/Dlist.h"
#include <iostream>

namespace n_Graph {
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

		/*
			* Возвращает массив ключевых значений, на которые ссылается элемент
		*/
		Dlist<int> links() const;

		friend std::ostream& operator<<(std::ostream& _out, n_Graph::Node& _node);
	};
}	//namespace n_Graph