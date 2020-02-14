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


#pragma once

#include <QMainWindow>

#include "types_ui.h"
#include "common/common_types.h"

#include "qtcore/qtcore_types.h"
#include "game/basictypes.h"

class QTextEdit;
class QTabWidget;

class Ui_yggdrasil_editor;

namespace editor
{

class yggdrasil_editor: public QMainWindow
{
	Q_OBJECT

public:
	yggdrasil_editor();
	~yggdrasil_editor();
	void initEngine();

protected:
	void closeEvent(QCloseEvent *event);
	void contextMenuEvent(QContextMenuEvent *event);

private slots:
	void on_fileNew_triggered();
	void on_fileOpen_triggered();
	bool on_fileSave_triggered();
	bool on_fileSaveAs_triggered();
	void on_lockToolBars_toggled(bool);
	void onMouseMoved(const QPoint &newPos);
	void viewScreen();
	void viewObject();

private:
	void readSettings();
	void writeSettings();
	bool maybeSave();
	void loadFile(const QString &fileName);
	bool saveFile(const QString &fileName);
	void setCurrentFile(const QString &fileName);
	QString strippedName(const QString &fullFileName);

	QString currentGameDirectory;
	QString curFile;

	view::GameDisplayer *gameDisplayer;
	view::ObjectDisplayer *objectDisplayer;

	/**
	 * Core object that was created in the constructor
	 */
	core::QtCore *core;

	/**
	 * Draw Manager object that was created in the constructor
	 */
	draw::DrawManager *draw;

	/**
	 * Sound Manager object that was created in the constructor
	 */
	sound::SoundManager *sound;

	/**
	 * The GL Widget is a special kind of part of the Core object, created only by the QtCore plugin. This gives some control to insert the drawing inside our Main window.
	 */
	core::DisplayWidget *displayWidget;

	/**
	 * Core plugin
	 */
	Plugin *corePlugin;

	/**
	 * Draw plugin
	 */
	Plugin *drawPlugin;

	QTabWidget *tabs;

	void connectSignals();

	Ui_yggdrasil_editor *ui;
};



/**
 *
 * This is the list of things to do for the Yggdrasil Editor.
 *
 *
 * @done Allow multiple selected item in the GameDisplayer.
 * Features include: moving several items, delete several items. Control/Shift +click select items in the ScreenTree, select no item in the properties widget.
 * note:selecting several items in the screen tree was not done.It's unsure whether this is useful or not.
 *
 * @done Implement the Locked ScreenElement feature.
 * Aim : put an item into locked state. The item cannot be selected in the game screen, only in the screen Tree. This way, background items will not be a nuisance anymore.
 *
 * @done Delete a ScreenElement feature. More generally speaking, add some actions to a context menu for the selected screen element(s).
 *
 * @done Properties tree Widget.
 * This needs some thinking because it needs to be quite generic to hold the properties for all of the object that will be handled in the Yggdrasil Editor. Basically, I see two different approaches to address this problem : derive a class for each object type and make a common handler object ; or make a completely generic common handler and make some XSD-like file to handle the different objects. The latter choice may be better if the objects were all handled by XML files, but it's not the case and I personally prefer the first choice. This approach still leaves the opportunity to create a derivate class for generic XSD-like handling afterwards, though.
 *
 * @fixed When viewing a screen that has a vertical scrollbar and no horizontal scrollbar, 16 offscreen pixels can be shown horizontally (can scroll with the mouse and no scrollbar is shown)
 *
 * @done When an item is unselected in the GameDisplayer, unselect it in the screen tree. This will prevent an annoying UI issue where you have to select another item then the current item back to see the properties again.
 *
 * @todo a Toolbar that is shown depending on the context. For example, a ScreenElement toolbar shown when a ScreenElement is selected. Same for a Screen toolbar.
 *
 * @todo Modify several element properties.
 * When several items are selected, if they are of the same type, they should be modified at the same time.
 * This will propably greatly complexify the property handling widget, that works with a single pointer element at
 * a time. Furtermore, a new item state must represent the state "the selected items have a different property", when this happens. Usually it would mean to have no value at all, but this will probably be uneasy to do for boolean values.
 *
 * @done make a context menu inside the GameDisplayer for deleting ScreenElements, add more items later.
 *
 * @todo add the context menu to the ScreenTree also to have uniform handling.
 *
 * @todo add a "line Y" property that defines the offset Y of an item. This offset is added to the Y before drawing, just like Y. It's only used to move some items up/down for better viewing (e.g. for the tree, some roots should not be up the character if the character just begins to be up in the first 15 pixels)
 *
 * @fixme the selection of a single item seems to have some remaining bugs (look at mousePressEvent)
 *
 * @todo implement the handling of a "readonly" item, and readonly trees.
 */
}
