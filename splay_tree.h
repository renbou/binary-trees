#ifndef BST_SPLAY_TREE_H
#define BST_SPLAY_TREE_H

#include <iostream>
#include "algorithms.h"

template<typename T>
class SplayTree {
protected:
		struct node {
				node * left, * right, * parent;
				T *key;
				unsigned int height;
				node ()
				: left(nullptr),
				  right(nullptr),
				  parent(nullptr),
				  key(nullptr),
				  height(0) {}
				node (node * t_parent, T t_key)
				: left(nullptr),
				  right(nullptr),
				  parent(t_parent),
				  key(new T(t_key)),
				  height(0) {}
		};

		node *_root;

		void clearTree(node *t) {
				if (t == nullptr)
						return;
				clearTree(t->left);
				clearTree(t->right);
				delete t;
		}

		node *copyTree(node * parent, node *t) {
				if (t == nullptr)
						return nullptr;
				node *result = new node(parent, *t->key, *t->elem);
				result->left = copyTree(result, t->left);
				result->height = t->height;
				result->right = copyTree(result, t->right);
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

		inline void copyData(node * t, node * s) {
				if (t != nullptr) {
						if (t->key != nullptr)
								delete t->key;
						if (s != nullptr) {
								t->key = s->key;
						}
				}
		}

		inline void setRoot(node * t) {
				if (getParent(t) == nullptr)
						_root = t;
		}

		void rightRotate(node * t) {
				node * l = leftChild(t);
				setLeft(t, rightChild(l));
				updateHeight(t);
				setParent(leftChild(t), t);
				setParent(l, getParent(t));
				if (leftChild(getParent(t)) == t)
						setLeft(getParent(t), l);
				else
						setRight(getParent(t), l);
				setRight(l, t);
				updateHeight(l);
				setParent(t, l);
				updateHeight(getParent(l));
				setRoot(l);
		}

		void leftRotate(node * t) {
				node * r = rightChild(t);
				setRight(t, leftChild(r));
				updateHeight(t);
				setParent(rightChild(t), t);
				setParent(r, getParent(t));
				if (leftChild(getParent(t)) == t)
						setLeft(getParent(t), r);
				else
						setRight(getParent(t), r);
				setLeft(r, t);
				updateHeight(r);
				setParent(t, r);
				updateHeight(getParent(r));
				setRoot(r);
		}

		inline node * leftChild(node * t) {
				return t == nullptr ? nullptr : t->left;
		}

		inline node * rightChild(node * t) {
				return t == nullptr ? nullptr : t->right;
		}

		inline void setRight(node * t, node * r) {
				if (t != nullptr) {
						t->right = r;
						updateHeight(t);
				}
		}

		inline void setLeft(node * t, node * l) {
				if (t != nullptr) {
						t->left = l;
						updateHeight(t);
				}
		}

		inline bool isLeft(node * t) {
				if (leftChild(getParent(t)) == t)
						return true;
				return false;
		}

		inline void setParent(node * t, node * p) {
				if (t != nullptr)
						t->parent = p;
		}

		inline void deleteNode(node * t) {
				if (t != nullptr) {
						if (getParent(t) != nullptr) {
								if (isLeft(t))
										setLeft(getParent(t), nullptr);
								else
										setRight(getParent(t), nullptr);
								updateHeight(getParent(t));
						}
						delete t;
				}
		}

		inline void replaceNode(node * u, node * v) {
				if (getParent(u) == nullptr) {
					setParent(v, nullptr);
					setRoot(v);
					return;
				}
				else if (isLeft(u))
					setLeft(getParent(u), v);
				else
					setRight(getParent(u), v);
				updateHeight(getParent(u));
				setParent(v, getParent(u));
		}

		inline node * getParent(node * t) {
				return t == nullptr ? nullptr : t->parent;
		}

		inline node * getGrandParent(node * t) {
				return (t == nullptr || getParent(t) == nullptr) ? nullptr : getParent(getParent(t));
		}

		inline bool isRoot(node * t) {
				if (t != nullptr) {
						if (t->parent == nullptr)
								return true;
						return false;
				}
				return true;
		}

		node * find(node *t, T t_key)
		{
				if (t == nullptr || *t->key == t_key) {
						splay(t);
						return t;
				}
				if (t_key < *t->key)
						return find(t->left, t_key);
				else
						return find(t->right, t_key);
		}

		void splay(node * t) {
				while (!isRoot(t)) {
					updateHeight(leftChild(t));
					updateHeight(leftChild(leftChild(t)));
					updateHeight(rightChild(rightChild(t)));
					updateHeight(t);
						if (isRoot(getParent(t))) {
								if (isLeft(t))
										rightRotate(getParent(t));
								else
										leftRotate(getParent(t));
						} else if (isLeft(getParent(t))) {
								if (isLeft(t)) {
										rightRotate(getGrandParent(t));
										rightRotate(getParent(t));
								} else {
										leftRotate(getParent(t));
										rightRotate(getParent(t));
								}
						} else {
								if (not isLeft(t)) {
										leftRotate(getGrandParent(t));
										leftRotate(getParent(t));
								} else {
										rightRotate(getParent(t));
										leftRotate(getParent(t));
								}
						}
				}
				setRoot(t);
		}

		node * insert(node * t, T t_key) {
				node * par = nullptr;
				while (t != nullptr) {
						if (t_key == *t->key) {
								break;
						} else if (t_key < *t->key) {
								par = t;
								t = t->left;
						} else {
								par = t;
								t = t->right;
						}
				}
				if (t == nullptr) {
						t = new node(par, t_key);
						if (getParent(t) == nullptr)
								setRoot(t);
						else if (t_key < *par->key)
								setLeft(par, t);
						else
								setRight(par, t);
				}
				splay(t);
				return t;
		}

		node * remove(node * t, T t_key) {
				node * par = nullptr;
				while (t != nullptr && *t->key != t_key) {
						par = t;
						if (t_key < *t->key)
								t = t->left;
						else
								t = t->right;
				}

				if(t == nullptr)
					return _root;

				if (leftChild(t) != nullptr && rightChild(t) != nullptr) {
						node * toDel = findMax(t->left);
						copyData(t, toDel);
						t = toDel;
				}

				node * pred = leftChild(t) == nullptr ? t->right : t->left;
				if (pred != nullptr) {
						replaceNode(t, pred);
						setParent(t, nullptr);
						setLeft(t, nullptr);
						setRight(t, nullptr);
						delete t;
						if (getParent(pred) == nullptr)
							return pred;
						splay(t = getParent(pred));
				} else if (getParent(t) == nullptr) {
						deleteNode(t);
						t = nullptr;
				} else {
						node * tmpPar = getParent(t);
						splay(tmpPar);
						deleteNode(t);
						t = tmpPar;
				}
				return t;
		}
public:
		SplayTree()
						: _root(nullptr) {}

		~SplayTree()
		{
				clearTree(_root);
		}

		SplayTree(node * t_root) {
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

		SplayTree *getLeftNodeTree() {
				return new SplayTree(_root->left);
		}

		SplayTree *getRightNodeTree() {
				return new SplayTree(_root->right);
		}

		SplayTree (const SplayTree & other)
		{
				_root = copyTree(nullptr, other._root);
		}

		SplayTree& operator=(const SplayTree & other)
		{
				_root = copyTree(nullptr, other._root);
		}

		void insert(T t_key)
		{
				_root = insert(_root, t_key);
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

#endif //BST_SPLAY_TREE_H
