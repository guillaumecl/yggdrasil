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
#include "glwidget.h"

#include <QTimer>
#include <QTimerEvent>

#include <iostream>

#include "exception.h"
#include "core.h"

namespace core
{

GLWidget::GLWidget(QWidget *parent, const char *name) :
	QGLWidget(QGLFormat(QGL::AlphaChannel), parent),
	drawFunc(NULL),
	inputFunc(NULL),
	runningTimer(-1)
{
	setWindowTitle(name);
}


GLWidget::~GLWidget()
{
}

void GLWidget::setFrameRate(double pFrameRate)
{
	int time;
	if (runningTimer != -1)
		killTimer(runningTimer);

	time = (int)(1000/pFrameRate);
	runningTimer = startTimer((int)(1000/pFrameRate));
}

void GLWidget::resizeGL(int width, int height)
{
	Core::getDrawManager()->initGraphics(width,height);
}

void GLWidget::paintGL()
{
	DrawManager *draw = Core::getDrawManager();

	draw->beginDraw();

	if (drawFunc)
		drawFunc();

	draw->endDraw();
}

void GLWidget::keyPressEvent(QKeyEvent *e)
{

}

void GLWidget::timerEvent(QTimerEvent *event)
{
	updateGL();
	if (inputFunc)
		inputFunc();
}

void GLWidget::setFuncs(void (*pDrawFunc)(), void (*pInputFunc)())
{
	drawFunc = pDrawFunc;
	inputFunc = pInputFunc;

	setFrameRate(60);
}

}
