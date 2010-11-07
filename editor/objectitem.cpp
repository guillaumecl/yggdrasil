/***************************************************************************
 *   Copyright (C) 2007 by flik   *
 *   flik@baobob.org   *
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

#include "objectitem.h"
#include "mime.h"

using game::Screen;
using game::ScreenElement;
using game::Action;

namespace editor
{

namespace custom
{

ObjectItem::ObjectItem(const QIcon &pIcon, const QString &pText, const QString &pName, int pType) :
	QStandardItem(pIcon,pText),
	mType(pType),
	mName(pName),
	hasPointer(false),
	mPointer(NULL)
{
	setEditable(false);
}

ObjectItem::ObjectItem(const QIcon &pIcon, const QString &pText, int pType) :
	QStandardItem(pIcon,pText),
	mType(pType),
	mName(pText),
	hasPointer(false),
	mPointer(NULL)
{
	setEditable(false);
}

int ObjectItem::type() const
{
	return mType;
}

void *ObjectItem::pointer() const
{
	return mPointer;
}

Screen *ObjectItem::screen() const
{
	if(type() == item::Screen)
		return (Screen*)pointer();
	return NULL;
}

ScreenElement *ObjectItem::screenElement() const
{
	if(type() == item::Object)
		return (ScreenElement*)pointer();
	return NULL;
}

Action *ObjectItem::action() const
{
	if(type() == item::Action)
		return (Action*)pointer();
	return NULL;
}

QString ObjectItem::name() const
{
	return mName;
}

void ObjectItem::setName(const QString &pName)
{
	mName = pName;
	setData(pName,drag::Name);
}

void ObjectItem::setPointer(void *pPointer)
{
	hasPointer = pPointer != NULL;
	if(hasPointer)
	{
		QFont fnt = font();
		fnt.setBold(true);
		setFont(fnt);
	}
	mPointer = pPointer;
}

void ObjectItem::setScreenElement(game::ScreenElement *el)
{
	setPointer(el);
}

void ObjectItem::setScreen(game::Screen *scr)
{
	setPointer(scr);
}

void ObjectItem::setAction(game::Action *act)
{
	setPointer(act);
}

bool ObjectItem::isLoaded() const
{
	return hasPointer;
}


bool ObjectItem::hasVisibleChildren(QRegExp pFilter)
{
	int i;
	for(i=0;i<rowCount();i++)
	{
		ObjectItem *el = dynamic_cast<ObjectItem*>(child(i,0));
		if(el)
		{
			if(el->type() == item::Object && el->text().contains(pFilter))
				return true;
			else if(el->type() == item::Screen && el->text().contains(pFilter))
				return true;
			else if(el->type() == item::Folder)
			{
				if(el->hasVisibleChildren(pFilter))
					return true;
			}
		}
	}
	return false;
}

ObjectItem *ObjectItem::parent() const
{
	return dynamic_cast<ObjectItem*>(QStandardItem::parent());
}

}

}
