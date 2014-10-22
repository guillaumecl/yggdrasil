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

#include "ui_types.h"
#include "game/basictypes.h"
#include <QTreeView>
#include <QDir>

class QStandardItem;
class QStandardItemModel;

namespace editor
{

/**
 *	@author Lightning Flik <flik@baobob.org>
 */
class ScreenTree:public QTreeView
{
	Q_OBJECT

public:
	ScreenTree(QWidget *parent);

	~ScreenTree();

	void scan(QDir curDir, QStandardItem *folder = 0);

	void updateScreenInfo(custom::ObjectItem *item);
	QWidget *insertFilter();
	void setFilterWidget(custom::FilterWidget *filter);

	QIcon iconObject;
	QIcon iconScreen;
	QIcon iconFolderClosed;
	QIcon iconFolderOpen;

signals:
	void loadScreen(game::Screen *scr);
	void closeScreen(game::Screen *scr);
	void itemSelected(game::Screen *containerScreen, const QString &scrElName);
	void screenSelected(game::Screen *Screen);
	void removeObject(game::Screen *Screen, game::ScreenElement *el);

private slots:
	void openItem(const QModelIndex &);
	void on_close();
	void on_refresh();
	void on_load();

public slots:
	void on_selectItem(game::Screen *scr, game::ScreenElement *scrEl);
	void on_unselectItem(game::Screen *scr, game::ScreenElement *scrEl);
	void on_objectAdded(game::Screen *scr, game::ScreenElement *scrEl);
	void on_objectRemoved(game::Screen *scr, game::ScreenElement *scrEl);

protected:
	void currentChanged(const QModelIndex &current, const QModelIndex &previous);
	void keyPressEvent(QKeyEvent *event);

private:
	void addScreen(QString scrFile, QStandardItem *folder);

	QPoint dragStartPosition;

	void loadScreenInfo(custom::ObjectItem *item);

	void addElement(std::string pName, game::ScreenElement *element, custom::ObjectItem *scr);

	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);

	void refresh();
	void close();

	QAction *actLoad;
	QAction *actRefresh;
	QAction *actClose;

	custom::ObjectItem *getWidgetForScreen(game::Screen *pScr);
	custom::ObjectItem *getWidgetForObject(custom::ObjectItem *base, game::ScreenElement *scrEl);

	QStandardItemModel *itemModel;
	custom::ItemFilter *filterModel;

	custom::ObjectItem *itemAt(const QPoint &pos);
	custom::ObjectItem *itemAt(const QModelIndex &ind);

	void setCurrentIndex(const QModelIndex &ind);
	void setExpanded(const QModelIndex &ind, bool pExpanded);
};

}
