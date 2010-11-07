#ifndef QTEDITORLOG_H
#define QTEDITORLOG_H

#include "qtcore.h"
#include <QListWidget>

class QtEditorLog: public QListWidget, public core::QtCoreLogger
{
public:
	QtEditorLog(QWidget *parent);

	virtual void addLog(int severity, std::string log);
};

#endif // QTEDITORLOG_H
