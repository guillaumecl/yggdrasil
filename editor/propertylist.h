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
#ifndef EDITOR_PROPERTYPROPERTYLIST_H
#define EDITOR_PROPERTYPROPERTYLIST_H

#include <propertyitem.h>
#include <QComboBox>

namespace editor {

namespace property {

/**
	@author flik <flik@baobob.org>
*/
class PropertyList : public QObject, public PropertyItem
{
	Q_OBJECT
public:
	PropertyList(const QVariant &defaultValue);

    ~PropertyList();
	
	void clear();
	void add(const QIcon &icon, const QString &label, const QVariant &value);
	void add(const QString &label, const QVariant &value);
	
	virtual bool custom() const;
	
	virtual void setter(QWidget *editor);
	virtual void getter(QWidget *editor);
	
	virtual void set(const QVariant &pData);
	virtual QVariant get() const;
	
	virtual QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option);
	
private:
	QComboBox *modelCombo;
	QComboBox *currentCombo;
	
	QVariant currentData;
private slots:
	void updateSelection();
};

}

}

#endif
