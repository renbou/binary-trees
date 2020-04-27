#include "treePainter.h"
#include <QGraphicsTextItem>
#include <QFontMetrics>
#include "maths.h"

template<typename T>
treePainter<T>::treePainter(QGraphicsScene * t_scene, unsigned int treeType)
	: _nodeFont("arial", 14)
{
	_treeScene = t_scene;
	_tree = new T;
	_treeType = treeType;
	_treeHeight = 0;
	_nodeHeight = 50;
	_nodeWidth = 80;
	_nodeSpace = 70;
}

template<typename T>
void treePainter<T>::drawTree(T * treeNode, unsigned int left, unsigned int right, unsigned int t_y) {
	if (treeNode->isNull())
		return;
	if (right == -1) {
		unsigned int num = Maths::intPow(2, _treeHeight);
		unsigned int size = num*(_nodeWidth+_nodeSpace)-_nodeSpace;
		right = size;
	}
	unsigned int curX = (left+right)/2;
	drawRect(curX, t_y, QString::number(treeNode->getValue()));
	drawTree(treeNode->getLeftNodeTree(), left, curX-_nodeSpace/2, t_y+_nodeHeight*2);
	drawTree(treeNode->getRightNodeTree(), curX+_nodeSpace/2, right, t_y+_nodeHeight*2);
	return;
}

template<typename T>
void treePainter<T>::drawRect(unsigned int x, unsigned int y, QString text) {
	unsigned truX = x-_nodeWidth/2;
	unsigned truY = y-_nodeHeight/2;
	_treeScene->addRect(truX, truY, _nodeWidth, _nodeHeight);
	QGraphicsTextItem *nodeText = _treeScene->addText(text);
	QFontMetrics fm(_nodeFont);
	unsigned int textW = static_cast<unsigned int>(fm.horizontalAdvance(text));
	unsigned int textH = static_cast<unsigned int>(fm.height());
	nodeText->setPos(x-textW/2, y-textH/2);
	return;
}

template<typename T>
void treePainter<T>::addNode(long long value) {
	_tree->insert(value);
	drawTree(_tree, 0, -1, -200);
	return;
}

template<typename T>
void treePainter<T>::removeNode(long long value) {
	_tree->remove(value);
	drawTree(_tree, 0, -1, -200);
	return;
}
