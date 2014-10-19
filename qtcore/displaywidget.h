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
#ifndef COREDISPLAYWIDGET_H
#define COREDISPLAYWIDGET_H

#include <QWidget>
#include <QDebug>

#include "common/drawmanager.h"

namespace core
{

/**
 *	@author Lightning Flik <flik@baobob.org>
 */
class DisplayWidget : public QWidget
{
public:
	DisplayWidget(QWidget *parent = NULL, const char *name = NULL);

	virtual ~DisplayWidget();
	virtual void setFuncs(void (*drawFunc)(), void (*inputFunc)());
	void paintFunc();
	virtual void setup();

	virtual void setFrameRate(double pFrameRate);

protected:
	virtual void keyPressEvent(QKeyEvent *e);

	void timerEvent(QTimerEvent *event);

private:
	void (*drawFunc)();
	void (*inputFunc)();

	int runningTimer;

	QWidget *underlyingWidget;
};

}

#endif
