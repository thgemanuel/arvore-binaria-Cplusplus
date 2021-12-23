#include <utility>
#include <sstream>
#include <string>
#include <iostream>

#include "RegTree.h"

using namespace std;

/// métodos dos nós
Node::Node(pair<int, int> i) {
	item = i;
	left = right = NULL;
}

Node::Node(pair<int, int> i, Node *l, Node *r) {
    item = i;
	left = l;
	right = r;
}

/// métodos da árvore binária de registros
BinaryRegTree::BinaryRegTree() {
	root = NULL;
}

BinaryRegTree::BinaryRegTree(BinaryRegTree& st) {
	if (st.root == NULL)
		root = NULL;
	else
		CopyTree(this->root, st.root);
}

void BinaryRegTree::CopyTree(Node *& n, Node *& sn) {
	if (sn == NULL)
		n = NULL;
	else {
		n = new Node(sn->item);
		CopyTree(n->left, sn->left);
		CopyTree(n->right, sn->right);
	}
}

void BinaryRegTree::operator=(BinaryRegTree& st) {
	if (st.root == NULL)
		root = NULL;
	else
		CopyTree(this->root, st.root);
}

void BinaryRegTree::Update(pair<int, int> r) {
	if (Search(r)) {
		Node *aux = GetNode(r, root);
		if (aux) {
			aux->item.second += r.second;
			if (aux->item.second <= 0)
				Remove(r);
		} else
			cout << "Erro ao atualizar estoque!" << endl;
	} else {
		root = Insert(r, root);
	}
}

void BinaryRegTree::Upgrade(pair<int, int> r, BinaryRegTree& t) {
	root = new Node(t.root->item);
	Node *prev = t.root, *cur = root;
	while (prev != NULL && prev->item.first != r.first) {
		if (r.first > prev->item.first) {
			cur->left = prev->left;
			prev = prev->right;
			if (prev != NULL)
				cur->right = new Node(prev->item);
			else
				cur->right = new Node(r);
			cur = cur->right;
		} else {
			cur->right = prev->right;
			prev = prev->left;
			if (prev != NULL)
				cur->left = new Node(prev->item);
			else
				cur->left = new Node(r);
			cur = cur->left;
		}
	}
	if (prev != NULL) {
		cur->left = prev->left;
		cur->right = prev->right;
		cur->item.second += r.second;
		if (cur->item.second <= 0)
			Remove(cur->item);
	} else {
		cur->item.second = r.second;
	}
}

Node* BinaryRegTree::GetNode(pair<int, int> r, Node* n) {
	if (n == NULL)
		return NULL;
	else if (n->item.first == r.first)
		return n;
	else if (r.first > n->item.first)
		return GetNode(r, n->right);
	else
		return GetNode(r, n->left);
}

void BinaryRegTree::Insert(pair<int, int> r) {
	root = Insert(r, root);
}

Node* BinaryRegTree::Insert(pair<int, int> r, Node* n) {
	if (n == NULL)
		return new Node(r);
	else {
		if (r.first > n->item.first)
			n->right = Insert(r, n->right);
		else
			n->left = Insert(r, n->left);
		return n;
	}
}

bool BinaryRegTree::Search(pair<int, int> r) {
	return Search(r, root);
}

bool BinaryRegTree::Search(pair<int, int> r, Node* n) {
	if (n == NULL)
		return false;
	else if (n->item.first == r.first)
		return true;
	else if (r.first > n->item.first)
		return Search(r, n->right);
	else
		return Search(r, n->left);
}

void BinaryRegTree::Remove(pair<int, int> r) {
	root = Remove(r, root);
}

Node* BinaryRegTree::Remove(pair<int, int> r, Node* n) {
	Node *temp = NULL;
	if (n != NULL) {
		if (r.first == n->item.first) {
			temp = n;
			n = RemoveNode(n);
		}
		else if (r.first > n->item.first)
			n->right = Remove(r, n->right);
		else
			n->left = Remove(r, n->left);
	}
	if (temp)
		delete temp;
	return n;
}

Node* BinaryRegTree::RemoveNode(Node* n) {
	if (n->left == NULL)
		return n->right;
	else if (n->right == NULL)
		return n->left;
	else
		return RemoveMax(n);
}

Node* BinaryRegTree::RemoveMax(Node* n) {
	if (n->left->right == NULL) {
		n->left->right = n->right;
		return n->left;
	} else {
		Node *aux1 = n->left;
		Node *aux2 = n->left->right;
		while (aux2->right != NULL) {
			aux1 = aux2;
			aux2 = aux2->right;
		}
		aux1->right = aux2->left;
		aux2->left = n->left;
		aux2->right = n->right;
		return aux2;
	}
}

void BinaryRegTree::Print() {
	Print(root);
}

void BinaryRegTree::Print(Node *n) {
	if (n != NULL) {
		Print(n->left);
		cout << "Codigo: " << n->item.first << "\t Quantidade: " << n->item.second << endl;
		Print(n->right);
	}
}

BinaryRegTree::~BinaryRegTree() {
	Destruct(root);
}

void BinaryRegTree::Destruct(Node *n) {
	if (n != NULL) {
		Destruct(n->left);
		Destruct(n->right);
		delete (n);
	}
}
