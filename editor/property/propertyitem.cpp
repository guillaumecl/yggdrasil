/***************************************************************************
 *   Copyright (C) 2007 by CLEMENT Guillaume   *
 *   guillaume.clement@esial.uhp-nancy.fr   *
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
#include "propertyitem.h"
#include "propertyitemmodel.h"

namespace editor
{

namespace property
{


PropertyItem::PropertyItem() :
	QStandardItem()
{
}


PropertyItem::PropertyItem(const QVariant &data) :
	QStandardItem()
{
	set(data);
}

PropertyItem::~PropertyItem()
{
}

PropertyItemModel *PropertyItem::model() const
{
	return static_cast<PropertyItemModel*>(QStandardItem::model());
}


void PropertyItem::appendRow(PropertyItem *value)
{
	appendRow(value, new PropertyCaption(""));
}

void PropertyItem::appendRow(const QString &propertyName, PropertyItem *value)
{
	appendRow(new PropertyCaption(propertyName), value);
}

void PropertyItem::appendRow(PropertyItem *label, PropertyItem *value)
{
	QList<QStandardItem*> items;
	items.append(label);
	items.append(value);

	QStandardItem::appendRow(items);
}

int PropertyItem::type() const
{
	return type::section;
}

void PropertyItem::set(const QVariant &pData)
{
	setData(pData, Qt::DisplayRole);
}

bool PropertyItem::custom() const
{
	return false;
}

void PropertyItem::setter(QWidget *editor)
{
	throw "This must not be called";
	Q_UNUSED(editor);
}

void PropertyItem::getter(QWidget *editor)
{
	throw "This must not be called";
	Q_UNUSED(editor);
}

QWidget *PropertyItem::createEditor(QWidget *parent, const QStyleOptionViewItem &option)
{
	throw "This must not be called";
	Q_UNUSED(parent);
	Q_UNUSED(option);
}



QVariant PropertyItem::get() const
{
	return data(Qt::DisplayRole);
}

QSize PropertyItem::sizeHint(const QStyleOptionViewItem &option) const
{
	return QSize(0,0);
	Q_UNUSED(option);
}

bool PropertyItem::paint(QPainter *painter, const QStyleOptionViewItem &option) const
{
	return false;
	Q_UNUSED(painter);
	Q_UNUSED(option);
}




PropertyCaption::PropertyCaption(const QString &text) :
	PropertyItem(text)
{
	setEditable(false);
}

PropertyCaption::PropertyCaption(const QIcon &icon, const QString &text) :
	PropertyItem(text)
{
	setIcon(icon);
	setEditable(false);
}

PropertySectionItem::PropertySectionItem(QString pSectionName) :
	PropertyItem(pSectionName)
{
	setEditable(false);
	setSelectable(false);
	setEnabled(false);

	setBackground(QBrush(Qt::gray));
	setForeground(QBrush(Qt::white));
	QFont fnt = font();
	fnt.setBold(true);
	setFont(fnt);
}


PropertySectionItem::~PropertySectionItem()
{
}

int PropertySectionItem::type() const
{
	return type::section;
}


}

}
