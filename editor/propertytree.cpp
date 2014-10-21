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
#include "propertytree.h"
#include <QDebug>
#include "propertyitemdelegate.h"
#include "propertyitemmodel.h"
#include "propertyitem.h"


namespace editor
{

namespace property
{


PropertyTree::PropertyTree(QWidget *parent) :
	QTreeView(parent),
	model(NULL)
{
	model = new PropertyItemModel(this);
	setModel(model);
	setColumnWidth(0,100);

	setAllColumnsShowFocus(true);
	setRootIsDecorated(false);
	setIndentation(0);

	setItemDelegate(new PropertyItemDelegate(this,model));

	connect(model,SIGNAL(itemChanged(QStandardItem *)),this,SLOT(update(QStandardItem*)));
}

void PropertyTree::update(QStandardItem *item)
{
	PropertyItem *it = dynamic_cast<PropertyItem*>(item);
	if (it)
		itemUpdated(it);
}

PropertyTree::~PropertyTree()
{
}

PropertyItem *PropertyTree::insertSection(const QString &sectionName, PropertyItem *pParent)
{
	PropertyItem *it;
	it = new PropertySectionItem(sectionName);
	if (pParent) {
		pParent->appendRow(it);
		setFirstColumnSpanned(it->row(),pParent->index(),true);
	} else {
		model->appendRow(it);
		setFirstColumnSpanned(it->row(),model->invisibleRootItem()->index(),true);
	}
	setExpanded(it->index(), true);
	return it;
}

void PropertyTree::currentChanged(const QModelIndex &current, const QModelIndex &previous)
{
	PropertyItem *item = model->itemFromIndex(current);
	if (item->isEditable())
		edit(current);
	Q_UNUSED(previous);
}
}

}
