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


#include <QApplication>
#include "yggdrasil_editor.h"
#include <QMessageBox>
#include <QTranslator>

int main(int argc, char *argv[])
{
	//qInstallMsgHandler(myMessageOutput);
	Q_INIT_RESOURCE(application);
	QApplication app(argc, argv);

	try
	{
		QString locale = QLocale::system().name();

		QTranslator translator;
		translator.load(QString("yggdrasil_editor_") + locale);
		app.installTranslator(&translator);

		editor::yggdrasil_editor * mw = new editor::yggdrasil_editor();
		mw->show();
		return app.exec();
	}
	catch(const std::exception &e)
	{
		QMessageBox::warning(NULL, "Application",
							 e.what());
	}
}

