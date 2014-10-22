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

#include <QtGui>
#include <QDebug>
#include "yggdrasil_editor.h"
#include "ui_main.h"

#include <QTextEdit>
#include <QTextStream>
#include <QCloseEvent>
#include <QContextMenuEvent>
#include <QFileDialog>

#include "gamedisplayer.h"
#include "objectdisplayer.h"
#include "property/propertywidget.h"

#include "common/archiver.h"
#include "common/exception.h"
#include "common/plugin.h"
#include "common/drawmanager.h"

#include "qteditorlog.h"

namespace editor
{

using namespace custom;

yggdrasil_editor::yggdrasil_editor() :
	core(NULL),
	draw(NULL),
	sound(NULL),
	displayWidget(NULL),
	corePlugin(NULL),
	drawPlugin(NULL),
	ui(new Ui_yggdrasil_editor)
{
	ui->setupUi(this);
	setAttribute(Qt::WA_DeleteOnClose);

	ui->dockLog->setWidget(new QtEditorLog(this));

	initEngine();

	ui->menuDocks->addAction(ui->dockScreen->toggleViewAction());
	ui->menuDocks->addAction(ui->dockObject->toggleViewAction());
	ui->menuDocks->addAction(ui->dockProperties->toggleViewAction());
	ui->menuDocks->addAction(ui->dockLog->toggleViewAction());

	ui->menuToolbars->addAction(ui->menuToolBar->toggleViewAction());
	ui->menuToolbars->addAction(ui->fileToolBar->toggleViewAction());
	ui->menuToolbars->addAction(ui->editToolBar->toggleViewAction());
	ui->menuToolbars->addAction(ui->typeToolBar->toggleViewAction());
	ui->menuToolbars->addSeparator();
	ui->menuToolbars->addAction(ui->lockToolBars);

	QPalette palette = menuBar()->palette();
	palette.setColor(QPalette::Button, ui->menuToolBar->palette().color(QPalette::Window));
	ui->menuToolBar->setPalette(palette);
	ui->menuToolBar->addWidget(menuBar());

	ui->screenTree->setFilterWidget(ui->screenTreeFilter);
	ui->objectTree->setFilterWidget(ui->objectTreeFilter);

	tabs = new QTabWidget(this);

	gameDisplayer = new GameDisplayer(core,draw,sound,displayWidget);
	objectDisplayer = new ObjectDisplayer(core,draw,sound,displayWidget);

	tabs->addTab(gameDisplayer,ui->screenTree->iconScreen, tr("Screen editor"));
	tabs->addTab(objectDisplayer,ui->objectTree->iconObject, tr("Object editor"));
	tabs->addTab(new QWidget(),ui->objectTree->iconAction, tr("Action editor"));

	setCentralWidget(tabs);

	gameDisplayer->setFocus();

	// Read settings once all widgets have been properly set.

	readSettings();

	connectSignals();

	setCurrentFile("");
}

void yggdrasil_editor::closeEvent(QCloseEvent *event)
{
	if (maybeSave()) {
		writeSettings();
		event->accept();
	} else {
		event->ignore();
	}
}

void yggdrasil_editor::contextMenuEvent(QContextMenuEvent *event)
{
	QMenu popup;

	popup.addMenu(ui->menuDocks);
	popup.addMenu(ui->menuToolbars);

	popup.exec(event->globalPos());
}

void yggdrasil_editor::on_fileNew_triggered()
{
	if (maybeSave()) {
		/*		delete currentScreen;
		currentScreen = new Screen();*/
		setCurrentFile("");
	}
}

void yggdrasil_editor::on_fileOpen_triggered()
{
	if (maybeSave()) {
		QString fileName = QFileDialog::getOpenFileName(this);
		if (!fileName.isEmpty())
			loadFile(fileName);
	}
}

bool yggdrasil_editor::on_fileSave_triggered()
{
	if (curFile.isEmpty()) {
		return on_fileSaveAs_triggered();
	} else {
		return saveFile(curFile);
	}
}

bool yggdrasil_editor::on_fileSaveAs_triggered()
{
	QString fileName = QFileDialog::getSaveFileName(this);
	if (fileName.isEmpty())
		return false;

	return saveFile(fileName);
}

void yggdrasil_editor::readSettings()
{
	QPoint pos;
	QSize size;

	QSettings settings("yggdrasil", "editor");

	restoreGeometry(settings.value("geometry").toByteArray());
	restoreState(settings.value("windowState").toByteArray());
	ui->lockToolBars->setChecked(settings.value("toolBars/locked").toBool());

	currentGameDirectory = settings.value("currentGameDirectory", ".").toString();
	QDir::setCurrent(currentGameDirectory);
	ui->screenTree->scan(QDir(currentGameDirectory));
	ui->objectTree->scan(QDir(currentGameDirectory));
}

void yggdrasil_editor::writeSettings()
{
	QSettings settings("yggdrasil", "editor");

	settings.setValue("geometry", saveGeometry());
	settings.setValue("windowState", saveState());
	settings.setValue("currentGameDirectory", currentGameDirectory);
	settings.setValue("toolBars/locked", ui->lockToolBars->isChecked());
}

bool yggdrasil_editor::maybeSave()
{
	/*	if (textEdit->document()->isModified()) {
			int ret = QMessageBox::warning(this, tr("Application"),
						tr("The document has been modified.\n"
						"Do you want to save your changes?"),
						QMessageBox::Yes | QMessageBox::Default,
						QMessageBox::No,
						QMessageBox::Cancel | QMessageBox::Escape);
			if (ret == QMessageBox::Yes)
			return save();
			else if (ret == QMessageBox::Cancel)
			return false;
		}*/
	return true;
}

void yggdrasil_editor::loadFile(const QString &fileName)
{
	//delete currentScreen;

	QApplication::setOverrideCursor(Qt::WaitCursor);
	try {
		FileReader fr(fileName.toLatin1().data());
		//currentScreen = new Screen(*draw,fr);

		setCurrentFile(fileName);
		statusBar()->showMessage(tr("File loaded"), 2000);
	} catch (std::exception &e) {
		QMessageBox::warning(this, tr("Application"),
		                     tr(e.what()));
		//currentScreen = new Screen();
	}
	QApplication::restoreOverrideCursor();
}

bool yggdrasil_editor::saveFile(const QString &fileName)
{
	/*QFile file(fileName);
	if (!file.open(QFile::WriteOnly | QFile::Text)) {
		QMessageBox::warning(this, tr("Application"),
							tr("Cannot write file %1:\n%2.")
							.arg(fileName)
							.arg(file.errorString()));
		return false;
	}

	QTextStream out(&file);
	QApplication::setOverrideCursor(Qt::WaitCursor);
	//out << textEdit->toPlainText();
	QApplication::restoreOverrideCursor();

	setCurrentFile(fileName);
	statusBar()->showMessage(tr("File saved"), 2000);*/
	Q_UNUSED(fileName);
	return true;
}

void yggdrasil_editor::setCurrentFile(const QString &fileName)
{
	curFile = fileName;
	setWindowModified(false);

	QString shownName;
	if (curFile.isEmpty())
		shownName = "untitled.scr";
	else
		shownName = strippedName(curFile);

	setWindowTitle(tr("%1[*] - %2").arg(shownName).arg(tr("Application")));
}

QString yggdrasil_editor::strippedName(const QString &fullFileName)
{
	return QFileInfo(fullFileName).fileName();
}

yggdrasil_editor::~yggdrasil_editor()
{
	delete sound;
	delete draw;
	delete core;

	delete drawPlugin;
	delete corePlugin;

	delete ui;
}

void yggdrasil_editor::onMouseMoved(const QPoint &newPos)
{
	statusBar()->showMessage(QString("Position : (%1,%2)").arg(newPos.x()).arg(newPos.y()));
}

void yggdrasil_editor::initEngine()
{
	try {
		corePlugin = new Plugin("qtcore");
		/*
		*	Until a better solution is found, the global core must be initialized by hand. This is because the
		*	static variable lies in the core plugin namespace, and also in the editor namespace.
		*/
		core = static_cast<core::QtCore*>(corePlugin->create());
		core::Core::globalCore = core;

		drawPlugin = new Plugin("qtdrawgl");
		draw = static_cast<draw::DrawManager*>(drawPlugin->create());
		sound = new sound::SoundManager();

		core->setup(*draw,*sound);

		displayWidget = core->getWidget();
	} catch (std::exception &e) {
		delete sound;
		sound = NULL;
		delete draw;
		draw = NULL;
		delete core;
		core = NULL;
		delete corePlugin;
		corePlugin = NULL;
		delete drawPlugin;
		drawPlugin = NULL;

		displayWidget = NULL;

		QMessageBox::warning(this, tr("Application"),
		                     tr("The following error happened while loading the plugins :\n\n%1\n\nYggdrasil Editor cannot function properly without plugins.")
		                     .arg(QString::fromUtf8(e.what())));
	}
}

void yggdrasil_editor::viewScreen()
{
	tabs->setCurrentWidget(gameDisplayer);
}

void yggdrasil_editor::viewObject()
{
	tabs->setCurrentWidget(objectDisplayer);
}

void yggdrasil_editor::connectSignals()
{
	connect(gameDisplayer,SIGNAL(itemSelected(game::Screen*, game::ScreenElement*)),
		ui->screenTree, SLOT(on_selectItem(game::Screen*, game::ScreenElement*)));

	connect(gameDisplayer,SIGNAL(itemUnselected(game::Screen*, game::ScreenElement*)),
		ui->screenTree, SLOT(on_unselectItem(game::Screen*, game::ScreenElement*)));

	connect(gameDisplayer,SIGNAL(objectCreated(game::Screen*, game::ScreenElement*)),
		ui->screenTree, SLOT(on_objectAdded(game::Screen*, game::ScreenElement*)));

	connect(gameDisplayer,SIGNAL(mouseMoved(const QPoint &)),this, SLOT(onMouseMoved(const QPoint &)));

	connect(objectDisplayer,SIGNAL(mouseMoved(const QPoint &)),this, SLOT(onMouseMoved(const QPoint &)));

	connect(ui->screenTree,SIGNAL(itemSelected(game::Screen*, QString)),gameDisplayer,SLOT(selectItem(game::Screen*, QString)));
	connect(ui->screenTree,SIGNAL(loadScreen(game::Screen*)),gameDisplayer,SLOT(loadScreen(game::Screen*)));
	connect(ui->screenTree,SIGNAL(loadScreen(game::Screen*)),this,SLOT(viewScreen()));
	connect(ui->screenTree,SIGNAL(closeScreen(game::Screen*)),gameDisplayer,SLOT(closeScreen(game::Screen*)));
	connect(ui->screenTree,SIGNAL(screenSelected(game::Screen*)),ui->propertyWidget,SLOT(selectScreen(game::Screen*)));
	connect(ui->screenTree,SIGNAL(removeObject(game::Screen*, game::ScreenElement*)),gameDisplayer,SLOT(removeItem(game::Screen*, game::ScreenElement*)));
	connect(ui->screenTree,SIGNAL(itemSelected(game::Screen*, QString)),ui->propertyWidget,SLOT(selectScreenItem(game::Screen*, QString)));

	connect(gameDisplayer,SIGNAL(itemUnselected(game::Screen*, game::ScreenElement*)),ui->propertyWidget,SLOT(unselect()));

	connect(gameDisplayer,SIGNAL(itemSelected(game::Screen*, game::ScreenElement*)),ui->propertyWidget,SLOT(selectScreenItem(game::Screen*, game::ScreenElement*)));

	connect(gameDisplayer,SIGNAL(itemChanged(game::Screen*, game::ScreenElement*)),ui->propertyWidget,SLOT(selectScreenItem(game::Screen*, game::ScreenElement*)));

	connect(gameDisplayer,SIGNAL(objectRemoved(game::Screen*, game::ScreenElement*)),ui->screenTree,SLOT(on_objectRemoved(game::Screen*,game::ScreenElement*)));

	connect(ui->propertyWidget,SIGNAL(screenUpdated(game::Screen*)),gameDisplayer,SLOT(loadScreen(game::Screen*)));

	connect(ui->objectTree,SIGNAL(objectSelected(game::ScreenElement*)),ui->propertyWidget,SLOT(selectScreenElement(game::ScreenElement*)));

	connect(ui->objectTree,SIGNAL(loadObject(game::ScreenElement*)),objectDisplayer,SLOT(loadObject(game::ScreenElement*)));
	connect(ui->objectTree,SIGNAL(loadObject(game::ScreenElement*)),this,SLOT(viewObject()));

	connect(ui->objectTree,SIGNAL(actionSelected(game::ScreenElement*, game::Action*)),ui->propertyWidget,SLOT(selectAction(game::ScreenElement*,game::Action*)));

}

void yggdrasil_editor::on_lockToolBars_toggled(bool locked)
{
	foreach(QToolBar *tb, findChildren<QToolBar*>()) {
		tb->setMovable(not locked);
	}
}


}
