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
#include "propertylist.h"
#include <QPainter>
#include <QDebug>
//#include <QFontMetrics>

namespace editor
{

namespace property
{

PropertyList::PropertyList(const QVariant &defaultValue) :
	PropertyItem()
{
	modelCombo = new QComboBox();

	set(defaultValue);
}


PropertyList::~PropertyList()
{
	delete modelCombo;
}

void PropertyList::add(const QIcon &icon, const QString &label, const QVariant &value)
{
	modelCombo->addItem(icon,label,value);
}

void PropertyList::add(const QString &label, const QVariant &value)
{
	modelCombo->addItem(label,value);
}

void PropertyList::clear()
{
	modelCombo->clear();
}


bool PropertyList::custom() const
{
	return true;
}

void PropertyList::setter(QWidget *editor)
{
	Q_UNUSED(editor);
	currentCombo->setCurrentIndex(currentCombo->findData(get()));
}

void PropertyList::getter(QWidget *editor)
{
	Q_UNUSED(editor);
	set(currentCombo->itemData(currentCombo->currentIndex()));
}

void PropertyList::set(const QVariant &pData)
{
	currentData = pData;

	int index = modelCombo->findData(get());
	if (index >= 0) {
		setData(modelCombo->itemText(index), Qt::DisplayRole);
		setData(modelCombo->itemIcon(index), Qt::DecorationRole);
	}
}

QVariant PropertyList::get() const
{
	return currentData;
}

void PropertyList::updateSelection()
{
	getter(currentCombo);
	setData(QVariant(), Qt::DecorationRole);
}


QWidget *PropertyList::createEditor(QWidget *parent, const QStyleOptionViewItem &option)
{
	setData(QVariant(), Qt::DecorationRole);
	currentCombo = new QComboBox(parent);
	currentCombo->setModel(modelCombo->model());
	connect(currentCombo,SIGNAL(currentIndexChanged(int)),
	        this,SLOT(updateSelection()));
	return currentCombo;

	Q_UNUSED(parent);
	Q_UNUSED(option);
}

}

}
