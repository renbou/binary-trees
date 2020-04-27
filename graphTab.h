#ifndef GRAPHTAB_H
#define GRAPHTAB_H

#include <QVBoxLayout>
#include <QWidget>
#include "graphicsViewZoom.h"

class graphTab : public QWidget {
	Q_OBJECT
public:
	graphTab()
	{
		QVBoxLayout *mainLayout = new QVBoxLayout(this);
		view = new graphicsViewZoom(new QGraphicsScene(-10000, -10000, 20000, 20000));
		view->setFixedSize(995, 710);
		mainLayout->addWidget(view);
	}
	graphicsViewZoom *view;
};

#endif // GRAPHTAB_H
