/***************************************************************************
 *   Copyright (C) 2007 by Lightning Flik   *
 *   flik@baobob.org   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#include <QResizeEvent>
#include "glwrapper.h"

#include <iostream>

namespace editor {


inline static int min(int x, int y)
{
	if(x < y)
		return x;
	return y;
}

inline static int max(int x, int y)
{
	if(x > y)
		return x;
	return y;
}

GLWrapper *GLWrapper::editor = NULL;
bool GLWrapper::widgetSetup = false;

void GLWrapper::drawFunc()
{
	if(editor)
		editor->baseDrawFunction();
}

void GLWrapper::inputFunc()
{
	if(editor)
		editor->baseInputFunction();
}


void GLWrapper::setupUi()
{
	vboxLayout = new QVBoxLayout(this);
	vboxLayout->setSpacing(0);
	vboxLayout->setMargin(0);

	hboxLayout = new QHBoxLayout();
	hboxLayout->setSizeConstraint(QLayout::SetMaximumSize);
	hboxLayout->setSpacing(0);
	hboxLayout->setMargin(0);

	verticalScrollBar = new QScrollBar(this);
	verticalScrollBar->setObjectName(QString::fromUtf8("verticalScrollBar"));
	verticalScrollBar->setPageStep(100);
	verticalScrollBar->setSliderPosition(0);
	verticalScrollBar->setOrientation(Qt::Vertical);

	hboxLayout->addWidget(new QWidget(),-1,Qt::AlignLeft);
	hboxLayout->addWidget(hWidget = new QWidget(),-1,Qt::AlignLeft);
	hboxLayout->addWidget(new QWidget(),-1,Qt::AlignRight);
	hboxLayout->addWidget(verticalScrollBar,-1,Qt::AlignRight);
	vboxLayout->addLayout(hboxLayout);

	horizontalScrollBar = new QScrollBar(this);
	horizontalScrollBar->setObjectName(QString::fromUtf8("horizontalScrollBar"));
	horizontalScrollBar->setPageStep(100);
	horizontalScrollBar->setOrientation(Qt::Horizontal);

	hScrollSmall =  new QWidget(this);
	hScrollSmall->setFixedWidth(0);

	QHBoxLayout *hLayoutScroll = new QHBoxLayout();
	hLayoutScroll->addWidget(horizontalScrollBar);
	hLayoutScroll->addWidget(hScrollSmall);
	vboxLayout->addLayout(hLayoutScroll);


	QSize size(537, 472);
	size = size.expandedTo(minimumSizeHint());
	resize(size);

	QMetaObject::connectSlotsByName(this);

	setAttribute(Qt::WA_NativeWindow);
}

GLWrapper::GLWrapper(core::QtCore *pCore, draw::DrawManager *pDraw, sound::SoundManager *pSound, core::DisplayWidget *pDisplayWidget) :
	core(pCore),
	draw(pDraw),
	sound(pSound),
	displayWidget(pDisplayWidget),
	moving(false),
	scale(1.0)
{
	setupUi();

	setAcceptDrops(true);

	setMouseTracking(true);

	setFocusPolicy(Qt::WheelFocus);

	if(!widgetSetup)
	{
		editor = NULL;
		displayWidget->setFuncs(GLWrapper::drawFunc,GLWrapper::inputFunc);
		displayWidget->setMouseTracking(true);
		widgetSetup = true;
	}
}

void GLWrapper::resizeEvent (QResizeEvent *event)
{
	int w,h;
	if(!isVisible())
		return;

	if(!hasObject())
	{
		horizontalScrollBar->setVisible(false);
		verticalScrollBar->setVisible(false);
		hWidget->setVisible(false);
		displayWidget->setMaximumSize(QSize(0,0));
		return;
	}

	QSize newSize = event->size();

	w = (int)(insideWidth() * scale) - newSize.width();
	if(w > 0)
	{
		horizontalScrollBar->setVisible(true);
		horizontalScrollBar->setMaximum(w);
		horizontalScrollBar->setSingleStep(max(horizontalScrollBar->maximum() / 200,1));
		horizontalScrollBar->setPageStep(max(horizontalScrollBar->maximum() / 20,200));
	}
	else
	{
		horizontalScrollBar->setVisible(false);
		horizontalScrollBar->setMaximum(0);
	}

	h = (int)(insideHeight() * scale) - newSize.height();
	if(h > 0)
	{
		verticalScrollBar->setVisible(true);
		verticalScrollBar->setMaximum(h);
		verticalScrollBar->setSingleStep(max(verticalScrollBar->maximum() / 200,1));
		verticalScrollBar->setPageStep(max(verticalScrollBar->maximum() / 20,200));
		hWidget->setVisible(true);
	}
	else
	{
		verticalScrollBar->setVisible(false);
		verticalScrollBar->setMaximum(0);
		hWidget->setVisible(false);
	}

	/*
		Adjust the size according to the presence of the scrollbars. If we don't do this,
	we lose about 16 pixels of width/height (they're not attainable by scrolling)
	*/
	if(w > 0 && verticalScrollBar->isVisible())
		verticalScrollBar->setMaximum(verticalScrollBar->maximum() + horizontalScrollBar->height());
	if(h > 0 && horizontalScrollBar->isVisible())
		horizontalScrollBar->setMaximum(horizontalScrollBar->maximum() + verticalScrollBar->width());

	if(w <= 0)
	{
		newSize.setWidth( (int)(insideWidth() * scale));
		horizontalScrollBar->setValue(0);
	}

	if(h <= 0)
	{
		newSize.setHeight( (int)(insideHeight() * scale));
		verticalScrollBar->setValue(0);
	}

	hScrollSmall->setFixedWidth(w > 0 && h > 0 ? verticalScrollBar->width() : 0);
	hScrollSmall->setFixedHeight(horizontalScrollBar->isVisible() ? horizontalScrollBar->height() : 0);
	displayWidget->setMaximumSize(newSize);
}


