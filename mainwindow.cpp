#include "mainwindow.h"
#include "graphTab.h"
#include <QGraphicsTextItem>

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	this->setStyle();

	_baseWindow = new QWidget(this);
	_baseWindow->setFixedSize(1280, 720);
	QGridLayout *baseLayout = new QGridLayout(_baseWindow);


	_graphTabs = new QTabWidget(_baseWindow);
	_graphTabs->setFixedSize(995, 710);

	_tabs.resize(4);

	for (unsigned int i= 0; i < 4; i++) {
			_tabs[i] = new graphTab;
			_graphTabs->addTab(_tabs[i],
											   (i == 0 ? "AVL" : (i == 1 ? "Red-Black" : (i == 2 ? "Splay" : "Treap"))));
	}

	baseLayout->addWidget(_graphTabs, 0, 0, 5, 5);

	_AVLtreePainter = new treePainter<AVLtree<long long> >(_tabs[0]->view, 1);
	_RBtreePainter = new treePainter<RBtree<long long> >(_tabs[1]->view, 2);
	_splayTreePainter = new treePainter<SplayTree<long long> >(_tabs[2]->view, 3);
	_treapPainter = new treePainter<treap<long long> >(_tabs[3]->view, 4);

	_inputSideBar = new inputSideBar(this);
	baseLayout->addWidget(_inputSideBar, 0, 6, 1, 4, Qt::AlignRight);
	QObject::connect(_inputSideBar, &inputSideBar::acceptInsert, this, &MainWindow::updateInsert);
	QObject::connect(_inputSideBar, &inputSideBar::acceptRemove, this, &MainWindow::updateRemove);

	this->setCentralWidget(_baseWindow);
}

MainWindow::~MainWindow() {}

void MainWindow::updateInsert(long long value) {
	_AVLtreePainter->addNode(value);
	_RBtreePainter->addNode(value);
	_splayTreePainter->addNode(value);
	_treapPainter->addNode(value);
	//_tabs[0]->view->scene()->addRect(value, value, 100, 100);
}

void MainWindow::updateRemove(long long value) {
	_AVLtreePainter->removeNode(value);
	_RBtreePainter->removeNode(value);
	_splayTreePainter->removeNode(value);
	_treapPainter->removeNode(value);
}

void MainWindow::setStyle()
{
	static_cast<QApplication*>(QCoreApplication::instance())->
		  setStyleSheet(""
						"* {"
							"font-family: DejaVu sans;"
							"font-size: 4em;"
							"color: #d9d8ff;"
						"}"
						""
						"QWidget {"
							"background: #2c3e50;"
							"font-family: DejaVu sans;"
							"font-size: 10em;"
							"color: #bedaed;"
						"}"
						""
						".QPushButton {"
							"border-radius: 5%;"
							"height: 30%;"
							"width: 30%;"
							"border: 2px solid #2a6fb5;"
							"background: #4874a1;"
							"color: #ecf0f1;"
						"}"
						""
						".QPushButton:pressed {"
							"background: #1882ed"
						"}"
						".QLineEdit {"
							"border-radius: 0px;"
							"color: #000000;"
							"background: #61798f;"
						"}"
						".QLabel {"
							"font-size: 18px;"
							"color: #ecf0f1;"
							"font-family: Arial;"
						"}"
						""
	);
}
