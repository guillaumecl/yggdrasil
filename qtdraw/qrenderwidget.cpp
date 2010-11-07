#include "qrenderwidget.h"

#include "qtcore.h"

#include <QResizeEvent>

#include <iostream>

namespace draw
{

QRenderWidget::QRenderWidget(QWidget *parent) :
	QWidget(parent)
{
	setMouseTracking(true);
}

QRenderWidget::~QRenderWidget()
{

}

void QRenderWidget::paintEvent (QPaintEvent *event)
{
	core::Core::getCore()->mainLoopIteration();
}

void QRenderWidget::resizeEvent (QResizeEvent *event)
{
	core::Core::getDrawManager()->initGraphics(width(), height());
}

}
