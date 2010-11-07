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
#ifndef EDITOR_PROPERTYPROPERTYITEMDELEGATE_H
#define EDITOR_PROPERTYPROPERTYITEMDELEGATE_H

#include <QItemDelegate>

#include "propertyitemmodel.h"

namespace editor {

namespace property {

/**
	@author flik <flik@baobob.org>
*/
class PropertyItemDelegate : public QItemDelegate
{
	Q_OBJECT
public:
	PropertyItemDelegate(QObject *parent=0, PropertyItemModel *pModel=0);

    ~PropertyItemDelegate();
	
	virtual QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
	
	virtual void setEditorData(QWidget *editor, const QModelIndex &index) const;
	
	
	virtual void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
	
	virtual QSize sizeHint (const QStyleOptionViewItem &option, const QModelIndex &index) const;
	
	virtual void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index ) const;
	void try_connect(QWidget *editor,const char *sigName,const char *signal) const;
	
	PropertyItemModel *model;
private slots:
	virtual void valueChanged();
};

}

}

#endif
