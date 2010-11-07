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
#ifndef EDITORPROPERTYIDEMMODEL_H
#define EDITORPROPERTYIDEMMODEL_H

#include <QStandardItemModel>
#include "propertyitem.h"

namespace editor {

namespace property
{

namespace type
{
const int generic = QStandardItem::UserType;
const int section = QStandardItem::UserType+1;
}

/**
	@author flik <flik@baobob.org>
*/
class PropertyItemModel : public QStandardItemModel
{
	Q_OBJECT
public:
    PropertyItemModel(QObject *parent=0);

    ~PropertyItemModel();
	
	PropertyItem *item(int row, int column = 0) const;
	PropertyItem *itemFromIndex (const QModelIndex & index) const;
	
	virtual void appendRow(PropertyItem *value);
	virtual void appendRow(const QString &propertyName, PropertyItem *value);
	virtual void appendRow(PropertyItem *label, PropertyItem *value);
	
	PropertyItem *takeItem (int row, int column = 0);
};

}

}

#endif
