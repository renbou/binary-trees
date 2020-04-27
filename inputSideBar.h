#ifndef INPUTSIDEBAR_H
#define INPUTSIDEBAR_H

#include <QWidget>
#include <QLineEdit>

class inputSideBar: public QWidget {
	Q_OBJECT
public:
	inputSideBar(QWidget * parent = nullptr);

signals:
	void acceptInsert(long long t_value);
	void acceptRemove(long long t_value);

public slots:
	void _checkInsert();
	void _checkRemove();

private:
	QLineEdit *_insertInputLine;
	QLineEdit *_removeInputLine;
};

#endif // INPUTSIDEBAR_H
