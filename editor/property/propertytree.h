/***************************************************************************
 *   Copyright (C) 2007 by flik   *
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
#ifndef QTREEVIEWPROPERTYTREE_H
#define QTREEVIEWPROPERTYTREE_H

#include <QTreeView>
#include "editor/ui_types.h"
#include "game/screen.h"

class QStandardItem;

namespace editor
{

namespace property
{

/**
	@author flik <flik@baobob.org>
*/
class PropertyTree : public QTreeView
{
	Q_OBJECT
public:
	PropertyTree(QWidget *parent=0);

	~PropertyTree();

	PropertyItem *insertSection(const QString &sectionName, PropertyItem *parent=0);

	virtual void sync(void *item) = 0;
	virtual void itemUpdated(PropertyItem *item) = 0;

	virtual void setReadOnly(bool bReadOnly) = 0;
protected:
	PropertyItemModel *model;

	void currentChanged(const QModelIndex &current, const QModelIndex &previous);

private slots:
	void update(QStandardItem *item);
signals:
	void screenUpdated(game::Screen *scr);
};

}

}

#endif
