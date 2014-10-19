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

#include "common/exception.h"
#include "common/core.h"
#include "qtdrawglmanager.h"

namespace draw
{

using namespace core;

GLWidget::GLWidget(QWidget *parent, const char *name) :
	QGLWidget(QGLFormat(QGL::AlphaChannel), parent)
{
	setWindowTitle(name);
}


GLWidget::~GLWidget()
{
}


void GLWidget::resizeGL(int width, int height)
{
	Core::getDrawManager()->initGraphics(width, height);
}

void GLWidget::paintGL()
{
	Core::getCore()->mainLoopIteration();
}

}
