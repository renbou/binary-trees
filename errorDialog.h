#ifndef ERRORDIALOG_H
#define ERRORDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QHBoxLayout>

class ErrorDialog : public QDialog
{
public:
	ErrorDialog(const QString& text);
};

#endif // ERRORDIALOG_H
