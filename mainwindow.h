#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLayout>
#include <QGridLayout>
#include <QApplication>
#include <QCoreApplication>
#include <QLabel>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QTabWidget>
#include <QFont>
#include "inputSideBar.h"
#include "graphicsViewZoom.h"
#include "vector.h"
#include "graphTab.h"
#include "treePainter.h"
#include "avl_tree.h"
#include "treap.h"
#include "splay_tree.h"
#include "red_black_tree.h"

class MainWindow : public QMainWindow {
	Q_OBJECT
public:
	MainWindow(QWidget *parent = nullptr);
	~MainWindow();
private:
	QWidget *_baseWindow;
	void setStyle();
	void updateInsert(long long value);
	void updateRemove(long long value);
	QTabWidget *_graphTabs;
	inputSideBar *_inputSideBar;
	vector<graphTab *> _tabs;
	treePainter<AVLtree<long long> > *_AVLtreePainter;
	treePainter<RBtree<long long> > *_RBtreePainter;
	treePainter<treap<long long> > *_treapPainter;
	treePainter<SplayTree<long long> > *_splayTreePainter;
};
#endif // MAINWINDOW_H
