#ifndef TREAP_H
#define TREAP_H

#include "random.h"
#include "couple.h"
#include "algorithms.h"
#include <iostream>
#include <ctime>

template<typename T1, typename T2=void>
class treap {
protected:
	xorshiftGen64 priorityGen;

	struct node {
		T1 *key;
		T2 *elem;
		unsigned long long priority;
		node * left, * right;
		node()
		: left(nullptr),
		  right(nullptr),
		  key(nullptr),
		  elem(nullptr) {}

		node (xorshiftGen64 &priorityGen, T1 t_key, T2 t_elem)
		: key(new T1(t_key)),
		  elem(new T2(t_elem)),
		  left(nullptr),
		  right(nullptr),
		  priority(priorityGen()) {}
	};

	struct nodePair {
		node * left, * right;
		nodePair()
		: left(nullptr),
		  right(nullptr) {}
		nodePair(node * t_left, node * t_right)
		: left(t_left),
		  right(t_right) {}
	};

	node * _root;

	void clearTree(node * t)
	{
		if(t == nullptr)
			return;
		clearTree(t->left);
		clearTree(t->right);
		delete t;
	}

	node * copyTree(node * t)
	{
		if (t == nullptr)
			return nullptr;
		node * result = new node(priorityGen, *t->key, *t->elem);
		result->priority = t->priority;
		result->left = copyTree(t->left);
		result->right = copyTree(t->right);
		return result;
	}

	void stdoutTraverseInOrder(node * t)
	{
		if (t == nullptr)
			return;
		stdoutTraverseInOrder(t->left);
		std::cout << *t->key << ": " << *t->elem << std::endl;
		stdoutTraverseInOrder(t->right);
		return;
	}

	bool checkPriority(node * t) {
		if (t == nullptr)
			return true;
		if (t->left != nullptr && t->left->priority > t->priority)
			return false;
		if (t->right != nullptr && t->right->priority > t->priority)
			return false;
		return checkPriority(t->right) && checkPriority(t->left);
	}

	node * findMax(node * t)
	{
		while (t != nullptr && t->right != nullptr)
			t = t->right;
		return t;
	}

	node * findMin(node * t)
	{
		while (t != nullptr && t->left != nullptr)
			t = t->left;
		return t;
	}

	node * find(node *t, T1 t_key)
	{
		if (t == nullptr || *t->key == *t_key)
			return t;
		if (t_key < *t->key)
			return find(t->left, t_key);
		else
			return find(t->right, t_key);
	}

	nodePair split(node * t, T1 t_key)
	{
		if (t == nullptr)
			return nodePair(nullptr, nullptr);
		if (t_key < *t->key) {
			nodePair returnSplit = split(t->left, t_key);
			t->left = returnSplit.right;
			return {returnSplit.left, t};
		}
		nodePair returnSplit = split(t->right, t_key);
		t->right = returnSplit.left;
		return {t, returnSplit.right};
	}

	node * merge(nodePair nodes)
	{
		if (nodes.left == nullptr || nodes.right == nullptr)
			return nodes.left == nullptr ? nodes.right : nodes.left;
		if (nodes.left->priority > nodes.right->priority) {
			nodes.left->right = merge({nodes.left->right, nodes.right});
			return nodes.left;
		}
		nodes.right->left = merge({nodes.left, nodes.right->left});
		return nodes.right;
	}

	node * leftRotate(node * t)
	{
		node * x = t->right;
		node * y = x->left;
		x->left = t;
		t->right = y;
		return x;
	}

	node * rightRotate(node * t)
	{
		node * x = t->left;
		node * y = x->right;
		x->right = t;
		t->left = y;
		return x;
	}

	node * insert(node * t, T1 t_key, T2 t_elem)
	{
		if (t == nullptr)
			return new node(priorityGen, t_key, t_elem);
		if (t_key == *t->key) {
			t->elem = new T2(t_elem);
		} else if (t_key < *t->key) {
			t->left = insert(t->left, t_key, t_elem);
			if (t->left->priority > t->priority)
				t = rightRotate(t);
		} else {
			t->right = insert(t->right, t_key, t_elem);
			if (t->right->priority > t->priority)
				t = leftRotate(t);
		}
		return t;
	}

