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
#include "actionproperties.h"
#include "action.h"
#include <QDebug>
#include <QApplication>

using namespace game;
using game::Action;

namespace editor
{

namespace property
{

ActionProperties::ActionProperties(QWidget *parent) :
	PropertyTree(parent)
{
	PropertyItem *section = insertSection(tr("Action"));

	displayName = new PropertyItem("");

	defaultFrame = new PropertyItem("");
	name = new PropertyItem("");

	numFrames = new PropertyItem(0);

	baseOffsetY = new PropertyItem(0);

	background_fileName = new PropertyItem("");
	background_height = new PropertyItem(0);
	background_width = new PropertyItem(0);
	background_offsetX = new PropertyItem(0);
	background_offsetY = new PropertyItem(0);

	object_fileName = new PropertyItem("");
	object_height = new PropertyItem(0);
	object_width = new PropertyItem(0);
	object_offsetX = new PropertyItem(0);
	object_offsetY = new PropertyItem(0);

	foreground_fileName = new PropertyItem("");
	foreground_height = new PropertyItem(0);
	foreground_width = new PropertyItem(0);
	foreground_offsetX = new PropertyItem(0);
	foreground_offsetY = new PropertyItem(0);

	section->appendRow(QApplication::translate("editor::property::ActionProperties","Display Name"), displayName);
	section->appendRow(tr("name"), name);
	section->appendRow(tr("Base Offset Y"), baseOffsetY);
	spr = insertSection(tr("Sprite"),section);


	spr->appendRow(tr("Frame count"),numFrames);
	backgroundPlane = insertSection(tr("Background Plane"),spr);
	foregroundPlane = insertSection(tr("Foreground Plane"),spr);
	objectPlane = insertSection(tr("Object Plane"),spr);

	backgroundPlane->appendRow(tr("Image"),background_fileName);
	backgroundPlane->appendRow(tr("Width"),background_width);
	backgroundPlane->appendRow(tr("Height"),background_height);
	backgroundPlane->appendRow(tr("X Offset"),background_offsetX);
	backgroundPlane->appendRow(tr("Y Offset"),background_offsetY);

	objectPlane->appendRow(tr("Image"),object_fileName);
	objectPlane->appendRow(tr("Width"),object_width);
	objectPlane->appendRow(tr("Height"),object_height);
	objectPlane->appendRow(tr("X Offset"),object_offsetX);
	objectPlane->appendRow(tr("Y Offset"),object_offsetY);

	foregroundPlane->appendRow(tr("Image"),foreground_fileName);
	foregroundPlane->appendRow(tr("Width"),foreground_width);
	foregroundPlane->appendRow(tr("Height"),foreground_height);
	foregroundPlane->appendRow(tr("X Offset"),foreground_offsetX);
	foregroundPlane->appendRow(tr("Y Offset"),foreground_offsetY);
}


ActionProperties::~ActionProperties()
{
}


void ActionProperties::sync(void *item)
{
	Action *action = static_cast<Action*>(item);
	if (!action)
		return;

	current = NULL;

	name->set(QString::fromStdString(action->name));
	//displayName->set(action->mDisplayName);

	numFrames->set(action->spr.numFrames);
	baseOffsetY->set(action->baseOffsetY);

	if (action->spr.foregroundPlane) {
		setExpanded(foregroundPlane->index(),true);
		foregroundPlane->setEnabled(true);

		foreground_fileName->set(QString::fromStdString(action->spr.foregroundPlane->fileName));
		foreground_height->set(action->spr.foregroundPlane->mHeight);
		foreground_width->set(action->spr.foregroundPlane->mWidth);
		foreground_offsetX->set(action->spr.foregroundPlane->offsetX);
		foreground_offsetY->set(action->spr.foregroundPlane->offsetY);
	} else {
		foregroundPlane->setEnabled(false);
		setExpanded(foregroundPlane->index(),false);
	}

	if (action->spr.backgroundPlane) {
		setExpanded(backgroundPlane->index(),true);
		backgroundPlane->setEnabled(true);

		background_fileName->set(QString::fromStdString(action->spr.backgroundPlane->fileName));
		background_height->set(action->spr.backgroundPlane->mHeight);
		background_width->set(action->spr.backgroundPlane->mWidth);
		background_offsetX->set(action->spr.backgroundPlane->offsetX);
		background_offsetY->set(action->spr.backgroundPlane->offsetY);
	} else {
		backgroundPlane->setEnabled(false);
		setExpanded(backgroundPlane->index(),false);
	}

	if (action->spr.objectPlane) {
		setExpanded(objectPlane->index(),true);
		objectPlane->setEnabled(true);

		object_fileName->set(QString::fromStdString(action->spr.objectPlane->fileName));
		object_height->set(action->spr.objectPlane->mHeight);
		object_width->set(action->spr.objectPlane->mWidth);
		object_offsetX->set(action->spr.objectPlane->offsetX);
		object_offsetY->set(action->spr.objectPlane->offsetY);
	} else {
		objectPlane->setEnabled(false);
		setExpanded(objectPlane->index(),false);
	}
	current = action;
}

void ActionProperties::itemUpdated(PropertyItem *item)
{
	if (!current)
		return;

	if (item == name)
		current->name = name->get().toString().toStdString();

	if (item==baseOffsetY)
		current->baseOffsetY = baseOffsetY->get().toInt();

	if (current->spr.backgroundPlane) {
		if (item == background_offsetX)
			current->spr.backgroundPlane->offsetX = background_offsetX->get().toInt();

		if (item == background_offsetY)
			current->spr.backgroundPlane->offsetY = background_offsetY->get().toInt();

		if (item == background_height)
			current->spr.backgroundPlane->mHeight = background_height->get().toInt();

		if (item == background_width)
			current->spr.backgroundPlane->mWidth = background_width->get().toInt();
	}
	if (current->spr.objectPlane) {
		if (item == object_offsetX)
			current->spr.objectPlane->offsetX = object_offsetX->get().toInt();
		if (item == object_offsetY)
			current->spr.objectPlane->offsetY = object_offsetY->get().toInt();
		if (item == object_height)
			current->spr.objectPlane->mHeight = object_height->get().toInt();
		if (item == object_width)
			current->spr.objectPlane->mWidth = object_width->get().toInt();
	}
	if (current->spr.foregroundPlane) {
		if (item == foreground_offsetX)
			current->spr.foregroundPlane->offsetX =
			        foreground_offsetX->get().toInt();
		if (item == foreground_offsetY)
			current->spr.foregroundPlane->offsetY =
			        foreground_offsetY->get().toInt();
		if (item == foreground_height)
			current->spr.foregroundPlane->mHeight = foreground_height->get().toInt();
		if (item == foreground_width)
			current->spr.foregroundPlane->mWidth = foreground_width->get().toInt();
	}
}

void ActionProperties::setReadOnly(bool pReadOnly)
{
	background_fileName->setEditable(!pReadOnly);
	background_height->setEditable(!pReadOnly);
	background_width->setEditable(!pReadOnly);
	background_offsetX->setEditable(!pReadOnly);
	background_offsetY->setEditable(!pReadOnly);

	object_fileName->setEditable(!pReadOnly);
	object_height->setEditable(!pReadOnly);
	object_width->setEditable(!pReadOnly);
	object_offsetX->setEditable(!pReadOnly);
	object_offsetY->setEditable(!pReadOnly);

	foreground_fileName->setEditable(!pReadOnly);
	foreground_height->setEditable(!pReadOnly);
	foreground_width->setEditable(!pReadOnly);
	foreground_offsetX->setEditable(!pReadOnly);
	foreground_offsetY->setEditable(!pReadOnly);
}

}

}
