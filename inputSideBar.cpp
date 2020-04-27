#include "inputSideBar.h"

#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <QRegExp>
#include "errorDialog.h"

inputSideBar::inputSideBar(QWidget *parent):
	QWidget(parent)
{
	this->setFixedSize(250, 720);
	/*
	this->setStyleSheet(""
						"*{"
						"	background-color: orange;"
						"}");
	this->setAutoFillBackground(true);
	*/

	QGridLayout *baseLayout = new QGridLayout(this);

	QLabel *insertionLabel = new QLabel("Insert new elements:", this);
	baseLayout->addWidget(insertionLabel, 0, 0, 2, 3, Qt::AlignVCenter);

	_insertInputLine = new QLineEdit(this);
	_insertInputLine->setPlaceholderText("Value to insert");
	baseLayout->addWidget(_insertInputLine, 1, 0, 1, 3, Qt::AlignVCenter);

	QPushButton *inputButtonConfirm = new QPushButton("Ok", this);
	baseLayout->addWidget(inputButtonConfirm, 1, 0, 2, 3, Qt::AlignVCenter);
	QObject::connect(inputButtonConfirm, &QPushButton::clicked, this, &inputSideBar::_checkInsert);

	QLabel *removeLabel = new QLabel("Remove elements:", this);
	baseLayout->addWidget(removeLabel, 5, 0, 2, 3, Qt::AlignVCenter);

	_removeInputLine = new QLineEdit(this);
	_removeInputLine->setPlaceholderText("Value to remove");
	baseLayout->addWidget(_removeInputLine, 6, 0, 1, 3, Qt::AlignVCenter);

	QPushButton *removeButtonConfirm = new QPushButton("Ok", this);
	baseLayout->addWidget(removeButtonConfirm, 6, 0, 2, 3, Qt::AlignVCenter);
	QObject::connect(removeButtonConfirm, &QPushButton::clicked, this, &inputSideBar::_checkRemove);
}

void inputSideBar::_checkInsert()
{
	QRegExp intRe("\\d*");
	QString text = _insertInputLine->text();
	if (text.length() == 0)
		return;
	if (!intRe.exactMatch(text) || text.length() > 18) {
		if (text[0] == '-') {
			QString substr = text.mid(1, text.length()-1);
			if (!intRe.exactMatch(substr) || substr.length() > 18) {
				QDialog* errorBox = new ErrorDialog("Invalid integer input!");
				errorBox->exec();
				this->setFocus();
			}
			emit this->acceptInsert(text.toLongLong());
			return;
		} else {
			QDialog* errorBox = new ErrorDialog("Invalid integer input!");
			errorBox->exec();
			this->setFocus();
		}
		return;
	}
	emit this->acceptInsert(text.toLongLong());
}

void inputSideBar::_checkRemove()
{
	QRegExp intRe("\\d*");
	QString text = _removeInputLine->text();
	if (text.length() == 0)
		return;
	if (!intRe.exactMatch(text) || text.length() > 18) {
		if (text[0] == '-') {
			QString substr = text.mid(1, text.length()-1);
			if (!intRe.exactMatch(substr) || substr.length() > 18) {
				QDialog* errorBox = new ErrorDialog("Invalid integer input!");
				errorBox->exec();
				this->setFocus();
			}
			emit this->acceptRemove(text.toLongLong());
			return;
		} else {
			QDialog* errorBox = new ErrorDialog("Invalid integer input!");
			errorBox->exec();
			this->setFocus();
		}
		return;
	}
	emit this->acceptRemove(text.toLongLong());
}
