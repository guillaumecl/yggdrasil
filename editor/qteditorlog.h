#pragma once

#include "qtcore/qtcore.h"
#include <QListWidget>

class QtEditorLog: public QListWidget, public core::QtCoreLogger
{
public:
	QtEditorLog(QWidget *parent);

	virtual void addLog(int severity, std::string log);
};
