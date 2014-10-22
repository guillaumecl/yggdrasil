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
#include "displaywidget.h"
#include "qtdrawmanagerbase.h"

#include <QTimer>
#include <QTimerEvent>

#include <iostream>

#include "common/exception.h"
#include "common/core.h"

#include <QHBoxLayout>

namespace core
{

DisplayWidget::DisplayWidget(QWidget *parent, const char *name) :
	QWidget(parent),
	drawFunc(NULL),
	inputFunc(NULL),
	runningTimer(-1)
{
	setWindowTitle(name);

	QHBoxLayout *layout = new QHBoxLayout();

	underlyingWidget = ((draw::QtDrawManagerBase*)Core::getDrawManager())->getWidget(this, name);
	layout->addWidget(underlyingWidget);
	layout->setMargin(0);
	setMouseTracking(true);

	setLayout(layout);
}


DisplayWidget::~DisplayWidget()
{
}

void DisplayWidget::setFrameRate(double pFrameRate)
{
	if (runningTimer != -1)
		killTimer(runningTimer);

	runningTimer = startTimer(1000/pFrameRate);
}

void DisplayWidget::keyPressEvent(QKeyEvent * /*e*/)
{

}

void DisplayWidget::timerEvent(QTimerEvent * /*event*/)
{
	((draw::QtDrawManagerBase*)Core::getDrawManager())->update();
	if (inputFunc)
		inputFunc();
}

void DisplayWidget::setFuncs(void (*pDrawFunc)(), void (*pInputFunc)())
{
	drawFunc = pDrawFunc;
	inputFunc = pInputFunc;

	setFrameRate(60);
}

void DisplayWidget::paintFunc()
{
	draw::DrawManager *draw = Core::getDrawManager();

	draw->beginDraw();

	if (drawFunc)
		drawFunc();

	draw->endDraw();
}

void DisplayWidget::setup()
{
	((draw::QtDrawManagerBase*)Core::getDrawManager())->setup();
}

}
