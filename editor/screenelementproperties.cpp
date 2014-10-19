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
#include "screenelementproperties.h"
#include <QDebug>
#include "game/screenelement.h"

using game::ScreenElement;
using game::Action;
using namespace game;

namespace editor
{

namespace property
{

ScreenElementProperties::ScreenElementProperties(QWidget *parent) :
	PropertyTree(parent),
	current(NULL)
{
	PropertyItem *section = insertSection(tr("ScreenElement"));

	width = new PropertyItem(0);
	height = new PropertyItem(0);
	direction = new PropertyList(directions::up);

	direction->add(QIcon(":/arrows/up.png"),tr("Up"), directions::up);
	direction->add(QIcon(":/arrows/down.png"),tr("Down"), directions::down);
	direction->add(QIcon(":/arrows/left.png"),tr("Left"), directions::left);
	direction->add(QIcon(":/arrows/right.png"),tr("Right"), directions::right);
	direction->add(QIcon(":/arrows/up_left.png"),tr("Up Left"), directions::upLeft);
	direction->add(QIcon(":/arrows/up_right.png"),tr("Up Right"), directions::upRight);
	direction->add(QIcon(":/arrows/down_right.png"),tr("Down Right"), directions::downRight);
	direction->add(QIcon(":/arrows/down_left.png"),tr("Down left"), directions::downLeft);

	section->appendRow(tr("width"), width);
	section->appendRow(tr("height"), height);
	section->appendRow(tr("direction"), direction);

	section = insertSection(tr("ScreenEditor"));

	icon = new PropertyItem(QIcon());
	offsetX = new PropertyItem(0);
	offsetY = new PropertyItem(0);
	defaultAction = new PropertyList("");

	section->appendRow(tr("icon"), icon);
	section->appendRow(tr("offsetX"), offsetX);
	section->appendRow(tr("offsetY"), offsetY);
	section->appendRow(tr("defaultAction"), defaultAction);
}


ScreenElementProperties::~ScreenElementProperties()
{
}


void ScreenElementProperties::sync(void *item)
{
	ScreenElement *el = static_cast<ScreenElement*>(item);
	if (!el)
		return;

	current = NULL;

	width->set(el->width());
	height->set(el->height());
	direction->set(el->direction);

	offsetX->set(0);
	offsetY->set(0);

	defaultAction->clear();
	std::map<std::string, Action *>::iterator i;
	for (i = el->actions.begin(); i != el->actions.end() ; i++) {
		QString name = QString::fromStdString(i->first);
		defaultAction->add(name,name);
	}
	defaultAction->set(QString::fromStdString(el->defaultActionName));

	current = el;
}

void ScreenElementProperties::itemUpdated(PropertyItem *item)
{
	if (!current)
		return;
	if (item == direction)
		current->direction = (directions::DirectionType) item->get().toInt();

	if (item == defaultAction)
		current->defaultActionName = defaultAction->get().toString().toStdString();

	if (item == height)
		current->setSize(current->width(),height->get().toInt());

	if (item == width)
		current->setSize(width->get().toInt(),current->height());

	//emit screenElementUpdated(current);
}


void ScreenElementProperties::setReadOnly(bool pReadOnly)
{
	width->setEditable(!pReadOnly);
	height->setEditable(!pReadOnly);
	direction->setEditable(!pReadOnly);
	icon->setEditable(!pReadOnly);
	offsetX->setEditable(!pReadOnly);
	offsetY->setEditable(!pReadOnly);
	defaultAction->setEditable(!pReadOnly);
}

}

}
