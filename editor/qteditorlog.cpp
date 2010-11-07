#include "qteditorlog.h"
#include <QListWidgetItem>

QtEditorLog::QtEditorLog(QWidget *parent) :
	QListWidget(parent)
{
	setObjectName("loggerWidget");
}

void QtEditorLog::addLog(int severity, std::string log)
{
	QString iconName;

	if (severity < 2)
		iconName = ":/logs/info";
	else if (severity == 2)
		iconName = ":/logs/warning";
	else if (severity == 3)
		iconName = ":/logs/error";
	else
		iconName = ":/logs/fatal";

	QIcon icon(iconName);
	QListWidgetItem *item =new QListWidgetItem(icon, QString::fromStdString(log));

	addItem(item);

	setCurrentRow(count() - 1);
}
