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
			* ��������� ���� ������� �����
		*/
		Node(int _key);

		~Node();

		/*
			* ���������� ���� ������� �����
		*/
		int key() const;

		/*
			* ���������� ����� ������� ������� �����
			* (��, ������� ������� �� ���� ���������)
		*/
		int parentsAmount() const;

		/*
			* ��������� ������ ����� ����� �� ������ �����
		*/
		int addLinkTo(Node* _to);

		/*
			* ���������, ������� �� ����� � ������ ������
			* ���� ��, �� ����� pos+1
		*/
		int isLinkedTo(const Node* _to) const;

		int isParentTo(const Node* _to) const;

		/*
			* ������� ������ �� �����
		*/
		int removeLinkTo(Node* _to);

		/*
			* ���������� ������ �������� ��������, �� ������� ��������� �������
		*/
		Dlist<int> links() const;

		friend std::ostream& operator<<(std::ostream& _out, n_Graph::Node& _node);
	};
}	//namespace n_Graph