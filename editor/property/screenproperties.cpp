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
#include "screenproperties.h"
#include <QDebug>

#include "game/screen.h"

#include "propertyitem.h"

using game::Screen;

namespace editor
{

namespace property
{

ScreenProperties::ScreenProperties(QWidget *parent) :
	PropertyTree(parent)
{
	PropertyItem *section = insertSection(tr("Screen"));

	width = new PropertyItem(0);
	height = new PropertyItem(0);
	section->appendRow(tr("width"), width);
	section->appendRow(tr("height"), height);
}


ScreenProperties::~ScreenProperties()
{
}

void ScreenProperties::sync(void *item)
{
	Screen *scr = static_cast<Screen*>(item);
	if (!scr)
		return;

	/* This disables updating during the sync. (i.e. don't do itemUpdated) */
	current = NULL;

	width->set(scr->width());
	height->set(scr->height());

	current = scr;
}

void ScreenProperties::itemUpdated(PropertyItem *item)
{
	if (!current)
		return;

	if (item == width)
		current->setWidth(width->get().toInt());
	else if (item == height)
		current->setHeight(height->get().toInt());

	emit screenUpdated(current);
}

void ScreenProperties::setReadOnly(bool pReadOnly)
{
	height->setEditable(!pReadOnly);
	width->setEditable(!pReadOnly);
}

}

}
