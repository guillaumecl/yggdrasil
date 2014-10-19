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
#include "screenitemproperties.h"

#include "game/screenelement.h"

using game::ScreenElement;

namespace editor
{

namespace property
{

ScreenItemProperties::ScreenItemProperties(QWidget *parent) :
	ScreenElementProperties(parent)
{
	PropertyItem *section = insertSection(tr("Object"));

	x = new PropertyItem((unsigned int)0);
	y = new PropertyItem((unsigned int)0);
	locked = new PropertyItem(false);
	name = new PropertyItem("");

	section->appendRow(tr("name"), name);
	section->appendRow(tr("X"), x);
	section->appendRow(tr("Y"), y);
	section->appendRow(tr("locked"), locked);

	ScreenElementProperties::setReadOnly(true);
}


ScreenItemProperties::~ScreenItemProperties()
{
}

void ScreenItemProperties::sync(void *item)
{
	ScreenElementProperties::sync(item);

	ScreenElement *el = static_cast<ScreenElement*>(item);
	if (!el)
		return;

	current = NULL;
	/**
	 * @todo Make this use the coordinate used at the screen startup, not the current one modified by the actions.
	 */
	x->set(el->x());
	y->set(el->y());
	locked->set(el->locked);
	name->set(QString::fromStdString(el->getName()));

	current = el;
}

void ScreenItemProperties::itemUpdated(PropertyItem *item)
{
	ScreenElementProperties::itemUpdated(item);

	if (!current)
		return;
	if (item == x)
		current->setPosition(x->get().toInt(),current->y());
	if (item == y)
		current->setPosition(current->x(),y->get().toInt());
	if (item == locked)
		current->locked = locked->get().toBool();
}

void ScreenItemProperties::setReadOnly(bool pReadOnly)
{
	/*
		the default screen properties for the item are always visible and always non editable.
	*/
	ScreenElementProperties::setReadOnly(true);

	locked->setEditable(!pReadOnly);
	name->setEditable(!pReadOnly);
	x->setEditable(!pReadOnly);
	y->setEditable(!pReadOnly);
}

}

}