	node * remove(node * t, T1 t_key)
	{
		if (t == nullptr)
			return nullptr;
		if (*t->key == t_key) {
			node * result = merge({t->left, t->right});
			if (t->key != nullptr)
				delete t->key;
			if (t->elem != nullptr)
				delete t->elem;
			return result;
		}
		else if (t_key < *t->key)
			t->left = remove(t->left, t_key);
		else
			t->right = remove(t->right, t_key);
		return t;
	}
public:
	treap()
	: _root(nullptr) {}

	~treap()
	{
		clearTree(_root);
	}

	treap(node * t_root) {
		_root = t_root;
	}

	treap(const treap & other)
	{
		_root = copyTree(other._root);
		priorityGen = other.priorityGen;
	}

	treap& operator=(const treap & other)
	{
		_root = copyTree(other._root);
		priorityGen = other.priorityGen;
		return *this;
	}

	void insert(T1 t_key, T2 t_elem)
	{
		_root = insert(_root, t_key, t_elem);
		return;
	}

	void merge(const treap &other) {
		_root = merge({_root, other._root});
		return;
	}

	Couple::pair<treap, treap> split(T1 t_key)
	{
		node * tmp = copyTree(_root);
		nodePair returnSplit = split(tmp, t_key);
		return {returnSplit.left, returnSplit.right};
	}

	void remove(T1 t_key)
	{
		_root = remove(_root, t_key);
	}

	void inOrderPrint()
	{
		stdoutTraverseInOrder(_root);
	}

	T2 getMin()
	{
		return *findMin(_root)->elem;
	}

	T2 getMax()
	{
		return *findMax(_root)->elem;
	}

	T2 *find(T1 t_key)
	{
		node * findResult = find(_root, t_key);
		return findResult == nullptr ? nullptr : new T2(*findResult->elem);
	}
};


template<typename T>
class treap<T, void> {
protected:
	xorshiftGen64 priorityGen;

	struct node {
		T *key;
		unsigned long long priority;
		node *left, *right;
		unsigned int height;

		node()
		: left(nullptr),
		  right(nullptr),
		  height(0),
		  key(nullptr) {}

		node (xorshiftGen64 &priorityGen, T t_key)
		: key(new T(t_key)),
		  priority(priorityGen()),
		  left(nullptr),
		  right(nullptr),
		  height(1) {}
	};

	struct nodePair {
		node *left, *right;

		nodePair()
				: left(nullptr),
				  right(nullptr) {}

		nodePair(node *t_left, node *t_right)
				: left(t_left),
				  right(t_right) {}
	};

	node *_root;

	unsigned int getHeight(node * t) {
			if (t == nullptr)
					return 0;
			return t->height;
	}

	void updateHeight(node * t)
	{
		if (t != nullptr)
			t->height = Algorithms::max(getHeight(t->left), getHeight(t->right))+1;
	}

	void clearTree(node *t) {
		if (t == nullptr)
			return;
		clearTree(t->left);
		clearTree(t->right);
		delete t;
	}

	node *copyTree(node *t) {
		if (t == nullptr)
			return nullptr;
		node *result = new node(priorityGen, *t->key);
		result->priority = t->priority;
		result->height = t->height;
		result->left = copyTree(t->left);
		result->right = copyTree(t->right);
		return result;
	}

	void stdoutTraverseInOrder(node *t) {
		if (t == nullptr)
			return;
		stdoutTraverseInOrder(t->left);
		std::cout << *t->key << std::endl;
		stdoutTraverseInOrder(t->right);
		return;
	}

	bool checkPriority(node * t) {
		if (t == nullptr)
			return true;
		if (t->left != nullptr && t->left->priority > t->priority)
			return false;
		if (t->right != nullptr && t->right->priority > t->priority)
			return false;
		return checkPriority(t->right) && checkPriority(t->left);
	}

	node * findMax(node * t)
	{
		while (t != nullptr && t->right != nullptr)
			t = t->right;
		return t;
	}

	node * findMin(node * t)
	{
		while (t != nullptr && t->left != nullptr)
			t = t->left;
		return t;
	}

	node *find(node *t, T t_key) {
		if (t == nullptr || *t->key == t_key)
			return t;
		if (t_key < *t->key)
			return find(t->left, t_key);
		else
			return find(t->right, t_key);
	}

