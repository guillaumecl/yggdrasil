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

#include "game/basictypes.h"

#include <QTreeView>
#include <QStandardItemModel>
#include <QSortFilterProxyModel>

#include "ui_types.h"

#include <QDir>

namespace editor
{

/**
 *	@author Lightning Flik <flik@baobob.org>
 */
class ObjectTree:public QTreeView
{
	Q_OBJECT

public:
	ObjectTree(QWidget *parent);

	~ObjectTree();

	void scan(QDir curDir, QStandardItem *parent = NULL);

	void addObject(QString objFile, QStandardItem *parent);

	void updateScreenInfo(QStandardItem *item);

	QString getName(QStandardItem *it);

	QWidget *insertFilter();
	void setFilterWidget(custom::FilterWidget *filter);

	QIcon iconObject;
	QIcon iconAction;
	QIcon iconFolderClosed;
	QIcon iconFolderOpen;

signals:
	void objectSelected(game::ScreenElement *scrEl);
	void actionSelected(game::ScreenElement *scrEl,game::Action *act);
	void loadObject(game::ScreenElement *scrEl);

private slots:
	void on_itemExpanded(const QModelIndex &index);
	void on_itemCollapsed(const QModelIndex &index);
	void on_itemLoaded(game::ScreenElement *scrEl);
	void on_load();

private:
	QPoint dragStartPosition;

	void setName(custom::ObjectItem *it, QString name);
	void setType(custom::ObjectItem *it, int type);
	int getType(custom::ObjectItem *it);

	custom::ObjectItem *itemAt(const QPoint &);
	custom::ObjectItem *itemAt(const QModelIndex &);

	QStandardItemModel *itemModel;
	custom::ItemFilter *filterModel;

	QAction *actLoad;
	QAction *actRefresh;
	QAction *actClose;
	void scanObject(custom::ObjectItem *obj);

protected:
	void mouseDoubleClickEvent(QMouseEvent *event);
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void currentChanged(const QModelIndex &selected, const QModelIndex &previous);
};

}
