#include "errorDialog.h"

ErrorDialog::ErrorDialog(const QString& text)
{
	setStyleSheet("* { font-size: 20px; }");
	QHBoxLayout* layout = new QHBoxLayout(this);
	QLabel* label = new QLabel(text, this);
	layout->addWidget(label, Qt::AlignCenter);
	setModal(true);
	setWindowTitle("Error");
}