GLWrapper::~GLWrapper()
{

}


void GLWrapper::baseDrawFunction()
{
	if(hasObject() && isVisible())
	{
		draw->setGraphicOrigin(hValue(), verticalScrollBar->maximum() - vValue());
		draw->scale(scale);

		drawFunction();

		draw->endScale();
		draw->restoreGraphicOrigin();
	}
}

void GLWrapper::baseInputFunction()
{
	if(hasObject() && isVisible())
		inputFunction();
}

void GLWrapper::mousePressEvent(QMouseEvent *event)
{
	if(event->button() == Qt::MidButton)
	{
		if(!event->isAccepted())
		{
			moveStart = event->globalPos();
			scrollStart = QPoint(hValue(),vValue());
			moving = true;
			QApplication::setOverrideCursor(QCursor(Qt::SizeAllCursor));
		}
	}
}

void GLWrapper::mouseMoveEvent(QMouseEvent *event)
{
	if(!event->isAccepted())
	{
		QPoint pos = getInsidePosition(event->pos());
		if(isValidPosition(pos))
			emit mouseMoved(pos);
	}
	if(moving)
	{
		QPoint diffPos = event->globalPos() - moveStart;

		QPoint newPos = scrollStart - diffPos;

		horizontalScrollBar->setValue(newPos.x());
		verticalScrollBar->setValue(newPos.y());
	}
}

void GLWrapper::mouseReleaseEvent(QMouseEvent *event)
{
	if(event->button() != Qt::MidButton)
		return;
	if(!event->isAccepted() && moving)
	{
		moving = false;
		event->accept();
		QApplication::restoreOverrideCursor();
	}
}

void GLWrapper::wheelEvent(QWheelEvent *event)
{
	if (event->orientation() == Qt::Horizontal)
	{
		event->ignore();
		return;
	}
	event->accept();

	double x = (hValue() + event->x()) / scale;
	double y = (vValue() + event->y()) / scale;

	if(event->delta() > 0)
	{
		if(scale < 40)
			scale *= 1.5;
	}
	else
	{
		if(scale > 0.08)
			scale /= 1.5;
	}

	if(scale < 1.5 && scale > 1/1.5)
		scale = 1.0;

	QResizeEvent q(size(),size()) ;
	resizeEvent(&q);

	horizontalScrollBar->setValue( (int)(x * scale) - event->x());
	verticalScrollBar->setValue( (int)(y * scale) - event->y());

	QPoint pos = getInsidePosition(event->pos());
	if(isValidPosition(pos))
		emit mouseMoved(pos);
}

QPoint GLWrapper::getInsidePosition(QPoint relPos)
{
	relPos = displayWidget->mapFrom(this,relPos);
	int x = (int)((hValue() + relPos.x()) / scale);
	int y = (int)((double)insideHeight() - ((vValue() + relPos.y() ) / scale));

	return QPoint(x,y);
}

bool GLWrapper::isValidPosition(QPoint insidePos)
{
	if(!hasObject())
		return false;

	if(insidePos.x() >= 0 && insidePos.y() >= 0 &&
		insidePos.x() < insideWidth() && insidePos.y() < insideHeight())
		return true;
	return false;
}

void GLWrapper::activate()
{
	if(!displayWidget)
		return;

	displayWidget->setParent(this);
	hboxLayout->insertWidget(2,displayWidget,10000,0);
	core->setFrameRate(30);
	editor = this;
	displayWidget->setFuncs(GLWrapper::drawFunc,GLWrapper::inputFunc);
	displayWidget->setup();
	displayWidget->setVisible(true);
}

void GLWrapper::deactivate()
{
	if(!displayWidget)
		return;
	editor = NULL;
	hboxLayout->removeWidget(displayWidget);
	displayWidget->setVisible(false);
	displayWidget->setParent(NULL);
}

void GLWrapper::showEvent(QShowEvent *event)
{
	activate();

	QResizeEvent q(size(),size()) ;
	resizeEvent(&q);

	Q_UNUSED(event);
}

void GLWrapper::hideEvent(QHideEvent *event)
{
	deactivate();
	Q_UNUSED(event);
}


int GLWrapper::hValue()
{
	return horizontalScrollBar->value();
}

int GLWrapper::vValue()
{
	return verticalScrollBar->value();
}

QSize GLWrapper::sizeHint() const
{
	return QSize((int)(insideWidth() * scale), (int)(insideHeight() * scale));
}

}



