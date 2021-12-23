#ifndef REGTREE_H_
#define REGTREE_H_

#include <sstream>
#include <string>
#include <iostream>
#include <utility>

class BinaryRegTree;

class Node {
	private:
		Node *left, *right;
		std::pair<int, int> item;
	public:
		Node(std::pair<int, int> i);
		Node(std::pair<int, int> i, Node *l, Node *r); 
		friend class BinaryRegTree;
};

class BinaryRegTree {
	private:
		Node *root; // raiz
		// m�todos internos
		Node* GetNode(std::pair<int, int> r, Node *n);
		Node* Insert(std::pair<int, int> r, Node *n);
		bool Search(std::pair<int, int> r, Node *n);
		Node* Remove(std::pair<int, int> r, Node *n);
		Node* RemoveNode(Node *n);
		Node* RemoveMax(Node *n);
		void Destruct(Node *n);
		void Print(Node *n);
	public:
		BinaryRegTree(); // construtor
		BinaryRegTree(BinaryRegTree& st); // construtor de c�pia
		void CopyTree(Node *& n, Node *& sn); // auxilia o construtor de c�pia
		void operator =(BinaryRegTree &st); // sobrecarga do operador =
		void Update(std::pair<int, int> r); // atualiza informa��es dos n�s
		void Upgrade(std::pair<int, int> r, BinaryRegTree& t); // m�todo persistente
		void Insert(std::pair<int, int> r); // m�todo de inser��o
		bool Search(std::pair<int, int> r); // m�todo de busca
		void Remove(std::pair<int, int> r); // m�todo de remo��o
		void Print(); // m�todo de exibi��o
		~BinaryRegTree(); // destrutor
};

#endif
