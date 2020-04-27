#ifndef TREEPAINTER_H
#define TREEPAINTER_H

#include <QGraphicsScene>
#include <QFontMetrics>
#include <QGraphicsTextItem>
#include <QFont>
#include <QPen>
#include "graphicsViewZoom.h"
#include "maths.h"
#include "couple.h"
#include "avl_tree.h"

template<typename T>
class treePainter {
private:
	T *_tree;
	graphicsViewZoom *_treeScene;
	int _treeHeight = 0;
	int _treeType;
	int _nodeWidth, _nodeHeight, _nodeSpace;
	QFont _nodeFont;
public:
	treePainter(graphicsViewZoom * t_view, unsigned int treeType)
	: _nodeFont("arial", 11) {
		_treeScene = t_view;
		_tree = new T;
		_treeType = treeType;
		_treeHeight = 0;
		_nodeHeight = 50;
		_nodeWidth = 80;
		_nodeSpace = 50;
	}
	void addNode(long long value) {
		_tree->insert(value);
		_treeHeight = _tree->getHeight();
		_treeScene->scene()->clear();
		drawTree(_tree, 0, -1, -200);
		return;
	}
	void removeNode(long long value)  {
		_tree->remove(value);
		_treeHeight = _tree->getHeight();
		_treeScene->scene()->clear();
		drawTree(_tree, 0, -1, -200);
		return;
	}
	void drawTree(T * treeNode, int left, int right, int t_y) {
		QPen rectPen(QBrush("black"), 4);
		if (treeNode->isNull())
			return;
		if (right == -1) {
			int num = Maths::intPow(2, _treeHeight-1).second;
			int size = num*(_nodeWidth+_nodeSpace)-_nodeSpace;
			left = -size/2;
			right = size/2;
		}
		int curX = (left+right)/2;
		if (!treeNode->getLeftNodeTree()->isNull()) {
			QPoint leftRectEdge = {curX-_nodeWidth/2, t_y+_nodeHeight/2};
			QPoint leftChildMid = {(left + curX-_nodeSpace/2)/2,  t_y+_nodeHeight*2-_nodeHeight/2};
			_treeScene->scene()->addLine(leftRectEdge.x(), leftRectEdge.y(), leftChildMid.x(), leftChildMid.y(), rectPen);
		}
		if (!treeNode->getRightNodeTree()->isNull()) {
			QPoint rightRectEdge = {curX+_nodeWidth/2, t_y+_nodeHeight/2};
			QPoint rightChildMid = {(curX+_nodeSpace/2 + right)/2,  t_y+_nodeHeight*2-_nodeHeight/2};
			_treeScene->scene()->addLine(rightRectEdge.x(), rightRectEdge.y(), rightChildMid.x(), rightChildMid.y(), rectPen);
		}
		drawTree(treeNode->getLeftNodeTree(), left, curX-_nodeSpace/2, t_y+_nodeHeight*2);
		drawTree(treeNode->getRightNodeTree(), curX+_nodeSpace/2, right, t_y+_nodeHeight*2);
		drawRect(curX, t_y, QString::number(treeNode->getValue()), treeNode->getColor());
		return;
	}

	void drawRect(int x, int y, QString text, int color)  {
		QPen rectPen(Qt::black, 4);
		QBrush rectBrush(QColor(35, 35, 35));
		if (color == 1) {
			rectPen = QPen(QColor(192, 57, 43), 4);
			rectBrush = QBrush(QColor(111, 31, 21));
		}
		int truX = x-_nodeWidth/2;
		int truY = y-_nodeHeight/2;
		_treeScene->scene()->addRect(truX, truY, _nodeWidth, _nodeHeight, rectPen, rectBrush);
		if(text.length() > 10)
			text = text.mid(0, 10)+'\n'+text.mid(10, text.length()-10);
		QGraphicsTextItem *nodeText = _treeScene->scene()->addText(text);
		QRectF boundingRect = nodeText->sceneBoundingRect();
		nodeText->setPos(x-boundingRect.width()/2, y-boundingRect.height()/2);
		return;
	}
};

#endif // TREEPAINTER_H
