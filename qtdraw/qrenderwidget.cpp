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
	Q_UNUSED(event);
	core::Core::getCore()->mainLoopIteration();
}

void QRenderWidget::resizeEvent (QResizeEvent *event)
{
	Q_UNUSED(event);
	core::Core::getDrawManager()->initGraphics(width(), height());
}

}
