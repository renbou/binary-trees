#ifndef BST_RED_BLACK_TREE_HPP
#define BST_RED_BLACK_TREE_HPP

#include "algorithms.h"
#include <iostream>

template<typename T1, typename T2=void>
class RBtree {
protected:
	enum colorT {red, black};

	struct node
	{
		T1 *key;
		T2 *elem;
		unsigned int height;
		node * left, * right, * parent;
		colorT color;

		node()
		: left(nullptr),
		  right(nullptr),
		  parent(nullptr),
		  key(nullptr),
		  elem(nullptr),
		  height(0),
		  color(red) {}

		node (node * t_par, T1 t_key, T2 t_elem)
		: key(new T1(t_key)),
		  elem(new T2(t_elem)),
		  left(nullptr),
		  right(nullptr),
		  parent(t_par),
		  height(1),
		  color(red) {}

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

	node * copyTree(node * parent, node * t)
	{
		if (t == nullptr)
			return nullptr;
		node * result = new node(parent, *t->key, *t->elem);
		result->color = t->color;
		result->left = copyTree(result, t->left);
		result->right = copyTree(result, t->right);
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

	inline void setValue(node * t, T2 t_elem)
	{
		t->elem = new T2(t_elem);
	}

	inline void copyData(node * t, node * s) {
		if (t != nullptr) {
			if (t->key != nullptr)
				delete t->key;
			if (t->elem != nullptr)
				delete t->elem;
			if (s != nullptr) {
				t->elem = s->elem;
				t->key = s->key;
			}
		}
	}

	inline void setRoot(node *& root, node * t) {
		if (getParent(t) == nullptr)
			root = t;
	}

	void rightRotate(node *& root, node * t) {
		node * l = leftChild(t);
		setLeft(t, rightChild(l));
		updateHeight(t);
		setParent(leftChild(t), t);
		setParent(l, getParent(t));
		if (leftChild(getParent(t)) == t)
			setLeft(getParent(t), l);
		else
			setRight(getParent(t), l);
		updateHeight(getParent(t));
		setRight(l, t);
		updateHeight(l);
		setParent(t, l);
		setRoot(root, l);
	}

	void leftRotate(node *& root, node * t) {
		node * r = rightChild(t);
		setRight(t, leftChild(r));
		updateHeight(t);
		setParent(rightChild(t), t);
		setParent(r, getParent(t));
		if (leftChild(getParent(t)) == t)
			setLeft(getParent(t), r);
		else
			setRight(getParent(t), r);
		updateHeight(getParent(t));
		setLeft(r, t);
		updateHeight(r);
		setParent(t, r);
		setRoot(root, r);
	}

	inline bool isRed(node * t) {
		return (t == nullptr ? false : (t->color == red));
	}

	inline bool isBlack(node * t) {
		return (t == nullptr ? true : (t->color == black));
	}

	inline void setColor(node * t, colorT t_color) {
		if (t != nullptr)
			t->color = t_color;
	}

	inline colorT getColor(node * t) {
		return (t == nullptr ? black : t->color);
	}

	inline node * leftChild(node * t) {
		return t == nullptr ? nullptr : t->left;
	}

	inline node * rightChild(node * t) {
		return t == nullptr ? nullptr : t->right;
	}

	inline void setRight(node * t, node * r) {
		if (t != nullptr)
			t->right = r;
	}

	inline void setLeft(node * t, node * l) {
		if (t != nullptr)
			t->left = l;
	}

	inline void setParent(node * t, node * p) {
		if (t != nullptr)
			t->parent = p;
	}

	inline void deleteNode(node * t) {
		if (t != nullptr) {
			if (getParent(t) != nullptr) {
				if (t == leftChild(getParent(t)))
					setLeft(getParent(t), nullptr);
				else
					setRight(getParent(t), nullptr);
			}
			delete t;
		}
	}

	inline node * getParent(node * t) {
		return t == nullptr ? nullptr : t->parent;
	}

	inline node * getGrandParent(node * t) {
		return (t == nullptr || getParent(t) == nullptr) ? nullptr : getParent(getParent(t));
	}

	inline node * getSibling(node * t) {
		return (t == nullptr || getParent(t) == nullptr) ? nullptr :
			   (t == leftChild(getParent(t)) ? rightChild(getParent(t)) : leftChild(getParent(t)));
	}

	node * find(node *t, T1 t_key)
	{
		if (t == nullptr || *t->key == t_key)
			return t;
		if (t_key < *t->key)
			return find(t->left, t_key);
		else
			return find(t->right, t_key);
	}

	void fixAfterInsert(node *& root, node * t) {
		while (getParent(t) != nullptr && isRed(t) && isRed(getParent(t))) {
			if (isRed(getSibling(getParent(t)))) {
				setColor(getParent(t), black);
				setColor(getSibling(getParent(t)), black);
				setColor(getGrandParent(t), red);
				t = getGrandParent(t);
			} else if (getParent(t) == leftChild(getGrandParent(t))) {
				if (t == rightChild(getParent(t)))
					leftRotate(root, t = getParent(t));
				setColor(getParent(t), black);
				setColor(getGrandParent(t), red);
				rightRotate(root, t = getGrandParent(t));
				t = getParent(t);
			} else {
				if (t == leftChild(getParent(t)))
					rightRotate(root, t = getParent(t));
				setColor(getParent(t), black);
				setColor(getGrandParent(t), red);
				leftRotate(root, t = getGrandParent(t));
				t = getParent(t);
			}
		}
		if (getParent(t) == nullptr)
			root = t;
		setColor(root, black);
	}

	node * insert(node * t, T1 t_key, T2 t_elem)
	{
		if (t == nullptr) {
			t = new node(nullptr, t_key, t_elem);
			setColor(t, black);
			return t;
		}
		node * cur = t;
		while (true) {
			if (t_key == *cur->key) {
				setValue(cur, t_elem);
				return t;
			} else if (t_key < *cur->key) {
				if (leftChild(cur) == nullptr) {
					setLeft(cur, new node(cur, t_key, t_elem));
					cur = leftChild(cur);
					break;
				}
				cur = leftChild(cur);
			} else {
				if (rightChild(cur) == nullptr) {
					setRight(cur, new node(cur, t_key, t_elem));
					cur = rightChild(cur);
					break;
				}
				cur = rightChild(cur);
			}
		}
		fixAfterInsert(t, cur);
		return t;
	}

	void fixAfterDelete(node *& root, node * t) {
		while(getParent(t) != nullptr && isBlack(t)) {
			node * sibling = getSibling(t);
			if (t == leftChild(getParent(t))) {
				if (isRed(sibling)) {
					setColor(sibling, black);
					setColor(getParent(t), red);
					leftRotate(root, getParent(t));
					sibling = getSibling(t);
				}
				if (isBlack(leftChild(sibling)) && isBlack(rightChild(sibling))) {
					setColor(sibling, red);
					t = getParent(t);
					if (isRed(t)) {
						setColor(t, black);
						break;
					}
				} else {
					if (isBlack(rightChild(sibling))) {
						setColor(leftChild(sibling), black);
						setColor(sibling, red);
						rightRotate(root, sibling);
						sibling = getSibling(t);
					}
					setColor(sibling, getColor(getParent(t)));
					setColor(getParent(t), black);
					setColor(rightChild(sibling), black);
					leftRotate(root, t = getParent(t));
					t = getParent(t);
					break;
				}
			} else {
				if (isRed(sibling)) {
					setColor(sibling, black);
					setColor(getParent(t), red);
					rightRotate(root, getParent(t));
					sibling = getSibling(t);
				}
				if (isBlack(leftChild(sibling)) && isBlack(rightChild(sibling))) {
					setColor(sibling, red);
					t = getParent(t);
					if (isRed(t)) {
						setColor(t, black);
						break;
					}
				} else {
					if (isBlack(leftChild(sibling))) {
						setColor(rightChild(sibling), black);
						setColor(sibling, red);
						leftRotate(root, sibling);
						sibling = getSibling(t);
					}
					setColor(sibling, getColor(getParent(t)));
					setColor(leftChild(sibling), black);
					setColor(getParent(t), black);
					rightRotate(root, t = getParent(t));
					t = getParent(t);
					break;
				}
			}
		}
		if (getParent(t) == nullptr)
			root = t;
		setColor(root, black);
	}

	node * remove(node * t, T1 t_key)
	{
		node * cur = find(t, t_key);
		if (cur == nullptr)
			return t;
		if (leftChild(cur) != nullptr && rightChild(cur) != nullptr) {
			node * toDel = findMax(leftChild(cur));
			copyData(cur, toDel);
			cur = toDel;
		}

		node * pullUp = leftChild(cur) == nullptr ? rightChild(cur) : leftChild(cur);
		if (pullUp != nullptr) {
			if (getParent(cur) == nullptr)
				t = pullUp;
			else if (leftChild(getParent(cur)) == cur)
				setLeft(getParent(cur), pullUp);
			else
				setRight(getParent(cur), pullUp);
			setParent(pullUp, getParent(cur));
			if (isBlack(cur))
				setColor(pullUp, black);
			setParent(cur, nullptr);
			setLeft(cur, nullptr);
			setRight(cur, nullptr);
		} else if (getParent(cur) == nullptr) {
			t = nullptr;
		} else {
			if (isBlack(cur))
				fixAfterDelete(t, cur);
		}
		deleteNode(cur);
		return t;
	}
public:
	RBtree()
	: _root(nullptr) {}

	~RBtree()
	{
		clearTree(_root);
	}

	RBtree(node * otherRoot) {
			_root = otherRoot;
			return;
	}

	T2 getValue() {
			if (_root != nullptr)
					return *_root->elem;
			return T2();
	}

	bool getColor() {
		if (_root != nullptr)
			return _root->color == red;
		return 0;
	}

	unsigned int getHeight() {
		if (_root != nullptr)
			return _root->height;
		return 0;
	}

	bool isNull() {
			return _root == nullptr;
	}

	RBtree *getLeftNodeTree() {
			return new RBtree(_root->left);
	}

	RBtree *getRightNodeTree() {
			return new RBtree(_root->right);
	}

	RBtree (const RBtree & other)
	{
		_root = copyTree(nullptr, other._root);
	}

	RBtree&operator=(const RBtree & other)
	{
		_root = copyTree(nullptr, other._root);
	}

	void insert(T1 t_key, T2 t_elem)
	{
		_root = insert(_root, t_key, t_elem);
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
class RBtree<T, void> {
protected:
	enum colorT {red, black};

	struct node
	{
		T *key;
		node * left, * right, * parent;
		unsigned int height;
		colorT color;

		node()
				: left(nullptr),
				  right(nullptr),
				  parent(nullptr),
				  key(nullptr),
				  height(0),
				  color(red) {}

		node (node * t_par, T t_key)
				: key(new T(t_key)),
				  left(nullptr),
				  right(nullptr),
				  parent(t_par),
				  height(1),
				  color(red) {}

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

	node * copyTree(node * parent, node * t)
	{
		if (t == nullptr)
			return nullptr;
		node * result = new node(parent, *t->key);
		result->color = t->color;
		result->left = copyTree(result, t->left);
		result->height = t->height;
		result->right = copyTree(result, t->right);
		return result;
	}

	void stdoutTraverseInOrder(node * t)
	{
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

	inline void setRoot(node *& root, node * t) {
		if (getParent(t) == nullptr)
			root = t;
	}

	void rightRotate(node *& root, node * t) {
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
		setRoot(root, l);
	}

	void leftRotate(node *& root, node * t) {
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
		setRoot(root, r);
	}

	inline bool isRed(node * t) {
		return (t == nullptr ? false : (t->color == red));
	}

	inline bool isBlack(node * t) {
		return (t == nullptr ? true : (t->color == black));
	}

	inline void setColor(node * t, colorT t_color) {
		if (t != nullptr)
			t->color = t_color;
	}

	inline colorT getColor(node * t) {
		return (t == nullptr ? black : t->color);
	}

	inline node * leftChild(node * t) {
		return t == nullptr ? nullptr : t->left;
	}

	inline node * rightChild(node * t) {
		return t == nullptr ? nullptr : t->right;
	}

	inline void setRight(node * t, node * r) {
		if (t != nullptr)
			t->right = r;
		updateHeight(t);
	}

	inline void setLeft(node * t, node * l) {
		if (t != nullptr)
			t->left = l;
		updateHeight(t);
	}

	inline void setParent(node * t, node * p) {
		if (t != nullptr)
			t->parent = p;
	}

	inline void deleteNode(node * t) {
		if (t != nullptr) {
			if (getParent(t) != nullptr) {
				if (t == leftChild(getParent(t)))
					setLeft(getParent(t), nullptr);
				else
					setRight(getParent(t), nullptr);
			}
			delete t;
		}
	}

	inline node * getParent(node * t) {
		return t == nullptr ? nullptr : t->parent;
	}

	inline node * getGrandParent(node * t) {
		return (t == nullptr || getParent(t) == nullptr) ? nullptr : getParent(getParent(t));
	}

	inline node * getSibling(node * t) {
		return (t == nullptr || getParent(t) == nullptr) ? nullptr :
			   (t == leftChild(getParent(t)) ? rightChild(getParent(t)) : leftChild(getParent(t)));
	}

	node * find(node *t, T t_key)
	{
		if (t == nullptr || *t->key == t_key)
			return t;
		if (t_key < *t->key)
			return find(t->left, t_key);
		else
			return find(t->right, t_key);
	}

	void fixAfterInsert(node *& root, node * t) {
		updateHeight(t);
		while (getParent(t) != nullptr && isRed(t) && isRed(getParent(t))) {
			updateHeight(t);
			if (isRed(getSibling(getParent(t)))) {
				setColor(getParent(t), black);
				setColor(getSibling(getParent(t)), black);
				setColor(getGrandParent(t), red);
				t = getGrandParent(t);
			} else if (getParent(t) == leftChild(getGrandParent(t))) {
				if (t == rightChild(getParent(t)))
					leftRotate(root, t = getParent(t));
				setColor(getParent(t), black);
				setColor(getGrandParent(t), red);
				rightRotate(root, t = getGrandParent(t));
				t = getParent(t);
				updateHeight(t);
			} else {
				if (t == leftChild(getParent(t)))
					rightRotate(root, t = getParent(t));
				setColor(getParent(t), black);
				setColor(getGrandParent(t), red);
				leftRotate(root, t = getGrandParent(t));
				t = getParent(t);
				updateHeight(t);
			}
		}
		if (getParent(t) == nullptr)
			root = t;
		while(t != nullptr) {
			updateHeight(t);
			t = getParent(t);
		}
		setColor(root, black);
		updateHeight(t);
	}

	node * insert(node * t, T t_key)
	{
		if (t == nullptr) {
			t = new node(nullptr, t_key);
			setColor(t, black);
			return t;
		}
		node * cur = t;
		while (true) {
			if (t_key == *cur->key) {
				return t;
			} else if (t_key < *cur->key) {
				if (leftChild(cur) == nullptr) {
					setLeft(cur, new node(cur, t_key));
					cur = leftChild(cur);
					break;
				}
				cur = leftChild(cur);
			} else {
				if (rightChild(cur) == nullptr) {
					setRight(cur, new node(cur, t_key));
					cur = rightChild(cur);
					break;
				}
				cur = rightChild(cur);
			}
		}
		fixAfterInsert(t, cur);
		while(cur != nullptr) {
			updateHeight(cur);
			cur = getParent(cur);
		}
		return t;
	}

	void fixAfterDelete(node *& root, node * t) {
		while(getParent(t) != nullptr && isBlack(t)) {
			node * sibling = getSibling(t);
			if (t == leftChild(getParent(t))) {
				if (isRed(sibling)) {
					setColor(sibling, black);
					setColor(getParent(t), red);
					leftRotate(root, getParent(t));
					sibling = getSibling(t);
				}
				if (isBlack(leftChild(sibling)) && isBlack(rightChild(sibling))) {
					setColor(sibling, red);
					t = getParent(t);
					if (isRed(t)) {
						setColor(t, black);
						break;
					}
				} else {
					if (isBlack(rightChild(sibling))) {
						setColor(leftChild(sibling), black);
						setColor(sibling, red);
						rightRotate(root, sibling);
						sibling = getSibling(t);
					}
					setColor(sibling, getColor(getParent(t)));
					setColor(getParent(t), black);
					setColor(rightChild(sibling), black);
					leftRotate(root, t = getParent(t));
					t = getParent(t);
					break;
				}
			} else {
				if (isRed(sibling)) {
					setColor(sibling, black);
					setColor(getParent(t), red);
					rightRotate(root, getParent(t));
					sibling = getSibling(t);
				}
				if (isBlack(leftChild(sibling)) && isBlack(rightChild(sibling))) {
					setColor(sibling, red);
					t = getParent(t);
					if (isRed(t)) {
						setColor(t, black);
						break;
					}
				} else {
					if (isBlack(leftChild(sibling))) {
						setColor(rightChild(sibling), black);
						setColor(sibling, red);
						leftRotate(root, sibling);
						sibling = getSibling(t);
					}
					setColor(sibling, getColor(getParent(t)));
					setColor(leftChild(sibling), black);
					setColor(getParent(t), black);
					rightRotate(root, t = getParent(t));
					t = getParent(t);
					break;
				}
			}
		}
		if (getParent(t) == nullptr)
			root = t;
		while(t != nullptr) {
			updateHeight(t);
			t = getParent(t);
		}
		setColor(root, black);
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

	node * remove(node * t, T t_key)
	{
		node * cur = find(t, t_key);
		if (cur == nullptr)
			return t;
		if (leftChild(cur) != nullptr && rightChild(cur) != nullptr) {
			node * toDel = findMax(leftChild(cur));
			copyData(cur, toDel);
			cur = toDel;
		}

		node * pullUp = leftChild(cur) == nullptr ? rightChild(cur) : leftChild(cur);
		if (pullUp != nullptr) {
			if (getParent(cur) == nullptr)
				t = pullUp;
			else if (leftChild(getParent(cur)) == cur)
				setLeft(getParent(cur), pullUp);
			else
				setRight(getParent(cur), pullUp);
			setParent(pullUp, getParent(cur));
			if (isBlack(cur))
				setColor(pullUp, black);
			setParent(cur, nullptr);
			setLeft(cur, nullptr);
			setRight(cur, nullptr);
		} else if (getParent(cur) == nullptr) {
			t = nullptr;
		} else {
			if (isBlack(cur))
				fixAfterDelete(t, cur);
		}
		deleteNode(cur);
		return t;
	}
public:
	RBtree()
			: _root(nullptr) {}

	~RBtree()
	{
		clearTree(_root);
	}

	RBtree(node * otherRoot) {
			_root = otherRoot;
			return;
	}

	T getValue() {
			if (_root != nullptr)
					return *_root->key;
			return T();
	}

	bool getColor() {
		if (_root != nullptr)
			return _root->color == red;
		return 0;
	}

	unsigned int getHeight() {
		if (_root != nullptr)
			return _root->height;
		return 0;
	}

	bool isNull() {
			return _root == nullptr;
	}

	RBtree *getLeftNodeTree() {
			return new RBtree(_root->left);
	}

	RBtree *getRightNodeTree() {
			return new RBtree(_root->right);
	}

	RBtree (const RBtree & other)
	{
		_root = copyTree(nullptr, other._root);
	}

	RBtree&operator=(const RBtree & other)
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

#endif //BST_RED_BLACK_TREE_HPP