	nodePair split(node *t, T t_key) {
		if (t == nullptr)
			return nodePair(nullptr, nullptr);
		if (t_key < *t->key) {
			nodePair returnSplit = split(t->left, t_key);
			updateHeight(returnSplit.left);
			updateHeight(returnSplit.right);
			t->left = returnSplit.right;
			updateHeight(t);
			return {returnSplit.left, t};
		}
		nodePair returnSplit = split(t->right, t_key);
		updateHeight(returnSplit.left);
		updateHeight(returnSplit.right);
		t->right = returnSplit.left;
		updateHeight(t);
		return {t, returnSplit.right};
	}

	node *merge(nodePair nodes) {
		if (nodes.left == nullptr || nodes.right == nullptr)
			return nodes.left == nullptr ? nodes.right : nodes.left;
		if (nodes.left->priority > nodes.right->priority) {
			nodes.left->right = merge({nodes.left->right, nodes.right});
			updateHeight(nodes.left->right);
			updateHeight(nodes.left);
			return nodes.left;
		}
		nodes.right->left = merge({nodes.left, nodes.right->left});
		updateHeight(nodes.right->left);
		updateHeight(nodes.right);
		return nodes.right;
	}

	node *leftRotate(node *t) {
		node *x = t->right;
		node *y = x->left;
		t->right = y;
		updateHeight(t);
		x->left = t;
		updateHeight(x);
		return x;
	}

	node *rightRotate(node *t) {
		node *x = t->left;
		node *y = x->right;
		t->left = y;
		updateHeight(t);
		x->right = t;
		updateHeight(x);
		return x;
	}

	node *insert(node *t, T t_key) {
		if (t == nullptr)
			return new node(priorityGen, t_key);
		if (t_key < *t->key) {
			t->left = insert(t->left, t_key);
			updateHeight(t);
			if (t->left->priority > t->priority)
				t = rightRotate(t);
		} else if (t_key > *t->key) {
			t->right = insert(t->right, t_key);
			updateHeight(t);
			if (t->right->priority > t->priority)
				t = leftRotate(t);
		}
		return t;
	}

	node *remove(node *t, T t_key) {
		if (t == nullptr)
			return nullptr;
		if (*t->key == t_key) {
			node * result = merge({t->left, t->right});
			if (t->key != nullptr)
				delete t->key;
			return result;
		}
		else if (t_key < *t->key) {
			t->left = remove(t->left, t_key);
			updateHeight(t);
		}
		else {
			t->right = remove(t->right, t_key);
			updateHeight(t);
		}
		return t;
	}

public:
	treap()
			: priorityGen((unsigned long long)time(nullptr)*65537*11*19),
			  _root(nullptr) {}

	~treap() {
		clearTree(_root);
	}

	treap(node * t_root) {
		_root = t_root;
	}

	T getValue() {
			if (_root != nullptr)
					return *_root->key;
			return T();
	}

	bool getColor() {
		return false;
	}

	unsigned int getHeight() {
		if (_root != nullptr)
			return _root->height;
		return 0;
	}

	bool isNull() {
			return _root == nullptr;
	}

	treap *getLeftNodeTree() {
			return new treap(_root->left);
	}

	treap *getRightNodeTree() {
			return new treap(_root->right);
	}

	treap(const treap &other) {
		_root = copyTree(other._root);
		priorityGen = other.priorityGen;
	}

	treap &operator=(const treap &other) {
		_root = copyTree(other._root);
		priorityGen = other.priorityGen;
		return *this;
	}

	void insert(T t_key) {
		_root = insert(_root, t_key);
		return;
	}

	void merge(const treap &other) {
		_root = merge({_root, other._root});
		return;
	}

	Couple::pair<treap, treap> split(T t_key)
	{
		node * tmp = copyTree(_root);
		nodePair returnSplit = split(tmp, t_key);
		return {returnSplit.left, returnSplit.right};
	}

	void remove(T t_key)
	{
		_root = remove(_root, t_key);
	}

	void inOrderPrint()
	{
		stdoutTraverseInOrder(_root);
	}

	T getMin()
	{
		return *findMin(_root)->key;
	}

	T getMax()
	{
		return *findMax(_root)->key;
	}

	T *find(T t_key)
	{
		node * findResult = find(_root, t_key);
		return findResult == nullptr ? nullptr : new T(*findResult->key);
	}
};

#endif //TREAP_H
