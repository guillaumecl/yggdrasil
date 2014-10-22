#pragma once

#include <QWidget>

namespace draw
{

class QRenderWidget : public QWidget
{
public:
	QRenderWidget(QWidget *parent = 0);
	~QRenderWidget();
protected:
	void paintEvent(QPaintEvent *event);
	void resizeEvent(QResizeEvent *event);
};

}
