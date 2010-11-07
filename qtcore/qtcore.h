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
#ifndef QTCORE_H
#define QTCORE_H

#include "core.h"

#include <QApplication>
#include <QMainWindow>

#include "displaywidget.h"

namespace core
{

/**
*	@brief A Core that uses Qt for input and output purposes.
*
* 	@author Lightning Flik <flik@baobob.org>
*/
class QtCore : public Core
{
public:
	QtCore();


	~QtCore();
	virtual void mainLoop(void (*drawFunc)(), void (*inputFunc)());
	virtual void mainLoopIteration();
	virtual void setup(DrawManager &draw, SoundManager &sound);
	virtual void setFrameRate(double frameRate);
	virtual double frameRate();

	virtual DisplayWidget *getWidget();

	/**
	  * Sends a log line to the core. The core is free not to reimplement this method if
	  * no special logging ability is needed.
	  * @param severity the severity (1 = info, 2 = warning, 3 = error, 4 = fatal)
	  */
	virtual void showLog(int severity, std::string log);
private:
	QApplication *app;
	DisplayWidget *widget;
	bool privateApp;
};

class QtCoreLogger
{
public:
	virtual void addLog(int severity, std::string log) = 0;
};

}

#endif
