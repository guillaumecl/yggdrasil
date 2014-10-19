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

#include "qtcore.h"
#include "log.h"
#include "qtdrawmanagerbase.h"

#include <iostream>

#include <QDebug>

namespace core
{

static int paramCount = 0;
static char *params[] = {"QtCore"};

QtCore::QtCore() :
	Core(),
	app(NULL),
	widget(NULL),
	privateApp(true)
{
	if (!QApplication::instance()) {
		log() << "Creating QApplication...";
		app = new QApplication(paramCount,params);
		app->connect(app, SIGNAL(lastWindowClosed()), app, SLOT(quit()));
	} else {
		privateApp = false;
		app = (QApplication *) QApplication::instance();
	}
}

QtCore::~QtCore()
{
	log() << "Destructing the Widget...";
	delete widget;

	if (privateApp) {
		log() << "Destructing the QApplication...";
		delete app;
	}
}

DisplayWidget *QtCore::getWidget()
{
	return widget;
}

void QtCore::setup(DrawManager &draw, SoundManager &sound)
{
	m_draw = &draw;
	m_sound = &sound;

	widget = new DisplayWidget(NULL,"Yggdrasil -- QtCore");

	widget->setup();

	widget->resize(1024,768);
}

double QtCore::frameRate()
{
	return 0;
}

void QtCore::setFrameRate(double frameRate)
{
	if (frameRate > 1)
		widget->setFrameRate(frameRate);
	else
		widget->setFrameRate(0.5);
}

void QtCore::mainLoopIteration()
{
	widget->paintFunc();
}

void QtCore::mainLoop(void (*drawFunc)(), void (*inputFunc)())
{
	widget->setFuncs(drawFunc,inputFunc);

	log() << "Showing the Widget...";
	widget->show();

	app->exec();
}

/**
  * Sends a log line to the core. The core is free not to reimplement this method if
  * no special logging ability is needed.
  * @param severity the severity (1 = info, 2 = warning, 3 = error, 4 = fatal)
  */
void QtCore::showLog(int severity, std::string log)
{
	if (!app->activeWindow())
		return;

	QtCoreLogger *logger = dynamic_cast<QtCoreLogger*>(app->activeWindow()->findChild<QWidget*>("loggerWidget"));

	if (logger)
		logger->addLog(severity, log);
	else
		std::cerr << "No logger found to log message." << std::endl;
}

}


extern "C"
{



#ifdef WIN32

#ifdef BUILD_DLL
#define DLL_EXPORT __declspec(dllexport)
#else
#define DLL_EXPORT
#endif

#else
#define DLL_EXPORT
#endif

	using namespace core;
	/**
	Those functions are exported to be the plugin interface.
	 */

	/**
	Create a draw manager
	 */
	Core * DLL_EXPORT create()
	{
		return new QtCore();
	}

	const char * DLL_EXPORT author()
	{
		return "Lightning Flik <flik@baobob.org>";
	}

	const char * DLL_EXPORT type()
	{
		return "core";
	}

	const char * DLL_EXPORT description()
	{
		return "A portable core that relies on Qt.";
	}

	const char * DLL_EXPORT name()
	{
		return "Qt Core";
	}
}
