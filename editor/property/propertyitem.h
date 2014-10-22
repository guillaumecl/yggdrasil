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
#ifndef EDITORPROPERTYITEM_H
#define EDITORPROPERTYITEM_H

#include <QStandardItem>
#include <QStyleOptionViewItem>

namespace editor
{

namespace property
{

class PropertyItemModel;
/**
	@author flik <flik@baobob.org>
*/
class PropertyItem : public QStandardItem
{
public:
	PropertyItem();
	PropertyItem(const QVariant &text);

	~PropertyItem();

	PropertyItemModel *model() const;

	virtual void appendRow(PropertyItem *value);
	virtual void appendRow(const QString &propertyName, PropertyItem *value);
	virtual void appendRow(PropertyItem *label, PropertyItem *value);
	virtual void set(const QVariant &pData);
	virtual QVariant get() const;

	virtual int type() const;

	virtual bool custom() const;

	virtual void setter(QWidget *editor);
	virtual void getter(QWidget *editor);

	virtual QSize sizeHint(const QStyleOptionViewItem &option) const;
	virtual bool paint(QPainter *painter, const QStyleOptionViewItem &option) const;

	virtual QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option);
};

/**
@author flik <flik@baobob.org>
*/
class PropertySectionItem : public PropertyItem
{
public:
	PropertySectionItem(QString pSectionName);

	~PropertySectionItem();

	int type() const;

};

class PropertyCaption: public PropertyItem
{
public:
	PropertyCaption(const QString &text);
	PropertyCaption(const QIcon &icon, const QString &text);
};

}

}

#endif
