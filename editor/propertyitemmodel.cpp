/***************************************************************************
 *  Copyright(C) 2007 by CLEMENT Guillaume    *
 *  guillaume.clement@esial.uhp-nancy.fr    *
 *                                                                        *
 *  This program is free software; you can redistribute it and/or modify  *
 *  it under the terms of the GNU General Public License as published by  *
 *  the Free Software Foundation; either version 2 of the License, or     *
 * (at your option) any later version.                                    *
 *                                                                        *
 *  This program is distributed in the hope that it will be useful,       *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *  GNU General Public License for more details.                          *
 *                                                                        *
 *  You should have received a copy of the GNU General Public License     *
 *  along with this program; if not, write to the                         *
 *  Free Software Foundation, Inc.,                                       *
 *  59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
#include "propertyitemmodel.h"

#include <QDebug>

namespace editor
{

namespace property
{

PropertyItemModel::PropertyItemModel(QObject *parent)
	: QStandardItemModel(parent)
{
	QStringList headers;
	setColumnCount(2);

	headers.append(tr("Property"));
	headers.append(tr("Value"));

	setHorizontalHeaderLabels(headers);
}


PropertyItemModel::~PropertyItemModel()
{
}

PropertyItem *PropertyItemModel::item(int row, int column) const
{
	return static_cast<PropertyItem*>(QStandardItemModel::item(row,column));
}

PropertyItem *PropertyItemModel::itemFromIndex(const QModelIndex &index) const
{
	return static_cast<PropertyItem*>(QStandardItemModel::itemFromIndex(index));
}

PropertyItem *PropertyItemModel::takeItem(int row, int column)
{
	return static_cast<PropertyItem*>(QStandardItemModel::takeItem(row,column));
}

void PropertyItemModel::appendRow(PropertyItem *value)
{
	appendRow(value, new PropertyCaption(""));
}

void PropertyItemModel::appendRow(const QString &propertyName, PropertyItem *value)
{
	appendRow(new PropertyCaption(propertyName), value);
}

void PropertyItemModel::appendRow(PropertyItem *label, PropertyItem *value)
{
	QList<QStandardItem*> items;
	items.append(label);
	items.append(value);

	QStandardItemModel::appendRow(items);
}

}

}
