/*
_graphTabs = new QTabWidget(_baseWindow);
_graphTabs->setFixedSize(995, 710);

_graphs.resize(4);

for (unsigned int i= 0; i < 1; i++) {
		_graphs[i] = new graphicsViewZoom(new QGraphicsScene(-10000, -10000, 20000, 20000, _baseWindow), _baseWindow);
		_graphs[i]->setFixedSize(996, 710);
		_graphTabs->addTab(_graphs[i],
										   (i == 0 ? "AVL" : (i == 1 ? "Red-Black" : (i == 2 ? "Splay" : "Treap"))));
}

baseLayout->addWidget(_graphTabs, 0, 0, 5, 5, Qt::AlignBottom);
/////
_graphScenes.resize(1);
_graphs.resize(1);
_graphScenes[0] = new QGraphicsScene(-10000, -10000, 20000, 20000, _baseWindow);
_graphs[0] = new graphicsViewZoom(new QGraphicsScene(-10000, -10000, 20000, 20000, _baseWindow), _baseWindow);
_graphs[0]->setFixedSize(996, 710);
baseLayout->addWidget(_graphs[0], 0, 0, 5, 5, Qt::AlignBottom);
tmp = new QGraphicsView(_graphScenes[0], _baseWindow);
tmp->setFixedSize(996, 710);
baseLayout->addWidget(tmp, 0, 0, 5, 5, Qt::AlignBottom);
tmp->scene()->addEllipse(10, 10, 100, 100);
/////
_AVLtreePainter = new treePainter<AVLtree<long long> >(_graphs[0], 1);

_AVLtreePainter->addNode(10);
_AVLtreePainter->addNode(-10);
*/

/*
void MainWindow::updateTreesInsert(long long value) {
	graphScene->addRect(10, 10, 10, 10);
	//_AVLtreePainter->addNode(value);
	//_graphScenes[0]->addRect(0, 0, 100, 100);
}
*/

/*

void MainWindow::updateTreesRemove(long long value) {
	_AVLtreePainter->removeNode(value);
}
*/

/*
MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	this->setStyle();

	_baseWindow = new QWidget(this);
	_baseWindow->setFixedSize(1280, 720);
	QGridLayout *baseLayout = new QGridLayout(_baseWindow);

	graphScene = new QGraphicsScene(-10000, -10000, 20000, 20000);
	tmp = new QGraphicsView(graphScene, _baseWindow);
	baseLayout->addWidget(tmp, 0, 0, 5, 5);
	graphScene->addRect(10, 10, 10, 10);

	_inputSideBar = new inputSideBar(this);
	baseLayout->addWidget(_inputSideBar, 0, 6, 1, 4, Qt::AlignRight);

	QObject::connect(_inputSideBar, &inputSideBar::acceptInsert, this, &MainWindow::updateTreesInsert);
	QObject::connect(_inputSideBar, &inputSideBar::acceptInsert, this, &MainWindow::updateTreesRemove);

	this->setCentralWidget(_baseWindow);
}
*/
